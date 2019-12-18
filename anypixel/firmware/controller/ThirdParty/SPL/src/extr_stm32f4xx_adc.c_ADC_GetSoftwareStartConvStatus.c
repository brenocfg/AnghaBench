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
typedef  int uint32_t ;
struct TYPE_4__ {int CR2; } ;
typedef  scalar_t__ FlagStatus ;
typedef  TYPE_1__ ADC_TypeDef ;

/* Variables and functions */
 int ADC_CR2_JSWSTART ; 
 int /*<<< orphan*/  IS_ADC_ALL_PERIPH (TYPE_1__*) ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  /* Check the status of SWSTART bit */
  if ((ADCx->CR2 & ADC_CR2_JSWSTART) != (uint32_t)RESET)
  {
    /* SWSTART bit is set */
    bitstatus = SET;
  }
  else
  {
    /* SWSTART bit is reset */
    bitstatus = RESET;
  }
  
  /* Return the SWSTART bit status */
  return  bitstatus;
}