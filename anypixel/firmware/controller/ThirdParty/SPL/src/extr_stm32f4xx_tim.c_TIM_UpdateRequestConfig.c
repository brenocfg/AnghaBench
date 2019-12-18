#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ CR1; } ;
typedef  TYPE_1__ TIM_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_TIM_UPDATE_SOURCE (scalar_t__) ; 
 scalar_t__ TIM_CR1_URS ; 
 scalar_t__ TIM_UpdateSource_Global ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_UPDATE_SOURCE(TIM_UpdateSource));

  if (TIM_UpdateSource != TIM_UpdateSource_Global)
  {
    /* Set the URS Bit */
    TIMx->CR1 |= TIM_CR1_URS;
  }
  else
  {
    /* Reset the URS Bit */
    TIMx->CR1 &= (uint16_t)~TIM_CR1_URS;
  }
}