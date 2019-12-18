#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_18__ {size_t outputBytes; scalar_t__ aOutputBuf; scalar_t__ ptsOutputBuf; int /*<<< orphan*/ * resultInfo; } ;
struct TYPE_17__ {size_t numOfOutputCols; TYPE_4__* pSelectExpr; TYPE_3__** sdata; } ;
struct TYPE_16__ {TYPE_7__* pCtx; int /*<<< orphan*/ * resultInfo; TYPE_1__* pMeterObj; TYPE_6__* pQuery; } ;
struct TYPE_13__ {size_t functionId; } ;
struct TYPE_15__ {scalar_t__ resBytes; TYPE_2__ pBase; } ;
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_12__ {size_t pointsPerFileBlock; } ;
typedef  TYPE_5__ SQueryRuntimeEnv ;
typedef  TYPE_6__ SQuery ;
typedef  TYPE_7__ SQLFunctionCtx ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_6__*) ; 
 size_t TSDB_FUNC_BOTTOM ; 
 size_t TSDB_FUNC_DIFF ; 
 size_t TSDB_FUNC_TOP ; 
 int /*<<< orphan*/  initCtxOutputBuf (TYPE_5__*) ; 
 scalar_t__ isTSCompQuery (TYPE_6__*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  resetResultInfo (int /*<<< orphan*/ *) ; 

void resetCtxOutputBuf(SQueryRuntimeEnv *pRuntimeEnv) {
  SQuery *pQuery = pRuntimeEnv->pQuery;
  int32_t rows = pRuntimeEnv->pMeterObj->pointsPerFileBlock;

  for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
    SQLFunctionCtx *pCtx = &pRuntimeEnv->pCtx[i];

    // ts_comp query does not required reversed output
    if (QUERY_IS_ASC_QUERY(pQuery) || isTSCompQuery(pQuery)) {
      pCtx->aOutputBuf = pQuery->sdata[i]->data;
    } else {  // point to the last position of output buffer for desc query
      pCtx->aOutputBuf = pQuery->sdata[i]->data + (rows - 1) * pCtx->outputBytes;
    }

    /*
     * set the output buffer information and intermediate buffer
     * not all queries require the interResultBuf, such as COUNT/TAGPRJ/PRJ/TAG etc.
     */
    resetResultInfo(&pRuntimeEnv->resultInfo[i]);
    pCtx->resultInfo = &pRuntimeEnv->resultInfo[i];

    // set the timestamp output buffer for top/bottom/diff query
    int32_t functionId = pQuery->pSelectExpr[i].pBase.functionId;
    if (functionId == TSDB_FUNC_TOP || functionId == TSDB_FUNC_BOTTOM || functionId == TSDB_FUNC_DIFF) {
      pCtx->ptsOutputBuf = pRuntimeEnv->pCtx[0].aOutputBuf;
    }

    memset(pQuery->sdata[i]->data, 0, (size_t)pQuery->pSelectExpr[i].resBytes * rows);
  }

  initCtxOutputBuf(pRuntimeEnv);
}