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
 int PSOCK ; 
 int PSPIN ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fadv_list ; 
 int /*<<< orphan*/  fadv_lock ; 
 int /*<<< orphan*/  flowadv_thread_cont ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flowadv_thread_func(void *v, wait_result_t w)
{
#pragma unused(v, w)
	lck_mtx_lock(&fadv_lock);
	(void) msleep0(&fadv_list, &fadv_lock, (PSOCK | PSPIN),
	    "flowadv", 0, flowadv_thread_cont);
	/*
	 * msleep0() shouldn't have returned as PCATCH was not set;
	 * therefore assert in this case.
	 */
	lck_mtx_unlock(&fadv_lock);
	VERIFY(0);
}