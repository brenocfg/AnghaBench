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
struct net_device {scalar_t__ base_addr; } ;

/* Variables and functions */
 scalar_t__ BCMREG ; 
 int BCMREG_IEN ; 
 int /*<<< orphan*/  CMDREG_RST ; 
 scalar_t__ SONIC_CMDREG ; 
 scalar_t__ SONIC_IMREG ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void StopSONIC(struct net_device *dev)
{
	/* disable interrupts */

	outb(inb(dev->base_addr + BCMREG) & (~BCMREG_IEN), dev->base_addr + BCMREG);
	outb(0, dev->base_addr + SONIC_IMREG);

	/* reset the SONIC */

	outw(CMDREG_RST, dev->base_addr + SONIC_CMDREG);
	udelay(10);
	outw(CMDREG_RST, dev->base_addr + SONIC_CMDREG);
}