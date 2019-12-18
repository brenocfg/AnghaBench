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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int SMPR1; int SMPR2; int SQR3; int SQR2; int SQR1; } ;
typedef  TYPE_1__ ADC_TypeDef ;

/* Variables and functions */
 int ADC_Channel_9 ; 
 int /*<<< orphan*/  IS_ADC_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_ADC_CHANNEL (int) ; 
 int /*<<< orphan*/  IS_ADC_REGULAR_RANK (int) ; 
 int /*<<< orphan*/  IS_ADC_SAMPLE_TIME (int) ; 
 int SMPR1_SMP_SET ; 
 int SMPR2_SMP_SET ; 
 int SQR1_SQ_SET ; 
 int SQR2_SQ_SET ; 
 int SQR3_SQ_SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_REGULAR_RANK(Rank));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));
  
  /* if ADC_Channel_10 ... ADC_Channel_18 is selected */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR1;
    
    /* Calculate the mask to clear */
    tmpreg2 = SMPR1_SMP_SET << (3 * (ADC_Channel - 10));
    
    /* Clear the old sample time */
    tmpreg1 &= ~tmpreg2;
    
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
    
    /* Set the new sample time */
    tmpreg1 |= tmpreg2;
    
    /* Store the new register value */
    ADCx->SMPR1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR2;
    
    /* Calculate the mask to clear */
    tmpreg2 = SMPR2_SMP_SET << (3 * ADC_Channel);
    
    /* Clear the old sample time */
    tmpreg1 &= ~tmpreg2;
    
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
    
    /* Set the new sample time */
    tmpreg1 |= tmpreg2;
    
    /* Store the new register value */
    ADCx->SMPR2 = tmpreg1;
  }
  /* For Rank 1 to 6 */
  if (Rank < 7)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR3;
    
    /* Calculate the mask to clear */
    tmpreg2 = SQR3_SQ_SET << (5 * (Rank - 1));
    
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));
    
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    
    /* Store the new register value */
    ADCx->SQR3 = tmpreg1;
  }
  /* For Rank 7 to 12 */
  else if (Rank < 13)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR2;
    
    /* Calculate the mask to clear */
    tmpreg2 = SQR2_SQ_SET << (5 * (Rank - 7));
    
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));
    
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    
    /* Store the new register value */
    ADCx->SQR2 = tmpreg1;
  }
  /* For Rank 13 to 16 */
  else
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR1;
    
    /* Calculate the mask to clear */
    tmpreg2 = SQR1_SQ_SET << (5 * (Rank - 13));
    
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));
    
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    
    /* Store the new register value */
    ADCx->SQR1 = tmpreg1;
  }
}