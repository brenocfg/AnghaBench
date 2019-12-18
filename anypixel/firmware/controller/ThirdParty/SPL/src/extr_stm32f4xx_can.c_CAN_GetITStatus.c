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
struct TYPE_4__ {int IER; int /*<<< orphan*/  MSR; int /*<<< orphan*/  ESR; int /*<<< orphan*/  RF1R; int /*<<< orphan*/  RF0R; int /*<<< orphan*/  TSR; } ;
typedef  int ITStatus ;
typedef  TYPE_1__ CAN_TypeDef ;

/* Variables and functions */
 int CAN_ESR_BOFF ; 
 int CAN_ESR_EPVF ; 
 int CAN_ESR_EWGF ; 
 int CAN_ESR_LEC ; 
#define  CAN_IT_BOF 141 
#define  CAN_IT_EPV 140 
#define  CAN_IT_ERR 139 
#define  CAN_IT_EWG 138 
#define  CAN_IT_FF0 137 
#define  CAN_IT_FF1 136 
#define  CAN_IT_FMP0 135 
#define  CAN_IT_FMP1 134 
#define  CAN_IT_FOV0 133 
#define  CAN_IT_FOV1 132 
#define  CAN_IT_LEC 131 
#define  CAN_IT_SLK 130 
#define  CAN_IT_TME 129 
#define  CAN_IT_WKU 128 
 int CAN_MSR_ERRI ; 
 int CAN_MSR_SLAKI ; 
 int CAN_MSR_WKUI ; 
 int CAN_RF0R_FMP0 ; 
 int CAN_RF0R_FOVR0 ; 
 int CAN_RF0R_FULL0 ; 
 int CAN_RF1R_FMP1 ; 
 int CAN_RF1R_FOVR1 ; 
 int CAN_RF1R_FULL1 ; 
 int CAN_TSR_RQCP0 ; 
 int CAN_TSR_RQCP1 ; 
 int CAN_TSR_RQCP2 ; 
 int CheckITStatus (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IS_CAN_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_CAN_IT (int) ; 
 int RESET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT)
{
  ITStatus itstatus = RESET;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_IT(CAN_IT));
  
  /* check the interrupt enable bit */
 if((CANx->IER & CAN_IT) != RESET)
 {
   /* in case the Interrupt is enabled, .... */
    switch (CAN_IT)
    {
      case CAN_IT_TME:
        /* Check CAN_TSR_RQCPx bits */
        itstatus = CheckITStatus(CANx->TSR, CAN_TSR_RQCP0|CAN_TSR_RQCP1|CAN_TSR_RQCP2);  
        break;
      case CAN_IT_FMP0:
        /* Check CAN_RF0R_FMP0 bit */
        itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FMP0);  
        break;
      case CAN_IT_FF0:
        /* Check CAN_RF0R_FULL0 bit */
        itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FULL0);  
        break;
      case CAN_IT_FOV0:
        /* Check CAN_RF0R_FOVR0 bit */
        itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FOVR0);  
        break;
      case CAN_IT_FMP1:
        /* Check CAN_RF1R_FMP1 bit */
        itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FMP1);  
        break;
      case CAN_IT_FF1:
        /* Check CAN_RF1R_FULL1 bit */
        itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FULL1);  
        break;
      case CAN_IT_FOV1:
        /* Check CAN_RF1R_FOVR1 bit */
        itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FOVR1);  
        break;
      case CAN_IT_WKU:
        /* Check CAN_MSR_WKUI bit */
        itstatus = CheckITStatus(CANx->MSR, CAN_MSR_WKUI);  
        break;
      case CAN_IT_SLK:
        /* Check CAN_MSR_SLAKI bit */
        itstatus = CheckITStatus(CANx->MSR, CAN_MSR_SLAKI);  
        break;
      case CAN_IT_EWG:
        /* Check CAN_ESR_EWGF bit */
        itstatus = CheckITStatus(CANx->ESR, CAN_ESR_EWGF);  
        break;
      case CAN_IT_EPV:
        /* Check CAN_ESR_EPVF bit */
        itstatus = CheckITStatus(CANx->ESR, CAN_ESR_EPVF);  
        break;
      case CAN_IT_BOF:
        /* Check CAN_ESR_BOFF bit */
        itstatus = CheckITStatus(CANx->ESR, CAN_ESR_BOFF);  
        break;
      case CAN_IT_LEC:
        /* Check CAN_ESR_LEC bit */
        itstatus = CheckITStatus(CANx->ESR, CAN_ESR_LEC);  
        break;
      case CAN_IT_ERR:
        /* Check CAN_MSR_ERRI bit */ 
        itstatus = CheckITStatus(CANx->MSR, CAN_MSR_ERRI); 
        break;
      default:
        /* in case of error, return RESET */
        itstatus = RESET;
        break;
    }
  }
  else
  {
   /* in case the Interrupt is not enabled, return RESET */
    itstatus  = RESET;
  }
  
  /* Return the CAN_IT status */
  return  itstatus;
}