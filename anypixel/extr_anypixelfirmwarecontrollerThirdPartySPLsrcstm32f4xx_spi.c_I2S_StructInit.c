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
struct TYPE_3__ {int /*<<< orphan*/  I2S_CPOL; int /*<<< orphan*/  I2S_AudioFreq; int /*<<< orphan*/  I2S_MCLKOutput; int /*<<< orphan*/  I2S_DataFormat; int /*<<< orphan*/  I2S_Standard; int /*<<< orphan*/  I2S_Mode; } ;
typedef  TYPE_1__ I2S_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  I2S_AudioFreq_Default ; 
 int /*<<< orphan*/  I2S_CPOL_Low ; 
 int /*<<< orphan*/  I2S_DataFormat_16b ; 
 int /*<<< orphan*/  I2S_MCLKOutput_Disable ; 
 int /*<<< orphan*/  I2S_Mode_SlaveTx ; 
 int /*<<< orphan*/  I2S_Standard_Phillips ; 

void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct)
{
/*--------------- Reset I2S init structure parameters values -----------------*/
  /* Initialize the I2S_Mode member */
  I2S_InitStruct->I2S_Mode = I2S_Mode_SlaveTx;
  
  /* Initialize the I2S_Standard member */
  I2S_InitStruct->I2S_Standard = I2S_Standard_Phillips;
  
  /* Initialize the I2S_DataFormat member */
  I2S_InitStruct->I2S_DataFormat = I2S_DataFormat_16b;
  
  /* Initialize the I2S_MCLKOutput member */
  I2S_InitStruct->I2S_MCLKOutput = I2S_MCLKOutput_Disable;
  
  /* Initialize the I2S_AudioFreq member */
  I2S_InitStruct->I2S_AudioFreq = I2S_AudioFreq_Default;
  
  /* Initialize the I2S_CPOL member */
  I2S_InitStruct->I2S_CPOL = I2S_CPOL_Low;
}