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
typedef  int /*<<< orphan*/ * uthread_t ;

/* Variables and functions */
 int throttle_get_io_policy (int /*<<< orphan*/ **) ; 
 int throttle_get_thread_throttle_level_internal (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
throttle_get_thread_throttle_level(uthread_t ut)
{
	uthread_t *ut_p = (ut == NULL) ? &ut : NULL;
	int io_tier = throttle_get_io_policy(ut_p);

	return throttle_get_thread_throttle_level_internal(ut, io_tier);
}