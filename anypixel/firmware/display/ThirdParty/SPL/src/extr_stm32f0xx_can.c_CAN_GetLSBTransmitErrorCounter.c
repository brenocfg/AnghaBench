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
struct TYPE_4__ {int ESR; } ;
typedef  TYPE_1__ CAN_TypeDef ;

/* Variables and functions */
 int CAN_ESR_TEC ; 
 int /*<<< orphan*/  IS_CAN_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

uint8_t CAN_GetLSBTransmitErrorCounter(CAN_TypeDef* CANx)
{
  uint8_t counter=0;
  
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  
  /* Get the LSB of the 9-bit CANx Transmit Error Counter(TEC) */
  counter = (uint8_t)((CANx->ESR & CAN_ESR_TEC)>> 16);
  
  /* Return the LSB of the 9-bit CANx Transmit Error Counter(TEC) */
  return counter;
}