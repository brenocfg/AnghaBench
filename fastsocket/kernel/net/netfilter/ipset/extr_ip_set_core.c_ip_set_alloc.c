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
 int GFP_KERNEL ; 
 size_t KMALLOC_MAX_SIZE ; 
 int __GFP_NOWARN ; 
 void* kzalloc (size_t,int) ; 
 int /*<<< orphan*/  pr_debug (char*,void*) ; 
 void* vzalloc (size_t) ; 

void *
ip_set_alloc(size_t size)
{
	void *members = NULL;

	if (size < KMALLOC_MAX_SIZE)
		members = kzalloc(size, GFP_KERNEL | __GFP_NOWARN);

	if (members) {
		pr_debug("%p: allocated with kmalloc\n", members);
		return members;
	}

	members = vzalloc(size);
	if (!members)
		return NULL;
	pr_debug("%p: allocated with vmalloc\n", members);

	return members;
}