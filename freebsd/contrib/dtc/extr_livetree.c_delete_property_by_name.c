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
struct property {struct property* next; int /*<<< orphan*/  name; } ;
struct node {struct property* proplist; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_property (struct property*) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 

void delete_property_by_name(struct node *node, char *name)
{
	struct property *prop = node->proplist;

	while (prop) {
		if (streq(prop->name, name)) {
			delete_property(prop);
			return;
		}
		prop = prop->next;
	}
}