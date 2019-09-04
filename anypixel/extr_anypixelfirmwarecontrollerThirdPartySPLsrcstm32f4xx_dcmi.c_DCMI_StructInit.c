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
struct TYPE_3__ {int /*<<< orphan*/  DCMI_ExtendedDataMode; int /*<<< orphan*/  DCMI_CaptureRate; int /*<<< orphan*/  DCMI_HSPolarity; int /*<<< orphan*/  DCMI_VSPolarity; int /*<<< orphan*/  DCMI_PCKPolarity; int /*<<< orphan*/  DCMI_SynchroMode; int /*<<< orphan*/  DCMI_CaptureMode; } ;
typedef  TYPE_1__ DCMI_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DCMI_CaptureMode_Continuous ; 
 int /*<<< orphan*/  DCMI_CaptureRate_All_Frame ; 
 int /*<<< orphan*/  DCMI_ExtendedDataMode_8b ; 
 int /*<<< orphan*/  DCMI_HSPolarity_Low ; 
 int /*<<< orphan*/  DCMI_PCKPolarity_Falling ; 
 int /*<<< orphan*/  DCMI_SynchroMode_Hardware ; 
 int /*<<< orphan*/  DCMI_VSPolarity_Low ; 

void DCMI_StructInit(DCMI_InitTypeDef* DCMI_InitStruct)
{
  /* Set the default configuration */
  DCMI_InitStruct->DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
  DCMI_InitStruct->DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  DCMI_InitStruct->DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
  DCMI_InitStruct->DCMI_VSPolarity = DCMI_VSPolarity_Low;
  DCMI_InitStruct->DCMI_HSPolarity = DCMI_HSPolarity_Low;
  DCMI_InitStruct->DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  DCMI_InitStruct->DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
}