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
struct TYPE_4__ {int CCMR2; } ;
typedef  TYPE_1__ TIM_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_LIST3_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_TIM_OCFAST_STATE (int) ; 
 scalar_t__ TIM_CCMR2_OC4FE ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

  /* Get the TIMx CCMR2 register value */
  tmpccmr2 = TIMx->CCMR2;

  /* Reset the OC4FE Bit */
  tmpccmr2 &= (uint16_t)(~TIM_CCMR2_OC4FE);

  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr2 |= (uint16_t)(TIM_OCFast << 8);

  /* Write to TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmr2;
}