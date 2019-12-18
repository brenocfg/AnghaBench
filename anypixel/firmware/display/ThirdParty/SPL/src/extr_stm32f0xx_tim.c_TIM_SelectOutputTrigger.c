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
struct TYPE_4__ {scalar_t__ CR2; } ;
typedef  TYPE_1__ TIM_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_LIST9_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_TIM_TRGO_SOURCE (scalar_t__) ; 
 scalar_t__ TIM_CR2_MMS ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST9_PERIPH(TIMx));
  assert_param(IS_TIM_TRGO_SOURCE(TIM_TRGOSource));

  /* Reset the MMS Bits */
  TIMx->CR2 &= (uint16_t)~((uint16_t)TIM_CR2_MMS);
  /* Select the TRGO source */
  TIMx->CR2 |=  TIM_TRGOSource;
}