#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  CCR; } ;
struct TYPE_4__ {int ADC_Mode; int ADC_Prescaler; int ADC_DMAAccessMode; int ADC_TwoSamplingDelay; } ;
typedef  TYPE_1__ ADC_CommonInitTypeDef ;

/* Variables and functions */
 TYPE_3__* ADC ; 
 int /*<<< orphan*/  CR_CLEAR_MASK ; 
 int /*<<< orphan*/  IS_ADC_DMA_ACCESS_MODE (int) ; 
 int /*<<< orphan*/  IS_ADC_MODE (int) ; 
 int /*<<< orphan*/  IS_ADC_PRESCALER (int) ; 
 int /*<<< orphan*/  IS_ADC_SAMPLING_DELAY (int) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void ADC_CommonInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct)
{
  uint32_t tmpreg1 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_MODE(ADC_CommonInitStruct->ADC_Mode));
  assert_param(IS_ADC_PRESCALER(ADC_CommonInitStruct->ADC_Prescaler));
  assert_param(IS_ADC_DMA_ACCESS_MODE(ADC_CommonInitStruct->ADC_DMAAccessMode));
  assert_param(IS_ADC_SAMPLING_DELAY(ADC_CommonInitStruct->ADC_TwoSamplingDelay));
  /*---------------------------- ADC CCR Configuration -----------------*/
  /* Get the ADC CCR value */
  tmpreg1 = ADC->CCR;
  
  /* Clear MULTI, DELAY, DMA and ADCPRE bits */
  tmpreg1 &= CR_CLEAR_MASK;
  
  /* Configure ADCx: Multi mode, Delay between two sampling time, ADC prescaler,
     and DMA access mode for multimode */
  /* Set MULTI bits according to ADC_Mode value */
  /* Set ADCPRE bits according to ADC_Prescaler value */
  /* Set DMA bits according to ADC_DMAAccessMode value */
  /* Set DELAY bits according to ADC_TwoSamplingDelay value */    
  tmpreg1 |= (uint32_t)(ADC_CommonInitStruct->ADC_Mode | 
                        ADC_CommonInitStruct->ADC_Prescaler | 
                        ADC_CommonInitStruct->ADC_DMAAccessMode | 
                        ADC_CommonInitStruct->ADC_TwoSamplingDelay);
                        
  /* Write to ADC CCR */
  ADC->CCR = tmpreg1;
}