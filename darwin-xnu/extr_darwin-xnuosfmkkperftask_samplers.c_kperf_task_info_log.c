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
struct kperf_context {int /*<<< orphan*/  cur_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_TK_INFO_DATA ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
kperf_task_info_log(struct kperf_context *ctx)
{
	assert(ctx != NULL);

	BUF_DATA(PERF_TK_INFO_DATA, ctx->cur_pid);
}