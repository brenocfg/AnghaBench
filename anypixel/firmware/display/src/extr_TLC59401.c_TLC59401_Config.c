#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  CR1; } ;
struct TYPE_12__ {int /*<<< orphan*/  SPI_NSS; int /*<<< orphan*/  SPI_CPHA; int /*<<< orphan*/  SPI_CPOL; int /*<<< orphan*/  SPI_Mode; int /*<<< orphan*/  SPI_FirstBit; int /*<<< orphan*/  SPI_Direction; int /*<<< orphan*/  SPI_BaudRatePrescaler; int /*<<< orphan*/  SPI_DataSize; } ;
struct TYPE_11__ {void* TIM_OCNIdleState; void* TIM_OCIdleState; int /*<<< orphan*/  TIM_OCNPolarity; int /*<<< orphan*/  TIM_OCPolarity; scalar_t__ TIM_Pulse; int /*<<< orphan*/  TIM_OutputNState; int /*<<< orphan*/  TIM_OutputState; int /*<<< orphan*/  TIM_OCMode; } ;
struct TYPE_10__ {int TIM_Period; scalar_t__ TIM_RepetitionCounter; int /*<<< orphan*/  TIM_ClockDivision; int /*<<< orphan*/  TIM_CounterMode; scalar_t__ TIM_Prescaler; } ;
typedef  TYPE_1__ TIM_TimeBaseInitTypeDef ;
typedef  TYPE_2__ TIM_OCInitTypeDef ;
typedef  TYPE_3__ SPI_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_pins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Delay (int) ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  RCC_AHBPeriphClockCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB1PeriphClockCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB2PeriphClockCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_BaudRatePrescaler_64 ; 
 int /*<<< orphan*/  SPI_CPHA_1Edge ; 
 int /*<<< orphan*/  SPI_CPOL_Low ; 
 int /*<<< orphan*/  SPI_CR1_SPE ; 
 int /*<<< orphan*/  SPI_DataSize_8b ; 
 int /*<<< orphan*/  SPI_Direction_2Lines_FullDuplex ; 
 int /*<<< orphan*/  SPI_FirstBit_MSB ; 
 int /*<<< orphan*/  SPI_I2S_DeInit (TYPE_4__*) ; 
 int /*<<< orphan*/  SPI_Init (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SPI_Mode_Master ; 
 int /*<<< orphan*/  SPI_NSS_Soft ; 
 int /*<<< orphan*/  TIM_CKD_DIV1 ; 
 int /*<<< orphan*/  TIM_Cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIM_CounterMode_Up ; 
 int /*<<< orphan*/  TIM_CtrlPWMOutputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* TIM_OCIdleState_Reset ; 
 int /*<<< orphan*/  TIM_OCMode_PWM1 ; 
 int /*<<< orphan*/  TIM_OCNPolarity_High ; 
 int /*<<< orphan*/  TIM_OCPolarity_High ; 
 int /*<<< orphan*/  TIM_OutputNState_Disable ; 
 int /*<<< orphan*/  TIM_OutputState_Enable ; 
 int /*<<< orphan*/  TIM_TimeBaseInit (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int TLC59401_CHANNELS ; 
 int TLC59401_GSCLK_CCR ; 
 int /*<<< orphan*/  TLC59401_GSCLK_INIT (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int TLC59401_LOOKUP_ENTRIES ; 
 int /*<<< orphan*/  TLC59401_NUM_PINS ; 
 int /*<<< orphan*/  TLC59401_POWER_AHB ; 
 int /*<<< orphan*/  TLC59401_POWER_APB1 ; 
 int /*<<< orphan*/  TLC59401_POWER_APB2 ; 
 TYPE_4__* TLC59401_SPI ; 
 int /*<<< orphan*/  TLC59401_Send () ; 
 int /*<<< orphan*/  TLC59401_SendDotCorrection () ; 
 int /*<<< orphan*/  TLC59401_SetDotCorrection (int,int) ; 
 int /*<<< orphan*/  TLC59401_SetValue (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLC59401_TMR ; 
 int enableBlank ; 
 int** lookupTable ; 
 int /*<<< orphan*/  pins_tlc59401 ; 

void TLC59401_Config(void) {
    int i, j;

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	SPI_InitTypeDef SPI_InitStruct;

    for(i = 0; i < TLC59401_LOOKUP_ENTRIES; i++) {
        for(j=0; j < TLC59401_CHANNELS; j++) {
            lookupTable[j][i] = (4000*i)/64;
        }
    }

    // Enable clocks
    RCC_AHBPeriphClockCmd(TLC59401_POWER_AHB, ENABLE);
    RCC_APB1PeriphClockCmd(TLC59401_POWER_APB1, ENABLE);
	RCC_APB2PeriphClockCmd(TLC59401_POWER_APB2, ENABLE);

    // FIXME need to move the numerical constants in here to project_config.h

    // Set up GSCLK timer
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TLC59401_TMR, &TIM_TimeBaseStructure);

    // Set up GSCLK compare unit
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TLC59401_GSCLK_INIT(TLC59401_TMR, &TIM_OCInitStructure);

    TLC59401_GSCLK_CCR = (TIM_TimeBaseStructure.TIM_Period + 1)/2;

    CONFIG_pins(pins_tlc59401, TLC59401_NUM_PINS);

    // set up SPI
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;

    SPI_I2S_DeInit(TLC59401_SPI);
	/* Disable first */
	TLC59401_SPI->CR1 &= ~SPI_CR1_SPE;

	/* Init SPI */
	SPI_Init(TLC59401_SPI, &SPI_InitStruct);

	/* Enable SPI */
	TLC59401_SPI->CR1 |= SPI_CR1_SPE;

    for(i = 0; i < 5; i++) {
        // indices are reversed so chip output 16 is index 0
		TLC59401_SetDotCorrection(i*3+1, 31); // R
		TLC59401_SetDotCorrection(i*3+2, 63); // G
		TLC59401_SetDotCorrection(i*3+3, 31); // B
        TLC59401_SetDotCorrection(i*3+17, 31); // R
		TLC59401_SetDotCorrection(i*3+18, 63); // G
		TLC59401_SetDotCorrection(i*3+19, 31); // B
	}

    // Set all dot correction values to max
    TLC59401_SendDotCorrection();

    // Zero out all PWM values so display starts dark initially
    for(i = 0; i < TLC59401_CHANNELS; i++)
        TLC59401_SetValue(i,0);
    TLC59401_Send();
    Delay(10);

    // finally enable the grayscale clock to start display
    TIM_Cmd(TLC59401_TMR, ENABLE);
    TIM_CtrlPWMOutputs(TLC59401_TMR, ENABLE);

    enableBlank = true;
}