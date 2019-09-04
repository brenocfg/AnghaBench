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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ host_t ;

/* Variables and functions */
 scalar_t__ HOST_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_HOST ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 

kern_return_t
mach_zone_force_gc(
	host_t host)
{
	if (host == HOST_NULL)
		return KERN_INVALID_HOST;

#if DEBUG || DEVELOPMENT
	/* Callout to buffer cache GC to drop elements in the apfs zones */
	if (consider_buffer_cache_collect != NULL) {
		(void)(*consider_buffer_cache_collect)(0);
	}
	consider_zone_gc(FALSE);
#endif /* DEBUG || DEVELOPMENT */
	return (KERN_SUCCESS);
}