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
struct vmac_ctx {scalar_t__ first_block_processed; int /*<<< orphan*/ * polykey; int /*<<< orphan*/ * polytmp; } ;

/* Variables and functions */

__attribute__((used)) static void vhash_abort(struct vmac_ctx *ctx)
{
	ctx->polytmp[0] = ctx->polykey[0] ;
	ctx->polytmp[1] = ctx->polykey[1] ;
	ctx->first_block_processed = 0;
}