#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int CFGR; int CFGR3; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RCC_ADCCLK (int) ; 
 TYPE_1__* RCC ; 
 int RCC_CFGR3_ADCSW ; 
 int RCC_CFGR_ADCPRE ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RCC_ADCCLKConfig(uint32_t RCC_ADCCLK)
{ 
  /* Check the parameters */
  assert_param(IS_RCC_ADCCLK(RCC_ADCCLK));

  /* Clear ADCPRE bit */
  RCC->CFGR &= ~RCC_CFGR_ADCPRE;
  /* Set ADCPRE bits according to RCC_PCLK value */
  RCC->CFGR |= RCC_ADCCLK & 0xFFFF;

  /* Clear ADCSW bit */
  RCC->CFGR3 &= ~RCC_CFGR3_ADCSW; 
  /* Set ADCSW bits according to RCC_ADCCLK value */
  RCC->CFGR3 |= RCC_ADCCLK >> 16;  
}