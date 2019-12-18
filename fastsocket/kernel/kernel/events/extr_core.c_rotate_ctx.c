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
struct perf_event_context {int /*<<< orphan*/  flexible_groups; int /*<<< orphan*/  rotate_disable; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_rotate_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rotate_ctx(struct perf_event_context *ctx)
{
	/*
	 * Rotate the first entry last of non-pinned groups. Rotation might be
	 * disabled by the inheritance code.
	 */
	if (!ctx->rotate_disable)
		list_rotate_left(&ctx->flexible_groups);
}