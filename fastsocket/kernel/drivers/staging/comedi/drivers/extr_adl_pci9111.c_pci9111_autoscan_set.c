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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int PCI9111_ASCAN_ON ; 
 int pci9111_trigger_and_autoscan_get () ; 
 int /*<<< orphan*/  pci9111_trigger_and_autoscan_set (int) ; 

__attribute__((used)) static void pci9111_autoscan_set(struct comedi_device *dev, bool autoscan)
{
	int flags;

	flags = pci9111_trigger_and_autoscan_get() & 0x0e;

	if (autoscan)
		flags |= PCI9111_ASCAN_ON;

	pci9111_trigger_and_autoscan_set(flags);
}