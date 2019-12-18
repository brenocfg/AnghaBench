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
struct TYPE_4__ {scalar_t__ SR1; } ;
typedef  TYPE_1__ I2C_TypeDef ;

/* Variables and functions */
 int FLAG_MASK ; 
 int /*<<< orphan*/  IS_I2C_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_I2C_CLEAR_FLAG (int) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
  uint32_t flagpos = 0;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));
  /* Get the I2C flag position */
  flagpos = I2C_FLAG & FLAG_MASK;
  /* Clear the selected I2C flag */
  I2Cx->SR1 = (uint16_t)~flagpos;
}