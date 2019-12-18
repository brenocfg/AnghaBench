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
struct pci_channel {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SH4A_PCIEINTR ; 
 unsigned int pci_read_reg (struct pci_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pci_wait_for_irq(struct pci_channel *chan, unsigned int mask)
{
	unsigned int timeout = 100;

	while (timeout--) {
		if ((pci_read_reg(chan, SH4A_PCIEINTR) & mask) == mask)
			return 0;

		udelay(100);
	}

	return -ETIMEDOUT;
}