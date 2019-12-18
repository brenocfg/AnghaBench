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
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int OF_IMAP_NO_PHANDLE ; 
 unsigned int OF_IMAP_OLDWORLD_MAC ; 
 struct device_node* of_find_all_nodes (struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_irq_dflt_pic ; 
 unsigned int of_irq_workarounds ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void of_irq_map_init(unsigned int flags)
{
	of_irq_workarounds = flags;

	/* OldWorld, don't bother looking at other things */
	if (flags & OF_IMAP_OLDWORLD_MAC)
		return;

	/* If we don't have phandles, let's try to locate a default interrupt
	 * controller (happens when booting with BootX). We do a first match
	 * here, hopefully, that only ever happens on machines with one
	 * controller.
	 */
	if (flags & OF_IMAP_NO_PHANDLE) {
		struct device_node *np;

		for (np = NULL; (np = of_find_all_nodes(np)) != NULL;) {
			if (of_get_property(np, "interrupt-controller", NULL)
				== NULL)
				continue;
			/* Skip /chosen/interrupt-controller */
			if (strcmp(np->name, "chosen") == 0)
				continue;
			/* It seems like at least one person on this planet
			 * wants to use BootX on a machine with an AppleKiwi
			 * controller which happens to pretend to be an
			 * interrupt controller too.
			 */
			if (strcmp(np->name, "AppleKiwi") == 0)
				continue;
			/* I think we found one ! */
			of_irq_dflt_pic = np;
			break;
		}
	}

}