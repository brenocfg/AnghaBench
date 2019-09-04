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
struct TYPE_5__ {scalar_t__ CD; } ;
typedef  TYPE_1__ TM2Context ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int GET_TOK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TM2_C_LO ; 
 int /*<<< orphan*/  TM2_INIT_POINTERS () ; 
 int /*<<< orphan*/  TM2_L_HI ; 
 int /*<<< orphan*/  U ; 
 int /*<<< orphan*/  Ustride ; 
 int /*<<< orphan*/  V ; 
 int /*<<< orphan*/  Vstride ; 
 int /*<<< orphan*/  Y ; 
 int /*<<< orphan*/  Ystride ; 
 scalar_t__ clast ; 
 int /*<<< orphan*/  last ; 
 int /*<<< orphan*/  tm2_apply_deltas (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tm2_low_chroma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int*,int) ; 

__attribute__((used)) static inline void tm2_med_res_block(TM2Context *ctx, AVFrame *pic, int bx, int by)
{
    int i;
    int deltas[16];
    TM2_INIT_POINTERS();

    /* low-res chroma */
    deltas[0] = GET_TOK(ctx, TM2_C_LO);
    deltas[1] = deltas[2] = deltas[3] = 0;
    tm2_low_chroma(U, Ustride, clast, ctx->CD, deltas, bx);

    deltas[0] = GET_TOK(ctx, TM2_C_LO);
    deltas[1] = deltas[2] = deltas[3] = 0;
    tm2_low_chroma(V, Vstride, clast + 2, ctx->CD + 2, deltas, bx);

    /* hi-res luma */
    for (i = 0; i < 16; i++)
        deltas[i] = GET_TOK(ctx, TM2_L_HI);

    tm2_apply_deltas(ctx, Y, Ystride, deltas, last);
}