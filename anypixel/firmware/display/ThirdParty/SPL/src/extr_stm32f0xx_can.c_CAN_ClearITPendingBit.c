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
struct TYPE_4__ {int TSR; void* MSR; void* ESR; int /*<<< orphan*/  RF1R; int /*<<< orphan*/  RF0R; } ;
typedef  TYPE_1__ CAN_TypeDef ;

/* Variables and functions */
#define  CAN_IT_BOF 139 
#define  CAN_IT_EPV 138 
#define  CAN_IT_ERR 137 
#define  CAN_IT_EWG 136 
#define  CAN_IT_FF0 135 
#define  CAN_IT_FF1 134 
#define  CAN_IT_FOV0 133 
#define  CAN_IT_FOV1 132 
#define  CAN_IT_LEC 131 
#define  CAN_IT_SLK 130 
#define  CAN_IT_TME 129 
#define  CAN_IT_WKU 128 
 void* CAN_MSR_ERRI ; 
 void* CAN_MSR_SLAKI ; 
 void* CAN_MSR_WKUI ; 
 int /*<<< orphan*/  CAN_RF0R_FOVR0 ; 
 int /*<<< orphan*/  CAN_RF0R_FULL0 ; 
 int /*<<< orphan*/  CAN_RF1R_FOVR1 ; 
 int /*<<< orphan*/  CAN_RF1R_FULL1 ; 
 int CAN_TSR_RQCP0 ; 
 int CAN_TSR_RQCP1 ; 
 int CAN_TSR_RQCP2 ; 
 int /*<<< orphan*/  IS_CAN_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_CAN_CLEAR_IT (int) ; 
 void* RESET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_CLEAR_IT(CAN_IT));

  switch (CAN_IT)
  {
    case CAN_IT_TME:
      /* Clear CAN_TSR_RQCPx (rc_w1)*/
      CANx->TSR = CAN_TSR_RQCP0|CAN_TSR_RQCP1|CAN_TSR_RQCP2;  
      break;
    case CAN_IT_FF0:
      /* Clear CAN_RF0R_FULL0 (rc_w1)*/
      CANx->RF0R = CAN_RF0R_FULL0; 
      break;
    case CAN_IT_FOV0:
      /* Clear CAN_RF0R_FOVR0 (rc_w1)*/
      CANx->RF0R = CAN_RF0R_FOVR0; 
      break;
    case CAN_IT_FF1:
      /* Clear CAN_RF1R_FULL1 (rc_w1)*/
      CANx->RF1R = CAN_RF1R_FULL1;  
      break;
    case CAN_IT_FOV1:
      /* Clear CAN_RF1R_FOVR1 (rc_w1)*/
      CANx->RF1R = CAN_RF1R_FOVR1; 
      break;
    case CAN_IT_WKU:
      /* Clear CAN_MSR_WKUI (rc_w1)*/
      CANx->MSR = CAN_MSR_WKUI;  
      break;
    case CAN_IT_SLK:
      /* Clear CAN_MSR_SLAKI (rc_w1)*/ 
      CANx->MSR = CAN_MSR_SLAKI;   
      break;
    case CAN_IT_EWG:
      /* Clear CAN_MSR_ERRI (rc_w1) */
      CANx->MSR = CAN_MSR_ERRI;
       /* @note the corresponding Flag is cleared by hardware depending on the CAN Bus status*/ 
      break;
    case CAN_IT_EPV:
      /* Clear CAN_MSR_ERRI (rc_w1) */
      CANx->MSR = CAN_MSR_ERRI; 
       /* @note the corresponding Flag is cleared by hardware depending on the CAN Bus status*/
      break;
    case CAN_IT_BOF:
      /* Clear CAN_MSR_ERRI (rc_w1) */ 
      CANx->MSR = CAN_MSR_ERRI; 
       /* @note the corresponding Flag is cleared by hardware depending on the CAN Bus status*/
       break;
    case CAN_IT_LEC:
      /*  Clear LEC bits */
      CANx->ESR = RESET; 
      /* Clear CAN_MSR_ERRI (rc_w1) */
      CANx->MSR = CAN_MSR_ERRI; 
      break;
    case CAN_IT_ERR:
      /*Clear LEC bits */
      CANx->ESR = RESET; 
      /* Clear CAN_MSR_ERRI (rc_w1) */
      CANx->MSR = CAN_MSR_ERRI; 
       /* @note BOFF, EPVF and EWGF Flags are cleared by hardware depending on the CAN Bus status*/
       break;
    default:
       break;
   }
}