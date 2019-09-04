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
struct TYPE_3__ {int mbx; int flags; int mb_width; void** mv; int /*<<< orphan*/ * pred_mode_Y; int /*<<< orphan*/ * top_pred_Y; void*** top_mv; } ;
typedef  TYPE_1__ AVSContext ;

/* Variables and functions */
 int B_AVAIL ; 
 int C_AVAIL ; 
 int D_AVAIL ; 
 int MV_BWD_B2 ; 
 size_t MV_BWD_B3 ; 
 size_t MV_BWD_C2 ; 
 size_t MV_BWD_D3 ; 
 int MV_FWD_B2 ; 
 size_t MV_FWD_B3 ; 
 size_t MV_FWD_C2 ; 
 size_t MV_FWD_D3 ; 
 int /*<<< orphan*/  NOT_AVAIL ; 
 void* un_mv ; 

void ff_cavs_init_mb(AVSContext *h)
{
    int i;

    /* copy predictors from top line (MB B and C) into cache */
    for (i = 0; i < 3; i++) {
        h->mv[MV_FWD_B2 + i] = h->top_mv[0][h->mbx * 2 + i];
        h->mv[MV_BWD_B2 + i] = h->top_mv[1][h->mbx * 2 + i];
    }
    h->pred_mode_Y[1] = h->top_pred_Y[h->mbx * 2 + 0];
    h->pred_mode_Y[2] = h->top_pred_Y[h->mbx * 2 + 1];
    /* clear top predictors if MB B is not available */
    if (!(h->flags & B_AVAIL)) {
        h->mv[MV_FWD_B2]  = un_mv;
        h->mv[MV_FWD_B3]  = un_mv;
        h->mv[MV_BWD_B2]  = un_mv;
        h->mv[MV_BWD_B3]  = un_mv;
        h->pred_mode_Y[1] = h->pred_mode_Y[2] = NOT_AVAIL;
        h->flags         &= ~(C_AVAIL | D_AVAIL);
    } else if (h->mbx) {
        h->flags |= D_AVAIL;
    }
    if (h->mbx == h->mb_width - 1) // MB C not available
        h->flags &= ~C_AVAIL;
    /* clear top-right predictors if MB C is not available */
    if (!(h->flags & C_AVAIL)) {
        h->mv[MV_FWD_C2] = un_mv;
        h->mv[MV_BWD_C2] = un_mv;
    }
    /* clear top-left predictors if MB D is not available */
    if (!(h->flags & D_AVAIL)) {
        h->mv[MV_FWD_D3] = un_mv;
        h->mv[MV_BWD_D3] = un_mv;
    }
}