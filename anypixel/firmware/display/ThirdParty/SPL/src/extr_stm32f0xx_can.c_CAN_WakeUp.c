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
struct TYPE_4__ {int MCR; int MSR; } ;
typedef  TYPE_1__ CAN_TypeDef ;

/* Variables and functions */
 scalar_t__ CAN_MCR_SLEEP ; 
 int CAN_MSR_SLAK ; 
 int /*<<< orphan*/  CAN_WakeUp_Failed ; 
 int /*<<< orphan*/  CAN_WakeUp_Ok ; 
 int /*<<< orphan*/  IS_CAN_ALL_PERIPH (TYPE_1__*) ; 
 int SLAK_TIMEOUT ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

uint8_t CAN_WakeUp(CAN_TypeDef* CANx)
{
  uint32_t wait_slak = SLAK_TIMEOUT;
  uint8_t wakeupstatus = CAN_WakeUp_Failed;
  
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
    
  /* Wake up request */
  CANx->MCR &= ~(uint32_t)CAN_MCR_SLEEP;
    
  /* Sleep mode status */
  while(((CANx->MSR & CAN_MSR_SLAK) == CAN_MSR_SLAK)&&(wait_slak!=0x00))
  {
   wait_slak--;
  }
  if((CANx->MSR & CAN_MSR_SLAK) != CAN_MSR_SLAK)
  {
   /* wake up done : Sleep mode exited */
    wakeupstatus = CAN_WakeUp_Ok;
  }
  /* return wakeup status */
  return (uint8_t)wakeupstatus;
}