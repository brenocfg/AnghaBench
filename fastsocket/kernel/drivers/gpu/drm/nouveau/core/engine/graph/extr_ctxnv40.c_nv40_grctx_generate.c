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
struct nouveau_grctx {int ctxvals_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS ; 
 int /*<<< orphan*/  AUTO_LOAD ; 
 int /*<<< orphan*/  AUTO_SAVE ; 
 int /*<<< orphan*/  CLEAR ; 
 int CP_END ; 
 int CP_NEXT_TO_CURRENT ; 
 int CP_NEXT_TO_SWAP ; 
 int /*<<< orphan*/  IDLE ; 
 int /*<<< orphan*/  LOAD ; 
 int /*<<< orphan*/  NOT_PENDING ; 
 int /*<<< orphan*/  PENDING ; 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  SWAP_DIRECTION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNK54 ; 
 int /*<<< orphan*/  UNK57 ; 
 int /*<<< orphan*/  USER_LOAD ; 
 int /*<<< orphan*/  USER_SAVE ; 
 int /*<<< orphan*/  cp_bra (struct nouveau_grctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_check_load ; 
 int /*<<< orphan*/  cp_exit ; 
 int /*<<< orphan*/  cp_lsr (struct nouveau_grctx*,int) ; 
 int /*<<< orphan*/  cp_name (struct nouveau_grctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_out (struct nouveau_grctx*,int) ; 
 int /*<<< orphan*/  cp_pos (struct nouveau_grctx*,int) ; 
 int /*<<< orphan*/  cp_prepare_exit ; 
 int /*<<< orphan*/  cp_set (struct nouveau_grctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_setup_auto_load ; 
 int /*<<< orphan*/  cp_setup_load ; 
 int /*<<< orphan*/  cp_setup_save ; 
 int /*<<< orphan*/  cp_swap_state ; 
 int /*<<< orphan*/  cp_wait (struct nouveau_grctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv40_graph_construct_general (struct nouveau_grctx*) ; 
 int /*<<< orphan*/  nv40_graph_construct_shader (struct nouveau_grctx*) ; 
 int /*<<< orphan*/  nv40_graph_construct_state3d (struct nouveau_grctx*) ; 
 int /*<<< orphan*/  nv40_graph_construct_state3d_2 (struct nouveau_grctx*) ; 
 int /*<<< orphan*/  nv40_graph_construct_state3d_3 (struct nouveau_grctx*) ; 

__attribute__((used)) static void
nv40_grctx_generate(struct nouveau_grctx *ctx)
{
	/* decide whether we're loading/unloading the context */
	cp_bra (ctx, AUTO_SAVE, PENDING, cp_setup_save);
	cp_bra (ctx, USER_SAVE, PENDING, cp_setup_save);

	cp_name(ctx, cp_check_load);
	cp_bra (ctx, AUTO_LOAD, PENDING, cp_setup_auto_load);
	cp_bra (ctx, USER_LOAD, PENDING, cp_setup_load);
	cp_bra (ctx, ALWAYS, TRUE, cp_exit);

	/* setup for context load */
	cp_name(ctx, cp_setup_auto_load);
	cp_wait(ctx, STATUS, IDLE);
	cp_out (ctx, CP_NEXT_TO_SWAP);
	cp_name(ctx, cp_setup_load);
	cp_wait(ctx, STATUS, IDLE);
	cp_set (ctx, SWAP_DIRECTION, LOAD);
	cp_out (ctx, 0x00910880); /* ?? */
	cp_out (ctx, 0x00901ffe); /* ?? */
	cp_out (ctx, 0x01940000); /* ?? */
	cp_lsr (ctx, 0x20);
	cp_out (ctx, 0x0060000b); /* ?? */
	cp_wait(ctx, UNK57, CLEAR);
	cp_out (ctx, 0x0060000c); /* ?? */
	cp_bra (ctx, ALWAYS, TRUE, cp_swap_state);

	/* setup for context save */
	cp_name(ctx, cp_setup_save);
	cp_set (ctx, SWAP_DIRECTION, SAVE);

	/* general PGRAPH state */
	cp_name(ctx, cp_swap_state);
	cp_pos (ctx, 0x00020/4);
	nv40_graph_construct_general(ctx);
	cp_wait(ctx, STATUS, IDLE);

	/* 3D state, block 1 */
	cp_bra (ctx, UNK54, CLEAR, cp_prepare_exit);
	nv40_graph_construct_state3d(ctx);
	cp_wait(ctx, STATUS, IDLE);

	/* 3D state, block 2 */
	nv40_graph_construct_state3d_2(ctx);

	/* Some other block of "random" state */
	nv40_graph_construct_state3d_3(ctx);

	/* Per-vertex shader state */
	cp_pos (ctx, ctx->ctxvals_pos);
	nv40_graph_construct_shader(ctx);

	/* pre-exit state updates */
	cp_name(ctx, cp_prepare_exit);
	cp_bra (ctx, SWAP_DIRECTION, SAVE, cp_check_load);
	cp_bra (ctx, USER_SAVE, PENDING, cp_exit);
	cp_out (ctx, CP_NEXT_TO_CURRENT);

	cp_name(ctx, cp_exit);
	cp_set (ctx, USER_SAVE, NOT_PENDING);
	cp_set (ctx, USER_LOAD, NOT_PENDING);
	cp_out (ctx, CP_END);
}