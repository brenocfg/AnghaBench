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
struct TYPE_3__ {int /*<<< orphan*/  I2C_AcknowledgedAddress; int /*<<< orphan*/  I2C_Ack; scalar_t__ I2C_OwnAddress1; int /*<<< orphan*/  I2C_Mode; scalar_t__ I2C_DigitalFilter; int /*<<< orphan*/  I2C_AnalogFilter; scalar_t__ I2C_Timing; } ;
typedef  TYPE_1__ I2C_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_Ack_Disable ; 
 int /*<<< orphan*/  I2C_AcknowledgedAddress_7bit ; 
 int /*<<< orphan*/  I2C_AnalogFilter_Enable ; 
 int /*<<< orphan*/  I2C_Mode_I2C ; 

void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
  /*---------------- Reset I2C init structure parameters values --------------*/
  /* Initialize the I2C_Timing member */
  I2C_InitStruct->I2C_Timing = 0;
  /* Initialize the I2C_AnalogFilter member */
  I2C_InitStruct->I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  /* Initialize the I2C_DigitalFilter member */
  I2C_InitStruct->I2C_DigitalFilter = 0;
  /* Initialize the I2C_Mode member */
  I2C_InitStruct->I2C_Mode = I2C_Mode_I2C;
  /* Initialize the I2C_OwnAddress1 member */
  I2C_InitStruct->I2C_OwnAddress1 = 0;
  /* Initialize the I2C_Ack member */
  I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
  /* Initialize the I2C_AcknowledgedAddress member */
  I2C_InitStruct->I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
}