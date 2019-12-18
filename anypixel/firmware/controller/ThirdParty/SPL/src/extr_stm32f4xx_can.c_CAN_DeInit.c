#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  CAN_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/ * CAN1 ; 
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  IS_CAN_ALL_PERIPH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCC_APB1PeriphResetCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB1Periph_CAN1 ; 
 int /*<<< orphan*/  RCC_APB1Periph_CAN2 ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CAN_DeInit(CAN_TypeDef* CANx)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
 
  if (CANx == CAN1)
  {
    /* Enable CAN1 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN1, ENABLE);
    /* Release CAN1 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN1, DISABLE);
  }
  else
  {  
    /* Enable CAN2 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, ENABLE);
    /* Release CAN2 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, DISABLE);
  }
}