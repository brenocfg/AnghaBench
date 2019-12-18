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
struct kperf_thread_info {int /*<<< orphan*/  kpthi_runmode; int /*<<< orphan*/  kpthi_dq_addr; int /*<<< orphan*/  kpthi_tid; int /*<<< orphan*/  kpthi_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_TI_DATA ; 

void
kperf_thread_info_log(struct kperf_thread_info *ti)
{
	BUF_DATA(PERF_TI_DATA, ti->kpthi_pid, ti->kpthi_tid /* K64-only */,
	                       ti->kpthi_dq_addr, ti->kpthi_runmode);
}