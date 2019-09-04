#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* ref; } ;
struct TYPE_15__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_14__ {int pred_flag; size_t* ref_idx; TYPE_5__* mv; } ;
struct TYPE_13__ {scalar_t__* list; } ;
struct TYPE_12__ {TYPE_1__* refPicList; } ;
struct TYPE_11__ {scalar_t__* list; } ;
typedef  TYPE_3__ RefPicList ;
typedef  TYPE_4__ MvField ;
typedef  TYPE_5__ Mv ;
typedef  TYPE_6__ HEVCContext ;

/* Variables and functions */
 int FFABS (scalar_t__) ; 
 int PF_BI ; 

__attribute__((used)) static int boundary_strength(HEVCContext *s, MvField *curr, MvField *neigh,
                             RefPicList *neigh_refPicList)
{
    if (curr->pred_flag == PF_BI &&  neigh->pred_flag == PF_BI) {
        // same L0 and L1
        if (s->ref->refPicList[0].list[curr->ref_idx[0]] == neigh_refPicList[0].list[neigh->ref_idx[0]]  &&
            s->ref->refPicList[0].list[curr->ref_idx[0]] == s->ref->refPicList[1].list[curr->ref_idx[1]] &&
            neigh_refPicList[0].list[neigh->ref_idx[0]] == neigh_refPicList[1].list[neigh->ref_idx[1]]) {
            if ((FFABS(neigh->mv[0].x - curr->mv[0].x) >= 4 || FFABS(neigh->mv[0].y - curr->mv[0].y) >= 4 ||
                 FFABS(neigh->mv[1].x - curr->mv[1].x) >= 4 || FFABS(neigh->mv[1].y - curr->mv[1].y) >= 4) &&
                (FFABS(neigh->mv[1].x - curr->mv[0].x) >= 4 || FFABS(neigh->mv[1].y - curr->mv[0].y) >= 4 ||
                 FFABS(neigh->mv[0].x - curr->mv[1].x) >= 4 || FFABS(neigh->mv[0].y - curr->mv[1].y) >= 4))
                return 1;
            else
                return 0;
        } else if (neigh_refPicList[0].list[neigh->ref_idx[0]] == s->ref->refPicList[0].list[curr->ref_idx[0]] &&
                   neigh_refPicList[1].list[neigh->ref_idx[1]] == s->ref->refPicList[1].list[curr->ref_idx[1]]) {
            if (FFABS(neigh->mv[0].x - curr->mv[0].x) >= 4 || FFABS(neigh->mv[0].y - curr->mv[0].y) >= 4 ||
                FFABS(neigh->mv[1].x - curr->mv[1].x) >= 4 || FFABS(neigh->mv[1].y - curr->mv[1].y) >= 4)
                return 1;
            else
                return 0;
        } else if (neigh_refPicList[1].list[neigh->ref_idx[1]] == s->ref->refPicList[0].list[curr->ref_idx[0]] &&
                   neigh_refPicList[0].list[neigh->ref_idx[0]] == s->ref->refPicList[1].list[curr->ref_idx[1]]) {
            if (FFABS(neigh->mv[1].x - curr->mv[0].x) >= 4 || FFABS(neigh->mv[1].y - curr->mv[0].y) >= 4 ||
                FFABS(neigh->mv[0].x - curr->mv[1].x) >= 4 || FFABS(neigh->mv[0].y - curr->mv[1].y) >= 4)
                return 1;
            else
                return 0;
        } else {
            return 1;
        }
    } else if ((curr->pred_flag != PF_BI) && (neigh->pred_flag != PF_BI)){ // 1 MV
        Mv A, B;
        int ref_A, ref_B;

        if (curr->pred_flag & 1) {
            A     = curr->mv[0];
            ref_A = s->ref->refPicList[0].list[curr->ref_idx[0]];
        } else {
            A     = curr->mv[1];
            ref_A = s->ref->refPicList[1].list[curr->ref_idx[1]];
        }

        if (neigh->pred_flag & 1) {
            B     = neigh->mv[0];
            ref_B = neigh_refPicList[0].list[neigh->ref_idx[0]];
        } else {
            B     = neigh->mv[1];
            ref_B = neigh_refPicList[1].list[neigh->ref_idx[1]];
        }

        if (ref_A == ref_B) {
            if (FFABS(A.x - B.x) >= 4 || FFABS(A.y - B.y) >= 4)
                return 1;
            else
                return 0;
        } else
            return 1;
    }

    return 1;
}