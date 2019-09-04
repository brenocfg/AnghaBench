#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int pred_flag; size_t* ref_idx; int /*<<< orphan*/ * mv; } ;
struct TYPE_10__ {TYPE_1__* sps; } ;
struct TYPE_13__ {TYPE_3__* ref; TYPE_2__ ps; } ;
struct TYPE_12__ {int* isLongTerm; } ;
struct TYPE_11__ {TYPE_4__* refPicList; int /*<<< orphan*/ * tab_mvf; } ;
struct TYPE_9__ {int min_pu_width; } ;
typedef  TYPE_4__ RefPicList ;
typedef  int /*<<< orphan*/  MvField ;
typedef  int /*<<< orphan*/  Mv ;
typedef  TYPE_5__ HEVCContext ;

/* Variables and functions */
 TYPE_8__ TAB_MVF (int,int) ; 
 int /*<<< orphan*/  dist_scale (TYPE_5__*,int /*<<< orphan*/ *,int,int,int,int,int,int) ; 

__attribute__((used)) static int mv_mp_mode_mx_lt(HEVCContext *s, int x, int y, int pred_flag_index,
                            Mv *mv, int ref_idx_curr, int ref_idx)
{
    MvField *tab_mvf = s->ref->tab_mvf;
    int min_pu_width = s->ps.sps->min_pu_width;

    RefPicList *refPicList = s->ref->refPicList;

    if ((TAB_MVF(x, y).pred_flag) & (1 << pred_flag_index)) {
        int currIsLongTerm     = refPicList[ref_idx_curr].isLongTerm[ref_idx];

        int colIsLongTerm =
            refPicList[pred_flag_index].isLongTerm[(TAB_MVF(x, y).ref_idx[pred_flag_index])];

        if (colIsLongTerm == currIsLongTerm) {
            *mv = TAB_MVF(x, y).mv[pred_flag_index];
            if (!currIsLongTerm)
                dist_scale(s, mv, min_pu_width, x, y,
                           pred_flag_index, ref_idx_curr, ref_idx);
            return 1;
        }
    }
    return 0;
}