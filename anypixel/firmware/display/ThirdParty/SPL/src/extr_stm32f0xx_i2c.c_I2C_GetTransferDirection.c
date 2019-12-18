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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int ISR; } ;
typedef  TYPE_1__ I2C_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_Direction_Receiver ; 
 int /*<<< orphan*/  I2C_Direction_Transmitter ; 
 int I2C_ISR_DIR ; 
 int /*<<< orphan*/  IS_I2C_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

uint16_t I2C_GetTransferDirection(I2C_TypeDef* I2Cx)
{
  uint32_t tmpreg = 0;
  uint16_t direction = 0;
  
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Return the slave matched address in the SR1 register */
  tmpreg = (uint32_t)(I2Cx->ISR & I2C_ISR_DIR);
  
  /* If write transfer is requested */
  if (tmpreg == 0)
  {
    /* write transfer is requested */
    direction = I2C_Direction_Transmitter;
  }
  else
  {
    /* Read transfer is requested */
    direction = I2C_Direction_Receiver;
  }  
  return direction;
}