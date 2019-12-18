#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;
struct TYPE_21__ {int /*<<< orphan*/  numOfNullPoints; int /*<<< orphan*/  min; int /*<<< orphan*/  max; int /*<<< orphan*/  sum; int /*<<< orphan*/  maxIndex; int /*<<< orphan*/  minIndex; } ;
struct TYPE_16__ {int isSet; int /*<<< orphan*/  numOfNull; int /*<<< orphan*/  min; int /*<<< orphan*/  max; int /*<<< orphan*/  sum; int /*<<< orphan*/  maxIndex; int /*<<< orphan*/  minIndex; } ;
struct TYPE_20__ {int scanFlag; int hasNull; int blockStatus; int startOffset; int size; TYPE_2__* param; int /*<<< orphan*/ * ptsList; TYPE_1__ preAggVals; void* aInputElemBuf; int /*<<< orphan*/  nStartQueryTimestamp; } ;
struct TYPE_19__ {int pos; int /*<<< orphan*/  ekey; int /*<<< orphan*/  skey; } ;
struct TYPE_18__ {int /*<<< orphan*/  EKey; int /*<<< orphan*/  SKey; } ;
struct TYPE_17__ {void* pz; } ;
struct TYPE_15__ {TYPE_3__* interResultBuf; } ;
struct TYPE_14__ {int nStatus; } ;
typedef  TYPE_3__ STwaInfo ;
typedef  TYPE_4__ SQuery ;
typedef  TYPE_5__ SQLFunctionCtx ;
typedef  TYPE_6__ SField ;

/* Variables and functions */
 TYPE_12__* GET_RES_INFO (TYPE_5__*) ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_4__*) ; 
 int TSDB_FUNCSTATE_SELECTIVITY ; 
 int TSDB_FUNC_ARITHM ; 
 int TSDB_FUNC_BOTTOM ; 
 int TSDB_FUNC_DIFF ; 
 int TSDB_FUNC_FIRST_DST ; 
 int TSDB_FUNC_LAST_DST ; 
 int TSDB_FUNC_TOP ; 
 int TSDB_FUNC_TWA ; 
 int TSDB_KEYSIZE ; 
 TYPE_10__* aAggs ; 

void setExecParams(SQuery *pQuery, SQLFunctionCtx *pCtx, int64_t startQueryTimestamp, void *inputData,
                   char *primaryColumnData, int32_t size, int32_t functionId, SField *pField, bool hasNull,
                   int32_t blockStatus, void *param, int32_t scanFlag) {
  int32_t startOffset = (QUERY_IS_ASC_QUERY(pQuery)) ? pQuery->pos : pQuery->pos - (size - 1);

  pCtx->nStartQueryTimestamp = startQueryTimestamp;
  pCtx->scanFlag = scanFlag;

  pCtx->aInputElemBuf = inputData;
  pCtx->hasNull = hasNull;
  pCtx->blockStatus = blockStatus;

  if (pField != NULL) {
    pCtx->preAggVals.isSet = true;
    pCtx->preAggVals.minIndex = pField->minIndex;
    pCtx->preAggVals.maxIndex = pField->maxIndex;
    pCtx->preAggVals.sum = pField->sum;
    pCtx->preAggVals.max = pField->max;
    pCtx->preAggVals.min = pField->min;
    pCtx->preAggVals.numOfNull = pField->numOfNullPoints;
  } else {
    pCtx->preAggVals.isSet = false;
  }

  if ((aAggs[functionId].nStatus & TSDB_FUNCSTATE_SELECTIVITY) != 0 && (primaryColumnData != NULL)) {
    pCtx->ptsList = (int64_t *)(primaryColumnData + startOffset * TSDB_KEYSIZE);
  }

  if (functionId >= TSDB_FUNC_FIRST_DST && functionId <= TSDB_FUNC_LAST_DST) {
    // last_dist or first_dist function
    // store the first&last timestamp into the intermediate buffer [1], the true
    // value may be null but timestamp will never be null
    pCtx->ptsList = (int64_t *)(primaryColumnData + startOffset * TSDB_KEYSIZE);
  } else if (functionId == TSDB_FUNC_TOP || functionId == TSDB_FUNC_BOTTOM || functionId == TSDB_FUNC_TWA ||
             functionId == TSDB_FUNC_DIFF) {
    /*
     * leastsquares function needs two columns of input, currently, the x value of linear equation is set to
     * timestamp column, and the y-value is the column specified in pQuery->pSelectExpr[i].colIdxInBuffer
     *
     * top/bottom function needs timestamp to indicate when the
     * top/bottom values emerge, so does diff function
     */
    if (functionId == TSDB_FUNC_TWA) {
      STwaInfo *pTWAInfo = GET_RES_INFO(pCtx)->interResultBuf;
      pTWAInfo->SKey = pQuery->skey;
      pTWAInfo->EKey = pQuery->ekey;
    }

    pCtx->ptsList = (int64_t *)(primaryColumnData + startOffset * TSDB_KEYSIZE);

  } else if (functionId == TSDB_FUNC_ARITHM) {
    pCtx->param[0].pz = param;
  }

  pCtx->startOffset = startOffset;
  pCtx->size = size;

#if defined(_DEBUG_VIEW)
  int64_t *tsList = (int64_t *)(primaryColumnData + startOffset * TSDB_KEYSIZE);
  int64_t  s = tsList[0];
  int64_t  e = tsList[size - 1];

//    if (IS_DATA_BLOCK_LOADED(blockStatus)) {
//        dTrace("QInfo:%p query ts:%lld-%lld, offset:%d, rows:%d, bstatus:%d,
//        functId:%d", GET_QINFO_ADDR(pQuery),
//               s, e, startOffset, size, blockStatus, functionId);
//    } else {
//        dTrace("QInfo:%p block not loaded, bstatus:%d",
//        GET_QINFO_ADDR(pQuery), blockStatus);
//    }
#endif
}