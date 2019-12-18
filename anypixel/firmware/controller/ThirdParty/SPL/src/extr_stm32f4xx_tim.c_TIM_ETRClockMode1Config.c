#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  SMCR; } ;
typedef  TYPE_1__ TIM_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_EXT_FILTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_TIM_EXT_POLARITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_TIM_EXT_PRESCALER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_TIM_LIST3_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  TIM_ETRConfig (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TIM_SMCR_SMS ; 
 scalar_t__ TIM_SMCR_TS ; 
 int /*<<< orphan*/  TIM_SlaveMode_External1 ; 
 int /*<<< orphan*/  TIM_TS_ETRF ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler,
                            uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  /* Configure the ETR Clock source */
  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
  
  /* Get the TIMx SMCR register value */
  tmpsmcr = TIMx->SMCR;

  /* Reset the SMS Bits */
  tmpsmcr &= (uint16_t)~TIM_SMCR_SMS;

  /* Select the External clock mode1 */
  tmpsmcr |= TIM_SlaveMode_External1;

  /* Select the Trigger selection : ETRF */
  tmpsmcr &= (uint16_t)~TIM_SMCR_TS;
  tmpsmcr |= TIM_TS_ETRF;

  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}