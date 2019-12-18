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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ PECR; } ;
typedef  TYPE_1__ I2C_TypeDef ;

/* Variables and functions */
 int I2C_PECR_PEC ; 
 int /*<<< orphan*/  IS_I2C_1_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_1_PERIPH(I2Cx));
  
  /* Return the slave matched address in the SR1 register */
  return (uint8_t)((uint32_t)I2Cx->PECR & I2C_PECR_PEC);
}