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
 int /*<<< orphan*/  TM2_C_HI ; 
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
 int /*<<< orphan*/  tm2_high_chroma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int*) ; 

__attribute__((used)) static inline void tm2_hi_res_block(TM2Context *ctx, AVFrame *pic, int bx, int by)
{
    int i;
    int deltas[16];
    TM2_INIT_POINTERS();

    /* hi-res chroma */
    for (i = 0; i < 4; i++) {
        deltas[i]     = GET_TOK(ctx, TM2_C_HI);
        deltas[i + 4] = GET_TOK(ctx, TM2_C_HI);
    }
    tm2_high_chroma(U, Ustride, clast,     ctx->CD,     deltas);
    tm2_high_chroma(V, Vstride, clast + 2, ctx->CD + 2, deltas + 4);

    /* hi-res luma */
    for (i = 0; i < 16; i++)
        deltas[i] = GET_TOK(ctx, TM2_L_HI);

    tm2_apply_deltas(ctx, Y, Ystride, deltas, last);
}