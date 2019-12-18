#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int x; int y; int /*<<< orphan*/  dist; } ;
typedef  TYPE_1__ cavs_vector ;
typedef  int /*<<< orphan*/  AVSContext ;

/* Variables and functions */
 int abs (int) ; 
 int mid_pred (int,int,int) ; 
 int /*<<< orphan*/  scale_mv (int /*<<< orphan*/ *,int*,int*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mv_pred_median(AVSContext *h,
                                  cavs_vector *mvP,
                                  cavs_vector *mvA,
                                  cavs_vector *mvB,
                                  cavs_vector *mvC)
{
    int ax, ay, bx, by, cx, cy;
    int len_ab, len_bc, len_ca, len_mid;

    /* scale candidates according to their temporal span */
    scale_mv(h, &ax, &ay, mvA, mvP->dist);
    scale_mv(h, &bx, &by, mvB, mvP->dist);
    scale_mv(h, &cx, &cy, mvC, mvP->dist);
    /* find the geometrical median of the three candidates */
    len_ab  = abs(ax - bx) + abs(ay - by);
    len_bc  = abs(bx - cx) + abs(by - cy);
    len_ca  = abs(cx - ax) + abs(cy - ay);
    len_mid = mid_pred(len_ab, len_bc, len_ca);
    if (len_mid == len_ab) {
        mvP->x = cx;
        mvP->y = cy;
    } else if (len_mid == len_bc) {
        mvP->x = ax;
        mvP->y = ay;
    } else {
        mvP->x = bx;
        mvP->y = by;
    }
}