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
struct TYPE_3__ {int ADC_NbrOfConversion; int /*<<< orphan*/  ADC_DataAlign; int /*<<< orphan*/  ADC_ExternalTrigConv; int /*<<< orphan*/  ADC_ExternalTrigConvEdge; void* ADC_ContinuousConvMode; void* ADC_ScanConvMode; int /*<<< orphan*/  ADC_Resolution; } ;
typedef  TYPE_1__ ADC_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_DataAlign_Right ; 
 int /*<<< orphan*/  ADC_ExternalTrigConvEdge_None ; 
 int /*<<< orphan*/  ADC_ExternalTrigConv_T1_CC1 ; 
 int /*<<< orphan*/  ADC_Resolution_12b ; 
 void* DISABLE ; 

void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
  /* Initialize the ADC_Mode member */
  ADC_InitStruct->ADC_Resolution = ADC_Resolution_12b;

  /* initialize the ADC_ScanConvMode member */
  ADC_InitStruct->ADC_ScanConvMode = DISABLE;

  /* Initialize the ADC_ContinuousConvMode member */
  ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;

  /* Initialize the ADC_ExternalTrigConvEdge member */
  ADC_InitStruct->ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;

  /* Initialize the ADC_ExternalTrigConv member */
  ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;

  /* Initialize the ADC_DataAlign member */
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;

  /* Initialize the ADC_NbrOfConversion member */
  ADC_InitStruct->ADC_NbrOfConversion = 1;
}