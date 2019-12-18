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
typedef  int /*<<< orphan*/  dispatch_semaphore_t ;

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_NOTNULL (void*,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  dispatch_semaphore_signal (int /*<<< orphan*/ ) ; 
 scalar_t__ running_threads ; 

__attribute__((used)) static void *
spinning_thread(void *semp)
{
	T_QUIET;
	T_ASSERT_NOTNULL(semp, "semaphore passed to thread should not be NULL");
	dispatch_semaphore_signal(*(dispatch_semaphore_t *)semp);

	while (running_threads);
	return NULL;
}