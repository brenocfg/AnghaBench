#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int x; int y; } ;
struct TYPE_7__ {int mb_stride; int mb_w; int mb_size; int mb_h; TYPE_2__* mv; scalar_t__ top; } ;
typedef  TYPE_1__ MVInfo ;
typedef  TYPE_2__ MV ;

/* Variables and functions */
 void* mid_pred (int,int,int) ; 
 TYPE_2__ zero_mv ; 

__attribute__((used)) static MV mvi_predict(MVInfo *mvi, int mb_x, int mb_y, MV diff)
{
    MV res, pred_mv;
    int left_mv, right_mv, top_mv, bot_mv;

    if (mvi->top) {
        if (mb_x > 0) {
            pred_mv = mvi->mv[mvi->mb_stride + mb_x - 1];
        } else {
            pred_mv = zero_mv;
        }
    } else if ((mb_x == 0) || (mb_x == mvi->mb_w - 1)) {
        pred_mv = mvi->mv[mb_x];
    } else {
        MV A = mvi->mv[mvi->mb_stride + mb_x - 1];
        MV B = mvi->mv[                 mb_x    ];
        MV C = mvi->mv[                 mb_x + 1];
        pred_mv.x = mid_pred(A.x, B.x, C.x);
        pred_mv.y = mid_pred(A.y, B.y, C.y);
    }

    res = pred_mv;

    left_mv = -((mb_x * mvi->mb_size));
    right_mv = ((mvi->mb_w - mb_x - 1) * mvi->mb_size);
    if (res.x < left_mv) {
        res.x = left_mv;
    }
    if (res.x > right_mv) {
        res.x = right_mv;
    }
    top_mv = -((mb_y * mvi->mb_size));
    bot_mv = ((mvi->mb_h - mb_y - 1) * mvi->mb_size);
    if (res.y < top_mv) {
        res.y = top_mv;
    }
    if (res.y > bot_mv) {
        res.y = bot_mv;
    }

    mvi->mv[mvi->mb_stride + mb_x].x = res.x + diff.x;
    mvi->mv[mvi->mb_stride + mb_x].y = res.y + diff.y;

    return res;
}