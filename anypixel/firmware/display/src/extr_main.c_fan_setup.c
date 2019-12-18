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
struct TYPE_13__ {int /*<<< orphan*/  NVIC_IRQChannelCmd; scalar_t__ NVIC_IRQChannelPriority; int /*<<< orphan*/  NVIC_IRQChannel; } ;
struct TYPE_12__ {int TIM_ICFilter; int /*<<< orphan*/  TIM_ICPrescaler; int /*<<< orphan*/  TIM_ICSelection; int /*<<< orphan*/  TIM_ICPolarity; int /*<<< orphan*/  TIM_Channel; } ;
struct TYPE_11__ {int TIM_Pulse; int /*<<< orphan*/  TIM_OCNIdleState; int /*<<< orphan*/  TIM_OCIdleState; int /*<<< orphan*/  TIM_OCNPolarity; int /*<<< orphan*/  TIM_OCPolarity; int /*<<< orphan*/  TIM_OutputNState; int /*<<< orphan*/  TIM_OutputState; int /*<<< orphan*/  TIM_OCMode; } ;
struct TYPE_10__ {int TIM_Prescaler; int TIM_Period; scalar_t__ TIM_RepetitionCounter; void* TIM_CounterMode; int /*<<< orphan*/  TIM_ClockDivision; } ;
typedef  TYPE_1__ TIM_TimeBaseInitTypeDef ;
typedef  TYPE_2__ TIM_OCInitTypeDef ;
typedef  TYPE_3__ TIM_ICInitTypeDef ;
typedef  TYPE_4__ NVIC_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_pins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  FAN_POWER_AHB ; 
 int /*<<< orphan*/  FAN_POWER_APB1 ; 
 int /*<<< orphan*/  FAN_POWER_APB2 ; 
 int /*<<< orphan*/  NVIC_Init (TYPE_4__*) ; 
 int /*<<< orphan*/  PWM_PINS_NUM ; 
 int /*<<< orphan*/  RCC_AHBPeriphClockCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB1PeriphClockCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB2PeriphClockCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIM16 ; 
 int /*<<< orphan*/  TIM3 ; 
 int /*<<< orphan*/  TIM3_IRQn ; 
 int /*<<< orphan*/  TIM_CKD_DIV1 ; 
 int /*<<< orphan*/  TIM_CKD_DIV4 ; 
 int /*<<< orphan*/  TIM_Channel_1 ; 
 int /*<<< orphan*/  TIM_Cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* TIM_CounterMode_Up ; 
 int /*<<< orphan*/  TIM_CtrlPWMOutputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIM_ICInit (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  TIM_ICPSC_DIV1 ; 
 int /*<<< orphan*/  TIM_ICPolarity_Rising ; 
 int /*<<< orphan*/  TIM_ICSelection_DirectTI ; 
 int /*<<< orphan*/  TIM_ITConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIM_IT_CC1 ; 
 int /*<<< orphan*/  TIM_OC1Init (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TIM_OCIdleState_Set ; 
 int /*<<< orphan*/  TIM_OCMode_PWM1 ; 
 int /*<<< orphan*/  TIM_OCNIdleState_Reset ; 
 int /*<<< orphan*/  TIM_OCNPolarity_High ; 
 int /*<<< orphan*/  TIM_OCPolarity_High ; 
 int /*<<< orphan*/  TIM_OutputNState_Disable ; 
 int /*<<< orphan*/  TIM_OutputState_Enable ; 
 int /*<<< orphan*/  TIM_TimeBaseInit (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TIM_TimeBaseStructInit (TYPE_1__*) ; 
 int /*<<< orphan*/  pins_pwm ; 

void fan_setup() {
    TIM_TimeBaseInitTypeDef tbis;
    TIM_OCInitTypeDef ocis;
    NVIC_InitTypeDef nvis;
    TIM_ICInitTypeDef icis;

    // Turn on peripherals
    RCC_AHBPeriphClockCmd(FAN_POWER_AHB, ENABLE);
    RCC_APB1PeriphClockCmd(FAN_POWER_APB1, ENABLE);
	RCC_APB2PeriphClockCmd(FAN_POWER_APB2, ENABLE);

    CONFIG_pins(pins_pwm, PWM_PINS_NUM);

    // First configure the PWM output
    tbis.TIM_Prescaler = 0;
    tbis.TIM_ClockDivision = TIM_CKD_DIV1;
    tbis.TIM_CounterMode = TIM_CounterMode_Up;
    tbis.TIM_Period = 1920;
    tbis.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM16, &tbis);

    ocis.TIM_OCMode = TIM_OCMode_PWM1;
    ocis.TIM_OutputState = TIM_OutputState_Enable;
    ocis.TIM_OutputNState = TIM_OutputNState_Disable;
    ocis.TIM_Pulse = 1000;
    ocis.TIM_OCPolarity = TIM_OCPolarity_High;
    ocis.TIM_OCNPolarity = TIM_OCNPolarity_High;
    ocis.TIM_OCIdleState = TIM_OCIdleState_Set;
    ocis.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC1Init(TIM16, &ocis);

    TIM_Cmd(TIM16, ENABLE);
    TIM_CtrlPWMOutputs(TIM16, ENABLE);

    // Now configure the Tach PWM input to measure rising edge to rising edge time
    icis.TIM_Channel = TIM_Channel_1;
    icis.TIM_ICPolarity = TIM_ICPolarity_Rising;
    icis.TIM_ICSelection = TIM_ICSelection_DirectTI;
    icis.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    icis.TIM_ICFilter = 0x0;

    TIM_TimeBaseStructInit(&tbis);
    tbis.TIM_Prescaler = 199;
    tbis.TIM_ClockDivision = TIM_CKD_DIV4;
    tbis.TIM_CounterMode = TIM_CounterMode_Up;
    tbis.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &tbis);

    TIM_ICInit(TIM3, &icis);
    TIM_Cmd(TIM3, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);

    nvis.NVIC_IRQChannel = TIM3_IRQn;
    nvis.NVIC_IRQChannelPriority = 0;
    nvis.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvis);
}