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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int CR2; } ;
typedef  TYPE_1__ I2C_TypeDef ;

/* Variables and functions */
 int I2C_CR2_SADD ; 
 int /*<<< orphan*/  IS_I2C_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_I2C_SLAVE_ADDRESS (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void I2C_SlaveAddressConfig(I2C_TypeDef* I2Cx, uint16_t Address)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_SLAVE_ADDRESS(Address));
               
  /* Get the old register value */
  tmpreg = I2Cx->CR2;

  /* Reset I2Cx SADD bit [9:0] */
  tmpreg &= (uint32_t)~((uint32_t)I2C_CR2_SADD);

  /* Set I2Cx SADD */
  tmpreg |= (uint32_t)((uint32_t)Address & I2C_CR2_SADD);

  /* Store the new register value */
  I2Cx->CR2 = tmpreg;
}