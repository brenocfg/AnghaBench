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
struct TYPE_3__ {void** D; scalar_t__ CD; } ;
typedef  TYPE_1__ TM2Context ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  TM2_INIT_POINTERS_2 () ; 
 int /*<<< orphan*/  TM2_RECALC_BLOCK (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * U ; 
 int /*<<< orphan*/ * Uo ; 
 int Ustride ; 
 int /*<<< orphan*/ * V ; 
 int /*<<< orphan*/ * Vo ; 
 int Vstride ; 
 void** Y ; 
 void** Yo ; 
 int /*<<< orphan*/  Ystride ; 
 scalar_t__ clast ; 
 void** last ; 
 int /*<<< orphan*/  oUstride ; 
 int /*<<< orphan*/  oVstride ; 
 int oYstride ; 

__attribute__((used)) static inline void tm2_still_block(TM2Context *ctx, AVFrame *pic, int bx, int by)
{
    int i, j;
    TM2_INIT_POINTERS_2();

    /* update chroma */
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 2; i++){
            U[i] = Uo[i];
            V[i] = Vo[i];
        }
        U  += Ustride; V += Vstride;
        Uo += oUstride; Vo += oVstride;
    }
    U -= Ustride * 2;
    V -= Vstride * 2;
    TM2_RECALC_BLOCK(U, Ustride, clast, ctx->CD);
    TM2_RECALC_BLOCK(V, Vstride, (clast + 2), (ctx->CD + 2));

    /* update deltas */
    ctx->D[0] = Yo[3] - last[3];
    ctx->D[1] = Yo[3 + oYstride] - Yo[3];
    ctx->D[2] = Yo[3 + oYstride * 2] - Yo[3 + oYstride];
    ctx->D[3] = Yo[3 + oYstride * 3] - Yo[3 + oYstride * 2];

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            Y[i]    = Yo[i];
            last[i] = Yo[i];
        }
        Y  += Ystride;
        Yo += oYstride;
    }
}