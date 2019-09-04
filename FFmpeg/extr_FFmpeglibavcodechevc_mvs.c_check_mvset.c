#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_9__ {int* isLongTerm; int* list; } ;
typedef  TYPE_1__ RefPicList ;
typedef  TYPE_2__ Mv ;

/* Variables and functions */
 int /*<<< orphan*/  mv_scale (TYPE_2__*,TYPE_2__*,int,int) ; 

__attribute__((used)) static int check_mvset(Mv *mvLXCol, Mv *mvCol,
                       int colPic, int poc,
                       RefPicList *refPicList, int X, int refIdxLx,
                       RefPicList *refPicList_col, int listCol, int refidxCol)
{
    int cur_lt = refPicList[X].isLongTerm[refIdxLx];
    int col_lt = refPicList_col[listCol].isLongTerm[refidxCol];
    int col_poc_diff, cur_poc_diff;

    if (cur_lt != col_lt) {
        mvLXCol->x = 0;
        mvLXCol->y = 0;
        return 0;
    }

    col_poc_diff = colPic - refPicList_col[listCol].list[refidxCol];
    cur_poc_diff = poc    - refPicList[X].list[refIdxLx];

    if (cur_lt || col_poc_diff == cur_poc_diff || !col_poc_diff) {
        mvLXCol->x = mvCol->x;
        mvLXCol->y = mvCol->y;
    } else {
        mv_scale(mvLXCol, mvCol, col_poc_diff, cur_poc_diff);
    }
    return 1;
}