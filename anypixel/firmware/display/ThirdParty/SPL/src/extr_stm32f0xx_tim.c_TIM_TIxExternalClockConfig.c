#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  SMCR; } ;
typedef  TYPE_1__ TIM_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_IC_FILTER (scalar_t__) ; 
 int /*<<< orphan*/  IS_TIM_IC_POLARITY (scalar_t__) ; 
 int /*<<< orphan*/  IS_TIM_LIST6_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  TI1_Config (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TI2_Config (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TIM_ICSelection_DirectTI ; 
 int /*<<< orphan*/  TIM_SelectInputTrigger (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  TIM_SlaveMode_External1 ; 
 scalar_t__ TIM_TIxExternalCLK1Source_TI2 ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICPolarity));
  assert_param(IS_TIM_IC_FILTER(ICFilter));
  
  /* Configure the Timer Input Clock Source */
  if (TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  else
  {
    TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  /* Select the Trigger source */
  TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);
  /* Select the External clock mode1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}