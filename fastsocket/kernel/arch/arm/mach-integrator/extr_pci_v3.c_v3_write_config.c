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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  __raw_readb (unsigned long) ; 
 int /*<<< orphan*/  __raw_readl (unsigned long) ; 
 int /*<<< orphan*/  __raw_readw (unsigned long) ; 
 int /*<<< orphan*/  __raw_writeb (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v3_close_config_window () ; 
 int /*<<< orphan*/  v3_lock ; 
 unsigned long v3_open_config_window (struct pci_bus*,unsigned int,int) ; 

__attribute__((used)) static int v3_write_config(struct pci_bus *bus, unsigned int devfn, int where,
			   int size, u32 val)
{
	unsigned long addr;
	unsigned long flags;

	spin_lock_irqsave(&v3_lock, flags);
	addr = v3_open_config_window(bus, devfn, where);

	switch (size) {
	case 1:
		__raw_writeb((u8)val, addr);
		__raw_readb(addr);
		break;

	case 2:
		__raw_writew((u16)val, addr);
		__raw_readw(addr);
		break;

	case 4:
		__raw_writel(val, addr);
		__raw_readl(addr);
		break;
	}

	v3_close_config_window();
	spin_unlock_irqrestore(&v3_lock, flags);

	return PCIBIOS_SUCCESSFUL;
}