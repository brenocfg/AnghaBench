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
 int ENOMEM ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_DIAG ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * kalloc_tag (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kperf_kdebug_filter ; 

int
kperf_kdebug_init(void)
{
	kperf_kdebug_filter = kalloc_tag(sizeof(*kperf_kdebug_filter),
	                                 VM_KERN_MEMORY_DIAG);
	if (kperf_kdebug_filter == NULL) {
		return ENOMEM;
	}
	bzero(kperf_kdebug_filter, sizeof(*kperf_kdebug_filter));

	return 0;
}