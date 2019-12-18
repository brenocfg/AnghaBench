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
struct TYPE_4__ {int /*<<< orphan*/  MCR; } ;
typedef  scalar_t__ FunctionalState ;
typedef  TYPE_1__ CAN_TypeDef ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_CAN_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  MCR_DBF ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CAN_DBGFreeze(CAN_TypeDef* CANx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Debug Freeze  */
    CANx->MCR |= MCR_DBF;
  }
  else
  {
    /* Disable Debug Freeze */
    CANx->MCR &= ~MCR_DBF;
  }
}