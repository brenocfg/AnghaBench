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
struct TYPE_3__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  h; int /*<<< orphan*/  y; int /*<<< orphan*/  (* gh ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ;scalar_t__ count_aad; } ;
typedef  TYPE_1__ br_gcm_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void
br_gcm_flip(br_gcm_context *ctx)
{
	/*
	 * We complete the GHASH computation if there is a partial block.
	 * The GHASH implementation automatically applies padding with
	 * zeros.
	 */
	size_t ptr;

	ptr = (size_t)ctx->count_aad & (size_t)15;
	if (ptr != 0) {
		ctx->gh(ctx->y, ctx->h, ctx->buf, ptr);
	}
}