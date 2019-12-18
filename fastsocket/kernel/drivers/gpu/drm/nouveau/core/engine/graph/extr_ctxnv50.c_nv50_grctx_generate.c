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
struct nouveau_grctx {int ctxvals_base; int ctxvals_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS ; 
 int /*<<< orphan*/  AUTO_LOAD ; 
 int /*<<< orphan*/  AUTO_SAVE ; 
 int /*<<< orphan*/  BUSY ; 
 int /*<<< orphan*/  CLEAR ; 
 int /*<<< orphan*/  CP_DISABLE1 ; 
 int /*<<< orphan*/  CP_DISABLE2 ; 
 int /*<<< orphan*/  CP_ENABLE ; 
 int /*<<< orphan*/  CP_END ; 
 int /*<<< orphan*/  CP_NEWCTX ; 
 int /*<<< orphan*/  CP_NEXT_TO_CURRENT ; 
 int /*<<< orphan*/  CP_NEXT_TO_SWAP ; 
 int /*<<< orphan*/  CP_SEEK_1 ; 
 int /*<<< orphan*/  CP_SET_XFER_POINTER ; 
 int /*<<< orphan*/  CP_XFER_1 ; 
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  INTR ; 
 int /*<<< orphan*/  LOAD ; 
 int /*<<< orphan*/  NEWCTX ; 
 int /*<<< orphan*/  NOT_PENDING ; 
 int /*<<< orphan*/  PENDING ; 
 int /*<<< orphan*/  RUNNING ; 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  SET ; 
 int /*<<< orphan*/  STATE ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  STOPPED ; 
 int /*<<< orphan*/  SWAP_DIRECTION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNK01 ; 
 int /*<<< orphan*/  UNK03 ; 
 int /*<<< orphan*/  UNK0B ; 
 int /*<<< orphan*/  UNK1D ; 
 int /*<<< orphan*/  UNK20 ; 
 int /*<<< orphan*/  USER_LOAD ; 
 int /*<<< orphan*/  USER_SAVE ; 
 int /*<<< orphan*/  XFER ; 
 int /*<<< orphan*/  XFER_SWITCH ; 
 int /*<<< orphan*/  cp_bra (struct nouveau_grctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_check_load ; 
 int /*<<< orphan*/  cp_ctx (struct nouveau_grctx*,int,int) ; 
 int /*<<< orphan*/  cp_exit ; 
 int /*<<< orphan*/  cp_lsr (struct nouveau_grctx*,int) ; 
 int /*<<< orphan*/  cp_name (struct nouveau_grctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_out (struct nouveau_grctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_pos (struct nouveau_grctx*,int) ; 
 int /*<<< orphan*/  cp_prepare_exit ; 
 int /*<<< orphan*/  cp_set (struct nouveau_grctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_setup_auto_load ; 
 int /*<<< orphan*/  cp_setup_load ; 
 int /*<<< orphan*/  cp_setup_save ; 
 int /*<<< orphan*/  cp_swap_state ; 
 int /*<<< orphan*/  cp_wait (struct nouveau_grctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_graph_construct_mmio (struct nouveau_grctx*) ; 
 int /*<<< orphan*/  nv50_graph_construct_xfer1 (struct nouveau_grctx*) ; 
 int /*<<< orphan*/  nv50_graph_construct_xfer2 (struct nouveau_grctx*) ; 

__attribute__((used)) static int
nv50_grctx_generate(struct nouveau_grctx *ctx)
{
	cp_set (ctx, STATE, RUNNING);
	cp_set (ctx, XFER_SWITCH, ENABLE);
	/* decide whether we're loading/unloading the context */
	cp_bra (ctx, AUTO_SAVE, PENDING, cp_setup_save);
	cp_bra (ctx, USER_SAVE, PENDING, cp_setup_save);

	cp_name(ctx, cp_check_load);
	cp_bra (ctx, AUTO_LOAD, PENDING, cp_setup_auto_load);
	cp_bra (ctx, USER_LOAD, PENDING, cp_setup_load);
	cp_bra (ctx, ALWAYS, TRUE, cp_prepare_exit);

	/* setup for context load */
	cp_name(ctx, cp_setup_auto_load);
	cp_out (ctx, CP_DISABLE1);
	cp_out (ctx, CP_DISABLE2);
	cp_out (ctx, CP_ENABLE);
	cp_out (ctx, CP_NEXT_TO_SWAP);
	cp_set (ctx, UNK01, SET);
	cp_name(ctx, cp_setup_load);
	cp_out (ctx, CP_NEWCTX);
	cp_wait(ctx, NEWCTX, BUSY);
	cp_set (ctx, UNK1D, CLEAR);
	cp_set (ctx, SWAP_DIRECTION, LOAD);
	cp_bra (ctx, UNK0B, SET, cp_prepare_exit);
	cp_bra (ctx, ALWAYS, TRUE, cp_swap_state);

	/* setup for context save */
	cp_name(ctx, cp_setup_save);
	cp_set (ctx, UNK1D, SET);
	cp_wait(ctx, STATUS, BUSY);
	cp_wait(ctx, INTR, PENDING);
	cp_bra (ctx, STATUS, BUSY, cp_setup_save);
	cp_set (ctx, UNK01, SET);
	cp_set (ctx, SWAP_DIRECTION, SAVE);

	/* general PGRAPH state */
	cp_name(ctx, cp_swap_state);
	cp_set (ctx, UNK03, SET);
	cp_pos (ctx, 0x00004/4);
	cp_ctx (ctx, 0x400828, 1); /* needed. otherwise, flickering happens. */
	cp_pos (ctx, 0x00100/4);
	nv50_graph_construct_mmio(ctx);
	nv50_graph_construct_xfer1(ctx);
	nv50_graph_construct_xfer2(ctx);

	cp_bra (ctx, SWAP_DIRECTION, SAVE, cp_check_load);

	cp_set (ctx, UNK20, SET);
	cp_set (ctx, SWAP_DIRECTION, SAVE); /* no idea why this is needed, but fixes at least one lockup. */
	cp_lsr (ctx, ctx->ctxvals_base);
	cp_out (ctx, CP_SET_XFER_POINTER);
	cp_lsr (ctx, 4);
	cp_out (ctx, CP_SEEK_1);
	cp_out (ctx, CP_XFER_1);
	cp_wait(ctx, XFER, BUSY);

	/* pre-exit state updates */
	cp_name(ctx, cp_prepare_exit);
	cp_set (ctx, UNK01, CLEAR);
	cp_set (ctx, UNK03, CLEAR);
	cp_set (ctx, UNK1D, CLEAR);

	cp_bra (ctx, USER_SAVE, PENDING, cp_exit);
	cp_out (ctx, CP_NEXT_TO_CURRENT);

	cp_name(ctx, cp_exit);
	cp_set (ctx, USER_SAVE, NOT_PENDING);
	cp_set (ctx, USER_LOAD, NOT_PENDING);
	cp_set (ctx, XFER_SWITCH, DISABLE);
	cp_set (ctx, STATE, STOPPED);
	cp_out (ctx, CP_END);
	ctx->ctxvals_pos += 0x400; /* padding... no idea why you need it */

	return 0;
}