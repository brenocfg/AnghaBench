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
struct module {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vfree (void*) ; 

void module_free(struct module *module, void *region)
{
	pr_debug("module_free(%s,%08lx)\n", module->name,
					(unsigned long)region);
	vfree(region);
}