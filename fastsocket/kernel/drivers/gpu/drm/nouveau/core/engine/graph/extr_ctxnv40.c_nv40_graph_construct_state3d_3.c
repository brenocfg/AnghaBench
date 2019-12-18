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
struct nouveau_grctx {int ctxvals_pos; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  SWAP_DIRECTION ; 
 int /*<<< orphan*/  cp_bra (struct nouveau_grctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lsr (struct nouveau_grctx*,int) ; 
 int /*<<< orphan*/  cp_name (struct nouveau_grctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_out (struct nouveau_grctx*,int) ; 
 int /*<<< orphan*/  cp_swap_state3d_3_is_save ; 
 scalar_t__ nv44_graph_class (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv40_graph_construct_state3d_3(struct nouveau_grctx *ctx)
{
	int len = nv44_graph_class(ctx->device) ? 0x0084 : 0x0684;

	cp_out (ctx, 0x300000);
	cp_lsr (ctx, len - 4);
	cp_bra (ctx, SWAP_DIRECTION, SAVE, cp_swap_state3d_3_is_save);
	cp_lsr (ctx, len);
	cp_name(ctx, cp_swap_state3d_3_is_save);
	cp_out (ctx, 0x800001);

	ctx->ctxvals_pos += len;
}