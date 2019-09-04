#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* sps; } ;
struct TYPE_11__ {TYPE_2__ ps; TYPE_4__* HEVClc; } ;
struct TYPE_9__ {int cand_up; int cand_left; int cand_up_left; int cand_up_right_sap; int cand_up_right; int cand_bottom_left; } ;
struct TYPE_10__ {int ctb_up_left_flag; int end_of_tiles_x; int end_of_tiles_y; TYPE_3__ na; scalar_t__ ctb_up_right_flag; scalar_t__ ctb_left_flag; scalar_t__ ctb_up_flag; } ;
struct TYPE_7__ {int log2_ctb_size; } ;
typedef  TYPE_4__ HEVCLocalContext ;
typedef  TYPE_5__ HEVCContext ;

/* Variables and functions */
 int av_mod_uintp2 (int,int) ; 

void ff_hevc_set_neighbour_available(HEVCContext *s, int x0, int y0,
                                     int nPbW, int nPbH)
{
    HEVCLocalContext *lc = s->HEVClc;
    int x0b = av_mod_uintp2(x0, s->ps.sps->log2_ctb_size);
    int y0b = av_mod_uintp2(y0, s->ps.sps->log2_ctb_size);

    lc->na.cand_up       = (lc->ctb_up_flag   || y0b);
    lc->na.cand_left     = (lc->ctb_left_flag || x0b);
    lc->na.cand_up_left  = (!x0b && !y0b) ? lc->ctb_up_left_flag : lc->na.cand_left && lc->na.cand_up;
    lc->na.cand_up_right_sap =
            ((x0b + nPbW) == (1 << s->ps.sps->log2_ctb_size)) ?
                    lc->ctb_up_right_flag && !y0b : lc->na.cand_up;
    lc->na.cand_up_right =
            lc->na.cand_up_right_sap
                     && (x0 + nPbW) < lc->end_of_tiles_x;
    lc->na.cand_bottom_left = ((y0 + nPbH) >= lc->end_of_tiles_y) ? 0 : lc->na.cand_left;
}