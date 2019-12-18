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
struct TYPE_4__ {scalar_t__ CR; scalar_t__ DR; } ;
typedef  TYPE_1__ ADC_TypeDef ;

/* Variables and functions */
 scalar_t__ ADC_CR_ADCAL ; 
 scalar_t__ CALIBRATION_TIMEOUT ; 
 int /*<<< orphan*/  IS_ADC_ALL_PERIPH (TYPE_1__*) ; 
 scalar_t__ RESET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

uint32_t ADC_GetCalibrationFactor(ADC_TypeDef* ADCx)
{
  uint32_t tmpreg = 0, calibrationcounter = 0, calibrationstatus = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  /* Set the ADC calibartion */
  ADCx->CR |= (uint32_t)ADC_CR_ADCAL;
  
  /* Wait until no ADC calibration is completed */
  do
  {
    calibrationstatus = ADCx->CR & ADC_CR_ADCAL;
    calibrationcounter++;  
  } while((calibrationcounter != CALIBRATION_TIMEOUT) && (calibrationstatus != 0x00));
    
  if((uint32_t)(ADCx->CR & ADC_CR_ADCAL) == RESET)
  {
    /*Get the calibration factor from the ADC data register */
    tmpreg = ADCx->DR;
  }
  else
  {
    /* Error factor */
    tmpreg = 0x00000000;
  }
  return tmpreg;
}