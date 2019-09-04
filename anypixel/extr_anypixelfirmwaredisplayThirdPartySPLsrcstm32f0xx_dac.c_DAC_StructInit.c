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
struct TYPE_3__ {int /*<<< orphan*/  DAC_OutputBuffer; int /*<<< orphan*/  DAC_LFSRUnmask_TriangleAmplitude; int /*<<< orphan*/  DAC_WaveGeneration; int /*<<< orphan*/  DAC_Trigger; } ;
typedef  TYPE_1__ DAC_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_LFSRUnmask_Bit0 ; 
 int /*<<< orphan*/  DAC_OutputBuffer_Enable ; 
 int /*<<< orphan*/  DAC_Trigger_None ; 
 int /*<<< orphan*/  DAC_WaveGeneration_None ; 

void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
/*--------------- Reset DAC init structure parameters values -----------------*/
  /* Initialize the DAC_Trigger member */
  DAC_InitStruct->DAC_Trigger = DAC_Trigger_None;
  
  /* Initialize the DAC_WaveGeneration member */
  DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;
  
  /* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */
  DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
  
  /* Initialize the DAC_OutputBuffer member */
  DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Enable;
}