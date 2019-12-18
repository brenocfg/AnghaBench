#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* f; } ;
struct TYPE_7__ {int flags; int mbx; int mb_width; int mby; int l_stride; int c_stride; int mb_height; TYPE_2__ cur; scalar_t__ cv; scalar_t__ cu; scalar_t__ cy; int /*<<< orphan*/ * mv; int /*<<< orphan*/ * pred_mode_Y; int /*<<< orphan*/  mbidx; int /*<<< orphan*/ ** top_mv; } ;
struct TYPE_5__ {scalar_t__* data; } ;
typedef  TYPE_3__ AVSContext ;

/* Variables and functions */
 int A_AVAIL ; 
 int B_AVAIL ; 
 int C_AVAIL ; 
 size_t MV_BWD_X2 ; 
 size_t MV_BWD_X3 ; 
 size_t MV_FWD_X2 ; 
 size_t MV_FWD_X3 ; 
 int /*<<< orphan*/  NOT_AVAIL ; 
 int /*<<< orphan*/  un_mv ; 

int ff_cavs_next_mb(AVSContext *h)
{
    int i;

    h->flags |= A_AVAIL;
    h->cy    += 16;
    h->cu    += 8;
    h->cv    += 8;
    /* copy mvs as predictors to the left */
    for (i = 0; i <= 20; i += 4)
        h->mv[i] = h->mv[i + 2];
    /* copy bottom mvs from cache to top line */
    h->top_mv[0][h->mbx * 2 + 0] = h->mv[MV_FWD_X2];
    h->top_mv[0][h->mbx * 2 + 1] = h->mv[MV_FWD_X3];
    h->top_mv[1][h->mbx * 2 + 0] = h->mv[MV_BWD_X2];
    h->top_mv[1][h->mbx * 2 + 1] = h->mv[MV_BWD_X3];
    /* next MB address */
    h->mbidx++;
    h->mbx++;
    if (h->mbx == h->mb_width) { // New mb line
        h->flags = B_AVAIL | C_AVAIL;
        /* clear left pred_modes */
        h->pred_mode_Y[3] = h->pred_mode_Y[6] = NOT_AVAIL;
        /* clear left mv predictors */
        for (i = 0; i <= 20; i += 4)
            h->mv[i] = un_mv;
        h->mbx = 0;
        h->mby++;
        /* re-calculate sample pointers */
        h->cy = h->cur.f->data[0] + h->mby * 16 * h->l_stride;
        h->cu = h->cur.f->data[1] + h->mby * 8 * h->c_stride;
        h->cv = h->cur.f->data[2] + h->mby * 8 * h->c_stride;
        if (h->mby == h->mb_height) { // Frame end
            return 0;
        }
    }
    return 1;
}