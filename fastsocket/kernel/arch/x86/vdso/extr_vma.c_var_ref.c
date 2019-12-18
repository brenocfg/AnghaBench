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

/* Variables and functions */
 scalar_t__ VMAGIC ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 scalar_t__ vdso_enabled ; 

__attribute__((used)) static inline void *var_ref(void *p, char *name)
{
	if (*(void **)p != (void *)VMAGIC) {
		printk("VDSO: variable %s broken\n", name);
		vdso_enabled = 0;
	}
	return p;
}