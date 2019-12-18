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
struct _throttle_io_info_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ALLOC_THROTTLE_INFO (char*,struct _throttle_io_info_t*,struct _throttle_io_info_t*) ; 
 int /*<<< orphan*/  throttle_info_rel (void*) ; 

void
throttle_info_release(void *throttle_info)
{
	DEBUG_ALLOC_THROTTLE_INFO("Releaseing info = %p\n",
		(struct _throttle_io_info_t *)throttle_info,
		(struct _throttle_io_info_t *)throttle_info);
	if (throttle_info) /* Just to be careful */
		throttle_info_rel(throttle_info);
}