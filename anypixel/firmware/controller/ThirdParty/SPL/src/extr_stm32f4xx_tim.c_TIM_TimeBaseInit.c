#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_15__ {int /*<<< orphan*/  TIM_RepetitionCounter; int /*<<< orphan*/  TIM_Prescaler; int /*<<< orphan*/  TIM_Period; scalar_t__ TIM_ClockDivision; scalar_t__ TIM_CounterMode; } ;
struct TYPE_14__ {int /*<<< orphan*/  EGR; int /*<<< orphan*/  RCR; int /*<<< orphan*/  PSC; int /*<<< orphan*/  ARR; int /*<<< orphan*/  CR1; } ;
typedef  TYPE_1__ TIM_TypeDef ;
typedef  TYPE_2__ TIM_TimeBaseInitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_TIM_CKD_DIV (scalar_t__) ; 
 int /*<<< orphan*/  IS_TIM_COUNTER_MODE (scalar_t__) ; 
 TYPE_1__* TIM1 ; 
 TYPE_1__* TIM2 ; 
 TYPE_1__* TIM3 ; 
 TYPE_1__* TIM4 ; 
 TYPE_1__* TIM5 ; 
 TYPE_1__* TIM6 ; 
 TYPE_1__* TIM7 ; 
 TYPE_1__* TIM8 ; 
 scalar_t__ TIM_CR1_CKD ; 
 int TIM_CR1_CMS ; 
 int TIM_CR1_DIR ; 
 int /*<<< orphan*/  TIM_PSCReloadMode_Immediate ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
  uint16_t tmpcr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
  assert_param(IS_TIM_COUNTER_MODE(TIM_TimeBaseInitStruct->TIM_CounterMode));
  assert_param(IS_TIM_CKD_DIV(TIM_TimeBaseInitStruct->TIM_ClockDivision));

  tmpcr1 = TIMx->CR1;  

  if((TIMx == TIM1) || (TIMx == TIM8)||
     (TIMx == TIM2) || (TIMx == TIM3)||
     (TIMx == TIM4) || (TIMx == TIM5)) 
  {
    /* Select the Counter Mode */
    tmpcr1 &= (uint16_t)(~(TIM_CR1_DIR | TIM_CR1_CMS));
    tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_CounterMode;
  }
 
  if((TIMx != TIM6) && (TIMx != TIM7))
  {
    /* Set the clock division */
    tmpcr1 &=  (uint16_t)(~TIM_CR1_CKD);
    tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_ClockDivision;
  }

  TIMx->CR1 = tmpcr1;

  /* Set the Autoreload value */
  TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period ;
 
  /* Set the Prescaler value */
  TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;
    
  if ((TIMx == TIM1) || (TIMx == TIM8))  
  {
    /* Set the Repetition Counter value */
    TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
  }

  /* Generate an update event to reload the Prescaler 
     and the repetition counter(only for TIM1 and TIM8) value immediatly */
  TIMx->EGR = TIM_PSCReloadMode_Immediate;          
}