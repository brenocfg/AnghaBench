#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int CAN_Prescaler; int /*<<< orphan*/  CAN_BS2; int /*<<< orphan*/  CAN_BS1; int /*<<< orphan*/  CAN_SJW; int /*<<< orphan*/  CAN_Mode; void* CAN_TXFP; void* CAN_RFLM; void* CAN_NART; void* CAN_AWUM; void* CAN_ABOM; void* CAN_TTCM; } ;
typedef  TYPE_1__ CAN_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_BS1_4tq ; 
 int /*<<< orphan*/  CAN_BS2_3tq ; 
 int /*<<< orphan*/  CAN_Mode_Normal ; 
 int /*<<< orphan*/  CAN_SJW_1tq ; 
 void* DISABLE ; 

void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct)
{
  /* Reset CAN init structure parameters values */
  
  /* Initialize the time triggered communication mode */
  CAN_InitStruct->CAN_TTCM = DISABLE;
  
  /* Initialize the automatic bus-off management */
  CAN_InitStruct->CAN_ABOM = DISABLE;
  
  /* Initialize the automatic wake-up mode */
  CAN_InitStruct->CAN_AWUM = DISABLE;
  
  /* Initialize the no automatic retransmission */
  CAN_InitStruct->CAN_NART = DISABLE;
  
  /* Initialize the receive FIFO locked mode */
  CAN_InitStruct->CAN_RFLM = DISABLE;
  
  /* Initialize the transmit FIFO priority */
  CAN_InitStruct->CAN_TXFP = DISABLE;
  
  /* Initialize the CAN_Mode member */
  CAN_InitStruct->CAN_Mode = CAN_Mode_Normal;
  
  /* Initialize the CAN_SJW member */
  CAN_InitStruct->CAN_SJW = CAN_SJW_1tq;
  
  /* Initialize the CAN_BS1 member */
  CAN_InitStruct->CAN_BS1 = CAN_BS1_4tq;
  
  /* Initialize the CAN_BS2 member */
  CAN_InitStruct->CAN_BS2 = CAN_BS2_3tq;
  
  /* Initialize the CAN_Prescaler member */
  CAN_InitStruct->CAN_Prescaler = 1;
}