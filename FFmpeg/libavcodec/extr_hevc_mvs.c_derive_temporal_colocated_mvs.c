#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ collocated_list; } ;
struct TYPE_13__ {scalar_t__ poc; TYPE_2__ sh; TYPE_1__* ref; } ;
struct TYPE_12__ {int pred_flag; } ;
struct TYPE_11__ {int nb_refs; scalar_t__* list; } ;
struct TYPE_9__ {TYPE_3__* refPicList; } ;
typedef  TYPE_3__ RefPicList ;
typedef  TYPE_4__ MvField ;
typedef  int /*<<< orphan*/  Mv ;
typedef  TYPE_5__ HEVCContext ;

/* Variables and functions */
 int CHECK_MVSET (int) ; 
 scalar_t__ L1 ; 
 int PF_BI ; 
 int PF_INTRA ; 
 int PF_L0 ; 

__attribute__((used)) static int derive_temporal_colocated_mvs(HEVCContext *s, MvField temp_col,
                                         int refIdxLx, Mv *mvLXCol, int X,
                                         int colPic, RefPicList *refPicList_col)
{
    RefPicList *refPicList = s->ref->refPicList;

    if (temp_col.pred_flag == PF_INTRA)
        return 0;

    if (!(temp_col.pred_flag & PF_L0))
        return CHECK_MVSET(1);
    else if (temp_col.pred_flag == PF_L0)
        return CHECK_MVSET(0);
    else if (temp_col.pred_flag == PF_BI) {
        int check_diffpicount = 0;
        int i, j;
        for (j = 0; j < 2; j++) {
            for (i = 0; i < refPicList[j].nb_refs; i++) {
                if (refPicList[j].list[i] > s->poc) {
                    check_diffpicount++;
                    break;
                }
            }
        }
        if (!check_diffpicount) {
            if (X==0)
                return CHECK_MVSET(0);
            else
                return CHECK_MVSET(1);
        } else {
            if (s->sh.collocated_list == L1)
                return CHECK_MVSET(0);
            else
                return CHECK_MVSET(1);
        }
    }

    return 0;
}