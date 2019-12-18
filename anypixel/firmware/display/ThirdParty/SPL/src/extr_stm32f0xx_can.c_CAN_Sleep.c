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
 scalar_t__ CAN_MCR_INRQ ; 
 int CAN_MCR_SLEEP ; 
 int CAN_MSR_INAK ; 
 int CAN_MSR_SLAK ; 
 int /*<<< orphan*/  CAN_Sleep_Failed ; 
 int /*<<< orphan*/  CAN_Sleep_Ok ; 
 int /*<<< orphan*/  IS_CAN_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

uint8_t CAN_Sleep(CAN_TypeDef* CANx)
{
  uint8_t sleepstatus = CAN_Sleep_Failed;
  
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
    
  /* Request Sleep mode */
   CANx->MCR = (((CANx->MCR) & (uint32_t)(~(uint32_t)CAN_MCR_INRQ)) | CAN_MCR_SLEEP);
   
  /* Sleep mode status */
  if ((CANx->MSR & (CAN_MSR_SLAK|CAN_MSR_INAK)) == CAN_MSR_SLAK)
  {
    /* Sleep mode not entered */
    sleepstatus =  CAN_Sleep_Ok;
  }
  /* return sleep mode status */
   return (uint8_t)sleepstatus;
}