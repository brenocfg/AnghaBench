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
struct TYPE_2__ {int DMAOMR; } ;
typedef  scalar_t__ FlagStatus ;

/* Variables and functions */
 TYPE_1__* ETH ; 
 int ETH_DMAOMR_FTF ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 

FlagStatus ETH_GetFlushTransmitFIFOStatus(void)
{
  FlagStatus bitstatus = RESET;
  if ((ETH->DMAOMR & ETH_DMAOMR_FTF) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}