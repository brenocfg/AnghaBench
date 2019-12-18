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
struct TYPE_4__ {scalar_t__ CCMR1; } ;
typedef  TYPE_1__ TIM_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_LIST4_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_TIM_OCFAST_STATE (scalar_t__) ; 
 scalar_t__ TIM_CCMR1_OC1FE ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr1 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  
  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC1FE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC1FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr1 |= TIM_OCFast;
  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
}