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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ MCR; int MSR; } ;
typedef  TYPE_1__ CAN_TypeDef ;

/* Variables and functions */
 scalar_t__ CAN_MCR_INRQ ; 
 scalar_t__ CAN_MCR_SLEEP ; 
 int CAN_MODE_MASK ; 
 int CAN_MSR_INAK ; 
 int CAN_MSR_SLAK ; 
 scalar_t__ CAN_ModeStatus_Failed ; 
 scalar_t__ CAN_ModeStatus_Success ; 
 scalar_t__ CAN_OperatingMode_Initialization ; 
 scalar_t__ CAN_OperatingMode_Normal ; 
 scalar_t__ CAN_OperatingMode_Sleep ; 
 scalar_t__ INAK_TIMEOUT ; 
 int /*<<< orphan*/  IS_CAN_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_CAN_OPERATING_MODE (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

uint8_t CAN_OperatingModeRequest(CAN_TypeDef* CANx, uint8_t CAN_OperatingMode)
{
  uint8_t status = CAN_ModeStatus_Failed;
  
  /* Timeout for INAK or also for SLAK bits*/
  uint32_t timeout = INAK_TIMEOUT; 

  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_OPERATING_MODE(CAN_OperatingMode));

  if (CAN_OperatingMode == CAN_OperatingMode_Initialization)
  {
    /* Request initialisation */
    CANx->MCR = (uint32_t)((CANx->MCR & (uint32_t)(~(uint32_t)CAN_MCR_SLEEP)) | CAN_MCR_INRQ);

    /* Wait the acknowledge */
    while (((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_INAK) && (timeout != 0))
    {
      timeout--;
    }
    if ((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_INAK)
    {
      status = CAN_ModeStatus_Failed;
    }
    else
    {
      status = CAN_ModeStatus_Success;
    }
  }
  else  if (CAN_OperatingMode == CAN_OperatingMode_Normal)
  {
    /* Request leave initialisation and sleep mode  and enter Normal mode */
    CANx->MCR &= (uint32_t)(~(CAN_MCR_SLEEP|CAN_MCR_INRQ));

    /* Wait the acknowledge */
    while (((CANx->MSR & CAN_MODE_MASK) != 0) && (timeout!=0))
    {
      timeout--;
    }
    if ((CANx->MSR & CAN_MODE_MASK) != 0)
    {
      status = CAN_ModeStatus_Failed;
    }
    else
    {
      status = CAN_ModeStatus_Success;
    }
  }
  else  if (CAN_OperatingMode == CAN_OperatingMode_Sleep)
  {
    /* Request Sleep mode */
    CANx->MCR = (uint32_t)((CANx->MCR & (uint32_t)(~(uint32_t)CAN_MCR_INRQ)) | CAN_MCR_SLEEP);

    /* Wait the acknowledge */
    while (((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_SLAK) && (timeout!=0))
    {
      timeout--;
    }
    if ((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_SLAK)
    {
      status = CAN_ModeStatus_Failed;
    }
    else
    {
      status = CAN_ModeStatus_Success;
    }
  }
  else
  {
    status = CAN_ModeStatus_Failed;
  }

  return  (uint8_t) status;
}