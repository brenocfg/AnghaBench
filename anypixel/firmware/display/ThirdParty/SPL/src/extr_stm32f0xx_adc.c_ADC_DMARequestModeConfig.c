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
struct TYPE_4__ {scalar_t__ CFGR1; } ;
typedef  TYPE_1__ ADC_TypeDef ;

/* Variables and functions */
 scalar_t__ ADC_CFGR1_DMACFG ; 
 int /*<<< orphan*/  IS_ADC_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void ADC_DMARequestModeConfig(ADC_TypeDef* ADCx, uint32_t ADC_DMARequestMode)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_DMACFG;
  ADCx->CFGR1 |= (uint32_t)ADC_DMARequestMode;
}