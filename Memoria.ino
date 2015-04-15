//Pinos
int pinoLuz[4] = {13, 12, 11, 10}; // Pinos dos leds//
int pinoBotao[4] = {2, 3, 4, 5}; // Pinos dos botões

//Tempo de pausa e de piscar luz
double tempoPausa = 3000; //milissegundos - Tempo que demora no início ou término do jogo//
double tempoBlink = 500; // milissegundos - Tempo em a luz demora para apagar//

class JogoMemoria {
  public:
    JogoMemoria();
    int sequencia[999] = {0};
    int numeroRodada = 0;
    boolean fim;

    //Métodos do jogo//
    void Jogo();
    int Sortear();
    void sequenciaJogador(int numSequencia);
    void Sequencia(int numSequencia);
    void Luz(boolean estado, int numLuz);
    void estadoPausa(double tempo);
};

void JogoMemoria::Jogo() {
  // Jogando //
  fim = false;

  estadoPausa(tempoPausa);

  while (fim == false) {
    numeroRodada++;
    Sequencia(numeroRodada);
    sequenciaJogador(numeroRodada);
  }

  //Game Over//
}

int JogoMemoria::Sortear() {
  //Sorteio de um novo número para a próxima sequência//
  int numeroSorteio = random(4);

  return numeroSorteio;
}

void JogoMemoria::Sequencia(int numSequencia) {
  sequencia[numeroRodada] = Sortear();
  //Exibir sequência
  for (int i = 1; i <= numSequencia; i++) {
    Luz(true, sequencia[i]);
    delay(tempoBlink);
    Luz(false, sequencia[i]);
  }
}

void JogoMemoria::sequenciaJogador(int numSequencia) {
  for (int i = 1; i <= numSequencia; i++) {

    int botaoApertado;
    boolean botaoApertadoOn = false;
    
    //Aguardando jogador
    while (botaoApertadoOn == false)
    {
      //Identificar qual botão foi pressionado
      for (int e = 0; e <= 3; e++) {
        int valor = digitalRead(pinoBotao[i]);
        if (valor == HIGH)
        {
          botaoApertado = e;
          botaoApertadoOn = true;
          Luz(true, e);
          delay(250);
          Luz(false, e);
        }

        if (e != sequencia[i])
        {
          fim = true;
          break;
        }
      }
    }

  }
}

void JogoMemoria::Luz(boolean estado, int numLuz)
{
  //Qual led deve acender ou apagar//
  if (estado == true)
  {
    digitalWrite(pinoLuz[numLuz], HIGH);
  }
  else
  {
    digitalWrite(pinoLuz[numLuz], LOW);
  }
}

void JogoMemoria::estadoPausa(double tempo) {
  
  //Tempo de pausa do jogo - Game Over ou Início//
  
  tempoPausa / 1000;
  for (int i = 0; i < tempoPausa; i++) {
    for (int i = 0; i < 4; i++)
    {
      Luz(true, i);
      delay(250);
      Luz(false, i);
    }
  }
  
  delay(1000);
  
}

//////////////////////////////////////////////////////////////////////////////////////

void setup() {
  for (int i = 0; i <= 3; i++) {
    pinMode(pinoLuz[i], OUTPUT);
    pinMode(pinoBotao[i], OUTPUT);
  }
}

void loop() {
 JogoMemoria Jogo();
}




