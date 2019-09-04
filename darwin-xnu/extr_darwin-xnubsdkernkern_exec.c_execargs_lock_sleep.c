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
typedef  int /*<<< orphan*/  wait_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_SLEEP_DEFAULT ; 
 int /*<<< orphan*/  THREAD_INTERRUPTIBLE ; 
 int /*<<< orphan*/  execargs_cache_lock ; 
 int /*<<< orphan*/  execargs_free_count ; 
 int /*<<< orphan*/  lck_mtx_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static wait_result_t
execargs_lock_sleep(void) {
	return(lck_mtx_sleep(execargs_cache_lock, LCK_SLEEP_DEFAULT, &execargs_free_count, THREAD_INTERRUPTIBLE));
}