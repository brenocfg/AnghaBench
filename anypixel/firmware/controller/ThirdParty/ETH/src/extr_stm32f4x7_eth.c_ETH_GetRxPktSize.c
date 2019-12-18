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
struct TYPE_4__ {int Status; } ;
typedef  TYPE_1__ ETH_DMADESCTypeDef ;

/* Variables and functions */
 int ETH_DMARxDesc_ES ; 
 int ETH_DMARxDesc_LS ; 
 int ETH_DMARxDesc_OWN ; 
 int ETH_GetDMARxDescFrameLength (TYPE_1__*) ; 
 scalar_t__ RESET ; 

uint32_t ETH_GetRxPktSize(ETH_DMADESCTypeDef *DMARxDesc)
{
  uint32_t frameLength = 0;
  if(((DMARxDesc->Status & ETH_DMARxDesc_OWN) == (uint32_t)RESET) &&
     ((DMARxDesc->Status & ETH_DMARxDesc_ES) == (uint32_t)RESET) &&
       ((DMARxDesc->Status & ETH_DMARxDesc_LS) != (uint32_t)RESET))
  {
    /* Get the size of the packet: including 4 bytes of the CRC */
    frameLength =  ETH_GetDMARxDescFrameLength(DMARxDesc);
  }

  /* Return Frame Length */
  return frameLength;
}