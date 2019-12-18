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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  CR1; } ;
typedef  TYPE_1__ I2C_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_NACKPosition_Current ; 
 int /*<<< orphan*/  I2C_NACKPosition_Next ; 
 int /*<<< orphan*/  IS_I2C_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_I2C_NACK_POSITION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void I2C_NACKPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_NACKPosition)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_NACK_POSITION(I2C_NACKPosition));
  
  /* Check the input parameter */
  if (I2C_NACKPosition == I2C_NACKPosition_Next)
  {
    /* Next byte in shift register is the last received byte */
    I2Cx->CR1 |= I2C_NACKPosition_Next;
  }
  else
  {
    /* Current byte in shift register is the last received byte */
    I2Cx->CR1 &= I2C_NACKPosition_Current;
  }
}