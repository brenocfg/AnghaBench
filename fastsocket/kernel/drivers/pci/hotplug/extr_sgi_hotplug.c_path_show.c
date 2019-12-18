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
struct slot {char* physical_path; } ;
struct pci_slot {TYPE_1__* hotplug; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct slot* private; } ;

/* Variables and functions */
 int ENOENT ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t path_show(struct pci_slot *pci_slot, char *buf)
{
	int retval = -ENOENT;
	struct slot *slot = pci_slot->hotplug->private;

	if (!slot)
		return retval;

	retval = sprintf (buf, "%s\n", slot->physical_path);
	return retval;
}