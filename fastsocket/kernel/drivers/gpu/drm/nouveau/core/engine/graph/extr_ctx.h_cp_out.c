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
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_grctx {scalar_t__ mode; scalar_t__ ctxprog_len; scalar_t__ ctxprog_max; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NOUVEAU_GRCTX_PROG ; 

__attribute__((used)) static inline void
cp_out(struct nouveau_grctx *ctx, u32 inst)
{
	u32 *ctxprog = ctx->data;

	if (ctx->mode != NOUVEAU_GRCTX_PROG)
		return;

	BUG_ON(ctx->ctxprog_len == ctx->ctxprog_max);
	ctxprog[ctx->ctxprog_len++] = inst;
}