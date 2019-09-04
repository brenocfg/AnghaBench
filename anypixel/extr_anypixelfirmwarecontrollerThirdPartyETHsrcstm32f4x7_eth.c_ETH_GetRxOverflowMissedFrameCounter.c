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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int DMAMFBOCR; } ;

/* Variables and functions */
 TYPE_1__* ETH ; 
 int ETH_DMAMFBOCR_MFA ; 
 int ETH_DMA_RX_OVERFLOW_MISSEDFRAMES_COUNTERSHIFT ; 

uint32_t ETH_GetRxOverflowMissedFrameCounter(void)
{
  return ((uint32_t)((ETH->DMAMFBOCR & ETH_DMAMFBOCR_MFA)>>ETH_DMA_RX_OVERFLOW_MISSEDFRAMES_COUNTERSHIFT));
}