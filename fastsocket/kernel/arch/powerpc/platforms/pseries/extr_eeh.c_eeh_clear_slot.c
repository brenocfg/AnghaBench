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
struct device_node {struct device_node* parent; } ;
struct TYPE_2__ {int eeh_mode; scalar_t__ eeh_check_count; } ;

/* Variables and functions */
 TYPE_1__* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  __eeh_clear_slot (struct device_node*,int) ; 
 int /*<<< orphan*/  confirm_error_lock ; 
 struct device_node* find_device_pe (struct device_node*) ; 
 int /*<<< orphan*/  pcibios_find_pci_bus (struct device_node*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void eeh_clear_slot (struct device_node *dn, int mode_flag)
{
	unsigned long flags;
	spin_lock_irqsave(&confirm_error_lock, flags);
	
	dn = find_device_pe (dn);
	
	/* Back up one, since config addrs might be shared */
	if (!pcibios_find_pci_bus(dn) && PCI_DN(dn->parent))
		dn = dn->parent;

	PCI_DN(dn)->eeh_mode &= ~mode_flag;
	PCI_DN(dn)->eeh_check_count = 0;
	__eeh_clear_slot(dn, mode_flag);
	spin_unlock_irqrestore(&confirm_error_lock, flags);
}