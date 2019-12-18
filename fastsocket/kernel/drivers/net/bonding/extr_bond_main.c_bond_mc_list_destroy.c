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
struct dev_mc_list {struct dev_mc_list* next; } ;
struct bonding {struct dev_mc_list* mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dev_mc_list*) ; 

__attribute__((used)) static void bond_mc_list_destroy(struct bonding *bond)
{
	struct dev_mc_list *dmi;

	dmi = bond->mc_list;
	while (dmi) {
		bond->mc_list = dmi->next;
		kfree(dmi);
		dmi = bond->mc_list;
	}

	bond->mc_list = NULL;
}