#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ TIM_Channel; int /*<<< orphan*/  TIM_ICPrescaler; int /*<<< orphan*/  TIM_ICFilter; int /*<<< orphan*/  TIM_ICSelection; int /*<<< orphan*/  TIM_ICPolarity; } ;
typedef  int /*<<< orphan*/  TIM_TypeDef ;
typedef  TYPE_1__ TIM_ICInitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_IC_FILTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_TIM_IC_POLARITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_TIM_IC_PRESCALER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_TIM_IC_SELECTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_TIM_LIST1_PERIPH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_TIM_LIST2_PERIPH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_TIM_LIST3_PERIPH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TI1_Config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI2_Config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI3_Config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI4_Config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TIM_Channel_1 ; 
 scalar_t__ TIM_Channel_2 ; 
 scalar_t__ TIM_Channel_3 ; 
 int /*<<< orphan*/  TIM_SetIC1Prescaler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIM_SetIC2Prescaler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIM_SetIC3Prescaler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIM_SetIC4Prescaler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST1_PERIPH(TIMx));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICInitStruct->TIM_ICPolarity));
  assert_param(IS_TIM_IC_SELECTION(TIM_ICInitStruct->TIM_ICSelection));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICInitStruct->TIM_ICPrescaler));
  assert_param(IS_TIM_IC_FILTER(TIM_ICInitStruct->TIM_ICFilter));
  
  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_2)
  {
    /* TI2 Configuration */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_3)
  {
    /* TI3 Configuration */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    TI3_Config(TIMx,  TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC3Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else
  {
    /* TI4 Configuration */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    TI4_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC4Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
}