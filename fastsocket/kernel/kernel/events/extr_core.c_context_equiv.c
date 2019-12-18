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
struct perf_event_context {scalar_t__ parent_ctx; scalar_t__ parent_gen; int /*<<< orphan*/  pin_count; } ;

/* Variables and functions */

__attribute__((used)) static int context_equiv(struct perf_event_context *ctx1,
			 struct perf_event_context *ctx2)
{
	return ctx1->parent_ctx && ctx1->parent_ctx == ctx2->parent_ctx
		&& ctx1->parent_gen == ctx2->parent_gen
		&& !ctx1->pin_count && !ctx2->pin_count;
}