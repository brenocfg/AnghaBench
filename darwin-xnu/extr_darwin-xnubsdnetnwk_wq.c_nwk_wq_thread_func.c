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
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nwk_wq_lock ; 
 int /*<<< orphan*/  nwk_wq_thread_cont ; 
 int /*<<< orphan*/  nwk_wq_waitch ; 

__attribute__((used)) static void
nwk_wq_thread_func(void *v, wait_result_t w)
{
#pragma unused(v, w)
	lck_mtx_lock(&nwk_wq_lock);
	(void) msleep0(&nwk_wq_waitch, &nwk_wq_lock,
	    (PZERO - 1), "nwk_wq_thread_func", 0, nwk_wq_thread_cont);
	/*
	 * msleep0() shouldn't have returned as PCATCH was not set;
	 * therefore assert in this case.
	 */
	lck_mtx_unlock(&nwk_wq_lock);
	VERIFY(0);
}