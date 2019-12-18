#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_10__ {int /*<<< orphan*/  nStatus; } ;
struct TYPE_9__ {int checkBufferInLoop; size_t numOfOutputCols; int /*<<< orphan*/  pointsToRead; int /*<<< orphan*/  pointsOffset; TYPE_1__* pSelectExpr; int /*<<< orphan*/  pGroupbyExpr; } ;
struct TYPE_8__ {size_t functionId; } ;
struct TYPE_7__ {TYPE_2__ pBase; } ;
typedef  TYPE_2__ SSqlFuncExprMsg ;
typedef  TYPE_3__ SQuery ;

/* Variables and functions */
 int IS_MULTIOUTPUT (int /*<<< orphan*/ ) ; 
 size_t TSDB_FUNC_TS ; 
 size_t TSDB_FUNC_TS_DUMMY ; 
 TYPE_6__* aAggs ; 
 scalar_t__ isGroupbyNormalCol (int /*<<< orphan*/ ) ; 
 scalar_t__ isTopBottomQuery (TYPE_3__*) ; 

__attribute__((used)) static void setScanLimitationByResultBuffer(SQuery *pQuery) {
  if (isTopBottomQuery(pQuery)) {
    pQuery->checkBufferInLoop = 0;
  } else if (isGroupbyNormalCol(pQuery->pGroupbyExpr)) {
    pQuery->checkBufferInLoop = 0;
  } else {
    bool hasMultioutput = false;
    for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
      SSqlFuncExprMsg *pExprMsg = &pQuery->pSelectExpr[i].pBase;
      if (pExprMsg->functionId == TSDB_FUNC_TS || pExprMsg->functionId == TSDB_FUNC_TS_DUMMY) {
        continue;
      }

      hasMultioutput = IS_MULTIOUTPUT(aAggs[pExprMsg->functionId].nStatus);
      if (!hasMultioutput) {
        break;
      }
    }

    pQuery->checkBufferInLoop = hasMultioutput ? 1 : 0;
  }

  pQuery->pointsOffset = pQuery->pointsToRead;
}