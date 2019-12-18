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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int OAR2; } ;
typedef  TYPE_1__ I2C_TypeDef ;

/* Variables and functions */
 scalar_t__ I2C_OAR2_ADD2 ; 
 int /*<<< orphan*/  IS_I2C_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address)
{
  uint16_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Get the old register value */
  tmpreg = I2Cx->OAR2;

  /* Reset I2Cx Own address2 bit [7:1] */
  tmpreg &= (uint16_t)~((uint16_t)I2C_OAR2_ADD2);

  /* Set I2Cx Own address2 */
  tmpreg |= (uint16_t)((uint16_t)Address & (uint16_t)0x00FE);

  /* Store the new register value */
  I2Cx->OAR2 = tmpreg;
}