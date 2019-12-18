#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  const** bctx; } ;
typedef  TYPE_1__ br_ccm_context ;
typedef  int /*<<< orphan*/  br_block_ctrcbc_class ;

/* Variables and functions */

void
br_ccm_init(br_ccm_context *ctx, const br_block_ctrcbc_class **bctx)
{
	ctx->bctx = bctx;
}