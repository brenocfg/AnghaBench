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
struct perf_event_context {int /*<<< orphan*/ * parent_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_ctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unclone_ctx(struct perf_event_context *ctx)
{
	if (ctx->parent_ctx) {
		put_ctx(ctx->parent_ctx);
		ctx->parent_ctx = NULL;
	}
}