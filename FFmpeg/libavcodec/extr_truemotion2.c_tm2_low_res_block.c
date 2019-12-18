#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* D; scalar_t__ CD; } ;
typedef  TYPE_1__ TM2Context ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int GET_TOK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TM2_C_LO ; 
 int /*<<< orphan*/  TM2_INIT_POINTERS () ; 
 int /*<<< orphan*/  TM2_L_LO ; 
 int /*<<< orphan*/  U ; 
 int /*<<< orphan*/  Ustride ; 
 int /*<<< orphan*/  V ; 
 int /*<<< orphan*/  Vstride ; 
 int /*<<< orphan*/  Y ; 
 int /*<<< orphan*/  Ystride ; 
 scalar_t__ clast ; 
 int* last ; 
 int /*<<< orphan*/  tm2_apply_deltas (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  tm2_low_chroma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int*,int) ; 

__attribute__((used)) static inline void tm2_low_res_block(TM2Context *ctx, AVFrame *pic, int bx, int by)
{
    int i;
    int t1, t2;
    int deltas[16];
    TM2_INIT_POINTERS();

    /* low-res chroma */
    deltas[0] = GET_TOK(ctx, TM2_C_LO);
    deltas[1] = deltas[2] = deltas[3] = 0;
    tm2_low_chroma(U, Ustride, clast, ctx->CD, deltas, bx);

    deltas[0] = GET_TOK(ctx, TM2_C_LO);
    deltas[1] = deltas[2] = deltas[3] = 0;
    tm2_low_chroma(V, Vstride, clast + 2, ctx->CD + 2, deltas, bx);

    /* low-res luma */
    for (i = 0; i < 16; i++)
        deltas[i] = 0;

    deltas[ 0] = GET_TOK(ctx, TM2_L_LO);
    deltas[ 2] = GET_TOK(ctx, TM2_L_LO);
    deltas[ 8] = GET_TOK(ctx, TM2_L_LO);
    deltas[10] = GET_TOK(ctx, TM2_L_LO);

    if (bx > 0)
        last[0] = (int)((unsigned)last[-1] - ctx->D[0] - ctx->D[1] - ctx->D[2] - ctx->D[3] + last[1]) >> 1;
    else
        last[0] = (int)((unsigned)last[1]  - ctx->D[0] - ctx->D[1] - ctx->D[2] - ctx->D[3])>> 1;
    last[2] = (int)((unsigned)last[1] + last[3]) >> 1;

    t1 = ctx->D[0] + ctx->D[1];
    ctx->D[0] = t1 >> 1;
    ctx->D[1] = t1 - (t1 >> 1);
    t2 = ctx->D[2] + ctx->D[3];
    ctx->D[2] = t2 >> 1;
    ctx->D[3] = t2 - (t2 >> 1);

    tm2_apply_deltas(ctx, Y, Ystride, deltas, last);
}