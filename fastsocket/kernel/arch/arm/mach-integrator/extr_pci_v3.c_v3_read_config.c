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
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  __raw_readb (unsigned long) ; 
 int /*<<< orphan*/  __raw_readl (unsigned long) ; 
 int /*<<< orphan*/  __raw_readw (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v3_close_config_window () ; 
 int /*<<< orphan*/  v3_lock ; 
 unsigned long v3_open_config_window (struct pci_bus*,unsigned int,int) ; 

__attribute__((used)) static int v3_read_config(struct pci_bus *bus, unsigned int devfn, int where,
			  int size, u32 *val)
{
	unsigned long addr;
	unsigned long flags;
	u32 v;

	spin_lock_irqsave(&v3_lock, flags);
	addr = v3_open_config_window(bus, devfn, where);

	switch (size) {
	case 1:
		v = __raw_readb(addr);
		break;

	case 2:
		v = __raw_readw(addr);
		break;

	default:
		v = __raw_readl(addr);
		break;
	}

	v3_close_config_window();
	spin_unlock_irqrestore(&v3_lock, flags);

	*val = v;
	return PCIBIOS_SUCCESSFUL;
}