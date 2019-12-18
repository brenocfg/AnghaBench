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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int OAR2; } ;
typedef  TYPE_1__ I2C_TypeDef ;

/* Variables and functions */
 int I2C_OAR2_OA2 ; 
 int I2C_OAR2_OA2MSK ; 
 int /*<<< orphan*/  IS_I2C_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_I2C_OWN_ADDRESS2 (scalar_t__) ; 
 int /*<<< orphan*/  IS_I2C_OWN_ADDRESS2_MASK (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Mask)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_OWN_ADDRESS2(Address));
  assert_param(IS_I2C_OWN_ADDRESS2_MASK(Mask));
  
  /* Get the old register value */
  tmpreg = I2Cx->OAR2;

  /* Reset I2Cx OA2 bit [7:1] and OA2MSK bit [1:0]  */
  tmpreg &= (uint32_t)~((uint32_t)(I2C_OAR2_OA2 | I2C_OAR2_OA2MSK));

  /* Set I2Cx SADD */
  tmpreg |= (uint32_t)(((uint32_t)Address & I2C_OAR2_OA2) | \
            (((uint32_t)Mask << 8) & I2C_OAR2_OA2MSK)) ;

  /* Store the new register value */
  I2Cx->OAR2 = tmpreg;
}