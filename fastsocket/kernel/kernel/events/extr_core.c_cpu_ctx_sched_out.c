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
struct perf_cpu_context {int /*<<< orphan*/  ctx; } ;
typedef  enum event_type_t { ____Placeholder_event_type_t } event_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ctx_sched_out (int /*<<< orphan*/ *,struct perf_cpu_context*,int) ; 

__attribute__((used)) static void cpu_ctx_sched_out(struct perf_cpu_context *cpuctx,
			      enum event_type_t event_type)
{
	ctx_sched_out(&cpuctx->ctx, cpuctx, event_type);
}