#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_14__ {int /*<<< orphan*/  TIM_RepetitionCounter; int /*<<< orphan*/  TIM_Prescaler; int /*<<< orphan*/  TIM_Period; scalar_t__ TIM_ClockDivision; scalar_t__ TIM_CounterMode; } ;
struct TYPE_13__ {int /*<<< orphan*/  EGR; int /*<<< orphan*/  RCR; int /*<<< orphan*/  PSC; int /*<<< orphan*/  ARR; scalar_t__ CR1; } ;
typedef  TYPE_1__ TIM_TypeDef ;
typedef  TYPE_2__ TIM_TimeBaseInitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_TIM_CKD_DIV (scalar_t__) ; 
 int /*<<< orphan*/  IS_TIM_COUNTER_MODE (scalar_t__) ; 
 TYPE_1__* TIM1 ; 
 TYPE_1__* TIM15 ; 
 TYPE_1__* TIM16 ; 
 TYPE_1__* TIM17 ; 
 TYPE_1__* TIM2 ; 
 TYPE_1__* TIM3 ; 
 TYPE_1__* TIM6 ; 
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

  if((TIMx == TIM1) || (TIMx == TIM2) || (TIMx == TIM3))
  {
    /* Select the Counter Mode */
    tmpcr1 &= (uint16_t)(~((uint16_t)(TIM_CR1_DIR | TIM_CR1_CMS)));
    tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_CounterMode;
  }
 
  if(TIMx != TIM6)
  {
    /* Set the clock division */
    tmpcr1 &= (uint16_t)(~((uint16_t)TIM_CR1_CKD));
    tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_ClockDivision;
  }

  TIMx->CR1 = tmpcr1;

  /* Set the Autoreload value */
  TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period ;
 
  /* Set the Prescaler value */
  TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;
    
  if ((TIMx == TIM1) || (TIMx == TIM15)|| (TIMx == TIM16) || (TIMx == TIM17))  
  {
    /* Set the Repetition Counter value */
    TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
  }

  /* Generate an update event to reload the Prescaler and the Repetition counter
     values immediately */
  TIMx->EGR = TIM_PSCReloadMode_Immediate;           
}