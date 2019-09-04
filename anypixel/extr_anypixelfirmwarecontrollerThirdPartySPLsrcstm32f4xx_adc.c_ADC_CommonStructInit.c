#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ADC_TwoSamplingDelay; int /*<<< orphan*/  ADC_DMAAccessMode; int /*<<< orphan*/  ADC_Prescaler; int /*<<< orphan*/  ADC_Mode; } ;
typedef  TYPE_1__ ADC_CommonInitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_DMAAccessMode_Disabled ; 
 int /*<<< orphan*/  ADC_Mode_Independent ; 
 int /*<<< orphan*/  ADC_Prescaler_Div2 ; 
 int /*<<< orphan*/  ADC_TwoSamplingDelay_5Cycles ; 

void ADC_CommonStructInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct)
{
  /* Initialize the ADC_Mode member */
  ADC_CommonInitStruct->ADC_Mode = ADC_Mode_Independent;

  /* initialize the ADC_Prescaler member */
  ADC_CommonInitStruct->ADC_Prescaler = ADC_Prescaler_Div2;

  /* Initialize the ADC_DMAAccessMode member */
  ADC_CommonInitStruct->ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;

  /* Initialize the ADC_TwoSamplingDelay member */
  ADC_CommonInitStruct->ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
}