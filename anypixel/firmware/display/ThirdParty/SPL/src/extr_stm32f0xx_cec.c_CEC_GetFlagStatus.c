#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_2__ {int ISR; } ;
typedef  scalar_t__ FlagStatus ;

/* Variables and functions */
 TYPE_1__* CEC ; 
 int /*<<< orphan*/  IS_CEC_GET_FLAG (int) ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

FlagStatus CEC_GetFlagStatus(uint16_t CEC_FLAG) 
{
  FlagStatus bitstatus = RESET;
  
  assert_param(IS_CEC_GET_FLAG(CEC_FLAG));
  
  /* Check the status of the specified CEC flag */
  if ((CEC->ISR & CEC_FLAG) != (uint16_t)RESET)
  {
    /* CEC flag is set */
    bitstatus = SET;
  }
  else
  {
    /* CEC flag is reset */
    bitstatus = RESET;
  }

  /* Return the CEC flag status */
  return  bitstatus;
}