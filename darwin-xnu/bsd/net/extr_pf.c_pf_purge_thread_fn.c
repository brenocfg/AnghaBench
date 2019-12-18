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
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_purge_thread_cont ; 
 int /*<<< orphan*/  tsleep0 (void (*) (void*,int /*<<< orphan*/ ),int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pf_purge_thread_fn(void *v, wait_result_t w)
{
#pragma unused(v, w)
	(void) tsleep0(pf_purge_thread_fn, PWAIT, "pf_purge", 0,
	    pf_purge_thread_cont);
	/*
	 * tsleep0() shouldn't have returned as PCATCH was not set;
	 * therefore assert in this case.
	 */
	VERIFY(0);
}