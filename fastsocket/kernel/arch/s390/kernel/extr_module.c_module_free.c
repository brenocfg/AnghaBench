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
struct TYPE_2__ {void* syminfo; } ;
struct module {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (void*) ; 

void module_free(struct module *mod, void *module_region)
{
	if (mod) {
		vfree(mod->arch.syminfo);
		mod->arch.syminfo = NULL;
	}
	vfree(module_region);
}