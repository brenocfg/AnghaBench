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
struct property {struct property const* value; struct property const* name; struct property* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct property const*) ; 

__attribute__((used)) static void release_prop_list(const struct property *prop)
{
	struct property *next;
	for (; prop; prop = next) {
		next = prop->next;
		kfree(prop->name);
		kfree(prop->value);
		kfree(prop);
	}

}