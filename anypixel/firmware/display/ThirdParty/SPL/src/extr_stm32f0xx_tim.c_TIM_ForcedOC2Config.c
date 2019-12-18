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
typedef  int uint16_t ;
struct TYPE_4__ {int CCMR1; } ;
typedef  TYPE_1__ TIM_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_FORCED_ACTION (int) ; 
 int /*<<< orphan*/  IS_TIM_LIST6_PERIPH (TYPE_1__*) ; 
 scalar_t__ TIM_CCMR1_OC2M ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC2M Bits */
  tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC2M);
  /* Configure The Forced output Mode */
  tmpccmr1 |= (uint16_t)(TIM_ForcedAction << 8);
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}