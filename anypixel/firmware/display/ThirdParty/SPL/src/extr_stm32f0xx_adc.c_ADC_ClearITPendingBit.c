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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ ISR; } ;
typedef  TYPE_1__ ADC_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ADC_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_ADC_CLEAR_IT (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLEAR_IT(ADC_IT));

  /* Clear the selected ADC interrupt pending bits */
  ADCx->ISR = (uint32_t)ADC_IT; 
}