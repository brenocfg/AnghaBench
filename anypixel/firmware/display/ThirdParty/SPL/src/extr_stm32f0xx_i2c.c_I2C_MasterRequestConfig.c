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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ CR2; } ;
typedef  TYPE_1__ I2C_TypeDef ;

/* Variables and functions */
 scalar_t__ I2C_CR2_RD_WRN ; 
 scalar_t__ I2C_Direction_Transmitter ; 
 int /*<<< orphan*/  IS_I2C_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_I2C_DIRECTION (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void I2C_MasterRequestConfig(I2C_TypeDef* I2Cx, uint16_t I2C_Direction)
{
/* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DIRECTION(I2C_Direction));
  
  /* Test on the direction to set/reset the read/write bit */
  if (I2C_Direction == I2C_Direction_Transmitter)
  {
    /* Request a write Transfer */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_RD_WRN);
  }
  else
  {
    /* Request a read Transfer */
    I2Cx->CR2 |= I2C_CR2_RD_WRN;
  }
}