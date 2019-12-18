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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 void* krealloc (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (int) ; 

__attribute__((used)) static void *pidlist_resize(void *p, int newcount)
{
	void *newlist;
	/* note: if new alloc fails, old p will still be valid either way */
	if (is_vmalloc_addr(p)) {
		newlist = vmalloc(newcount * sizeof(pid_t));
		if (!newlist)
			return NULL;
		memcpy(newlist, p, newcount * sizeof(pid_t));
		vfree(p);
	} else {
		newlist = krealloc(p, newcount * sizeof(pid_t), GFP_KERNEL);
	}
	return newlist;
}