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
typedef  int u32 ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_IOCTL ; 
 int /*<<< orphan*/  BCMA_RESET_CTL ; 
 int BCMA_RESET_CTL_RESET ; 
 int bcma_aread32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_awrite32 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void bcma_core_disable(struct bcma_device *core, u32 flags)
{
	if (bcma_aread32(core, BCMA_RESET_CTL) & BCMA_RESET_CTL_RESET)
		return;

	bcma_awrite32(core, BCMA_IOCTL, flags);
	bcma_aread32(core, BCMA_IOCTL);
	udelay(10);

	bcma_awrite32(core, BCMA_RESET_CTL, BCMA_RESET_CTL_RESET);
	bcma_aread32(core, BCMA_RESET_CTL);
	udelay(1);
}