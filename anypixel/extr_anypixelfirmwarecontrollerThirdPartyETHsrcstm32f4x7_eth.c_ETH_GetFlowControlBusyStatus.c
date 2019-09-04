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
typedef  int uint32_t ;
struct TYPE_2__ {int MACFCR; } ;
typedef  scalar_t__ FlagStatus ;

/* Variables and functions */
 TYPE_1__* ETH ; 
 int ETH_MACFCR_FCBBPA ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 

FlagStatus ETH_GetFlowControlBusyStatus(void)
{
  FlagStatus bitstatus = RESET;
  /* The Flow Control register should not be written to until this bit is cleared */
  if ((ETH->MACFCR & ETH_MACFCR_FCBBPA) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}