#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_12__ {int /*<<< orphan*/  nStatus; } ;
struct TYPE_11__ {scalar_t__ nAggTimeInterval; size_t numOfOutputCols; TYPE_1__* pSelectExpr; int /*<<< orphan*/  pGroupbyExpr; } ;
struct TYPE_9__ {scalar_t__ colIdx; } ;
struct TYPE_10__ {size_t functionId; int numOfParams; TYPE_2__ colInfo; } ;
struct TYPE_8__ {TYPE_3__ pBase; } ;
typedef  TYPE_3__ SSqlFuncExprMsg ;
typedef  TYPE_4__ SQuery ;

/* Variables and functions */
 int /*<<< orphan*/  IS_MULTIOUTPUT (int /*<<< orphan*/ ) ; 
 scalar_t__ PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 size_t TSDB_FUNC_PRJ ; 
 size_t TSDB_FUNC_TS ; 
 size_t TSDB_FUNC_TS_DUMMY ; 
 TYPE_7__* aAggs ; 
 scalar_t__ isGroupbyNormalCol (int /*<<< orphan*/ ) ; 
 scalar_t__ isTopBottomQuery (TYPE_4__*) ; 

bool isFixedOutputQuery(SQuery *pQuery) {
  if (pQuery->nAggTimeInterval != 0) {
    return false;
  }

  // Note:top/bottom query is fixed output query
  if (isTopBottomQuery(pQuery) || isGroupbyNormalCol(pQuery->pGroupbyExpr)) {
    return true;
  }

  for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
    SSqlFuncExprMsg *pExprMsg = &pQuery->pSelectExpr[i].pBase;

    // ignore the ts_comp function
    if (i == 0 && pExprMsg->functionId == TSDB_FUNC_PRJ && pExprMsg->numOfParams == 1 &&
        pExprMsg->colInfo.colIdx == PRIMARYKEY_TIMESTAMP_COL_INDEX) {
      continue;
    }

    if (pExprMsg->functionId == TSDB_FUNC_TS || pExprMsg->functionId == TSDB_FUNC_TS_DUMMY) {
      continue;
    }

    //    // ignore the group by + projection combination
    //    if (pExprMsg->functionId == TSDB_FUNC_PRJ && isGroupbyNormalCol(pQuery)) {
    //      continue;
    //    }

    if (!IS_MULTIOUTPUT(aAggs[pExprMsg->functionId].nStatus)) {
      return true;
    }
  }

  return false;
}