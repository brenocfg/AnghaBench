#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  chipcHw_REG_BUS_CLOCK_DMAC0 ; 
 int /*<<< orphan*/  chipcHw_REG_BUS_CLOCK_DMAC1 ; 
 int /*<<< orphan*/  chipcHw_busInterfaceClockDisable (int /*<<< orphan*/ ) ; 

void dmacHw_exitDma(void)
{
	/* Disable access to the DMA block */
	chipcHw_busInterfaceClockDisable(chipcHw_REG_BUS_CLOCK_DMAC0);
	chipcHw_busInterfaceClockDisable(chipcHw_REG_BUS_CLOCK_DMAC1);
}