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
struct TYPE_4__ {int ESR; int RF0R; int RF1R; int TSR; int MSR; } ;
typedef  TYPE_1__ CAN_TypeDef ;

/* Variables and functions */
 int CAN_FLAGS_RF0R ; 
 int CAN_FLAGS_RF1R ; 
 int CAN_FLAGS_TSR ; 
 int CAN_FLAG_LEC ; 
 int /*<<< orphan*/  IS_CAN_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_CAN_CLEAR_FLAG (int) ; 
 scalar_t__ RESET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CAN_ClearFlag(CAN_TypeDef* CANx, uint32_t CAN_FLAG)
{
  uint32_t flagtmp=0;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_CLEAR_FLAG(CAN_FLAG));
  
  if (CAN_FLAG == CAN_FLAG_LEC) /* ESR register */
  {
    /* Clear the selected CAN flags */
    CANx->ESR = (uint32_t)RESET;
  }
  else /* MSR or TSR or RF0R or RF1R */
  {
    flagtmp = CAN_FLAG & 0x000FFFFF;

    if ((CAN_FLAG & CAN_FLAGS_RF0R)!=(uint32_t)RESET)
    {
      /* Receive Flags */
      CANx->RF0R = (uint32_t)(flagtmp);
    }
    else if ((CAN_FLAG & CAN_FLAGS_RF1R)!=(uint32_t)RESET)
    {
      /* Receive Flags */
      CANx->RF1R = (uint32_t)(flagtmp);
    }
    else if ((CAN_FLAG & CAN_FLAGS_TSR)!=(uint32_t)RESET)
    {
      /* Transmit Flags */
      CANx->TSR = (uint32_t)(flagtmp);
    }
    else /* If((CAN_FLAG & CAN_FLAGS_MSR)!=(uint32_t)RESET) */
    {
      /* Operating mode Flags */
      CANx->MSR = (uint32_t)(flagtmp);
    }
  }
}