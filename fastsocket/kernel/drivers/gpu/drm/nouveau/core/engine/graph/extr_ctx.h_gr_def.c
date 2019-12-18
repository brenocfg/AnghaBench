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
typedef  int u32 ;
struct nouveau_grctx {scalar_t__ mode; int ctxprog_reg; int ctxvals_base; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ NOUVEAU_GRCTX_VALS ; 
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void
gr_def(struct nouveau_grctx *ctx, u32 reg, u32 val)
{
	if (ctx->mode != NOUVEAU_GRCTX_VALS)
		return;

	reg = (reg - 0x00400000) / 4;
	reg = (reg - ctx->ctxprog_reg) + ctx->ctxvals_base;

	nv_wo32(ctx->data, reg * 4, val);
}