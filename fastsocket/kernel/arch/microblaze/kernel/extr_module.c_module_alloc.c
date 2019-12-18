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
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * vmalloc (unsigned long) ; 

void *module_alloc(unsigned long size)
{
	void *ret;
	ret = (size == 0) ? NULL : vmalloc(size);
	pr_debug("module_alloc (%08lx@%08lx)\n", size, (unsigned long int)ret);
	return ret;
}