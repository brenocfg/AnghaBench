#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ numOfSids; scalar_t__ numOfSubSet; } ;
typedef  TYPE_1__ tSidSet ;
typedef  size_t int32_t ;
struct TYPE_8__ {scalar_t__ flag; } ;
struct TYPE_7__ {scalar_t__ numOfGroupCols; TYPE_3__* columnInfo; } ;
typedef  TYPE_2__ SSqlGroupbyExpr ;
typedef  TYPE_3__ SColIndexEx ;

/* Variables and functions */
 scalar_t__ TSDB_COL_TAG ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static bool isGroupbyEachTable(SSqlGroupbyExpr *pGroupbyExpr, tSidSet *pSidset) {
  if (pGroupbyExpr == NULL || pGroupbyExpr->numOfGroupCols == 0) {
    return false;
  }

  for (int32_t i = 0; i < pGroupbyExpr->numOfGroupCols; ++i) {
    SColIndexEx *pColIndex = &pGroupbyExpr->columnInfo[i];
    if (pColIndex->flag == TSDB_COL_TAG) {
      assert(pSidset->numOfSids == pSidset->numOfSubSet);
      return true;
    }
  }

  return false;
}