#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {TYPE_1__* sTxMailBox; scalar_t__ MCR; } ;
struct TYPE_5__ {scalar_t__ TDTR; } ;
typedef  scalar_t__ FunctionalState ;
typedef  TYPE_2__ CAN_TypeDef ;

/* Variables and functions */
 scalar_t__ CAN_MCR_TTCM ; 
 scalar_t__ CAN_TDT0R_TGT ; 
 scalar_t__ CAN_TDT1R_TGT ; 
 scalar_t__ CAN_TDT2R_TGT ; 
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_CAN_ALL_PERIPH (TYPE_2__*) ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CAN_TTComModeCmd(CAN_TypeDef* CANx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the TTCM mode */
    CANx->MCR |= CAN_MCR_TTCM;

    /* Set TGT bits */
    CANx->sTxMailBox[0].TDTR |= ((uint32_t)CAN_TDT0R_TGT);
    CANx->sTxMailBox[1].TDTR |= ((uint32_t)CAN_TDT1R_TGT);
    CANx->sTxMailBox[2].TDTR |= ((uint32_t)CAN_TDT2R_TGT);
  }
  else
  {
    /* Disable the TTCM mode */
    CANx->MCR &= (uint32_t)(~(uint32_t)CAN_MCR_TTCM);

    /* Reset TGT bits */
    CANx->sTxMailBox[0].TDTR &= ((uint32_t)~CAN_TDT0R_TGT);
    CANx->sTxMailBox[1].TDTR &= ((uint32_t)~CAN_TDT1R_TGT);
    CANx->sTxMailBox[2].TDTR &= ((uint32_t)~CAN_TDT2R_TGT);
  }
}