#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_16__ {int /*<<< orphan*/  numOfRows; } ;
struct TYPE_15__ {size_t numOfOutputCols; TYPE_2__* pSelectExpr; int /*<<< orphan*/  pGroupbyExpr; } ;
struct TYPE_14__ {size_t usedIndex; int /*<<< orphan*/ * pCtx; TYPE_5__* pResult; TYPE_4__* pQuery; } ;
struct TYPE_12__ {size_t functionId; } ;
struct TYPE_13__ {TYPE_1__ pBase; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* xFinalize ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;
typedef  TYPE_5__ SOutputRes ;

/* Variables and functions */
 TYPE_10__* aAggs ; 
 int /*<<< orphan*/  getNumOfResult (TYPE_3__*) ; 
 scalar_t__ isGroupbyNormalCol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setGroupOutputBuffer (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

void doFinalizeResult(SQueryRuntimeEnv *pRuntimeEnv) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  if (isGroupbyNormalCol(pQuery->pGroupbyExpr)) {
    // for each group result, call the finalize function for each column
    for (int32_t i = 0; i < pRuntimeEnv->usedIndex; ++i) {
      SOutputRes *buf = &pRuntimeEnv->pResult[i];
      setGroupOutputBuffer(pRuntimeEnv, buf);

      for (int32_t j = 0; j < pQuery->numOfOutputCols; ++j) {
        aAggs[pQuery->pSelectExpr[j].pBase.functionId].xFinalize(&pRuntimeEnv->pCtx[j]);
      }

      /*
       * set the number of output results for group by normal columns, the number of output rows usually is 1 except
       * the top and bottom query
       */
      buf->numOfRows = getNumOfResult(pRuntimeEnv);
    }

  } else {
    for (int32_t j = 0; j < pQuery->numOfOutputCols; ++j) {
      aAggs[pQuery->pSelectExpr[j].pBase.functionId].xFinalize(&pRuntimeEnv->pCtx[j]);
    }
  }
}