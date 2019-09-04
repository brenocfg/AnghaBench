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
struct TYPE_3__ {int /*<<< orphan*/  COMP_Mode; int /*<<< orphan*/  COMP_Hysteresis; int /*<<< orphan*/  COMP_OutputPol; int /*<<< orphan*/  COMP_Output; int /*<<< orphan*/  COMP_InvertingInput; } ;
typedef  TYPE_1__ COMP_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_Hysteresis_No ; 
 int /*<<< orphan*/  COMP_InvertingInput_1_4VREFINT ; 
 int /*<<< orphan*/  COMP_Mode_UltraLowPower ; 
 int /*<<< orphan*/  COMP_OutputPol_NonInverted ; 
 int /*<<< orphan*/  COMP_Output_None ; 

void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct)
{
  COMP_InitStruct->COMP_InvertingInput = COMP_InvertingInput_1_4VREFINT;
  COMP_InitStruct->COMP_Output = COMP_Output_None;
  COMP_InitStruct->COMP_OutputPol = COMP_OutputPol_NonInverted;
  COMP_InitStruct->COMP_Hysteresis = COMP_Hysteresis_No;
  COMP_InitStruct->COMP_Mode = COMP_Mode_UltraLowPower;
}