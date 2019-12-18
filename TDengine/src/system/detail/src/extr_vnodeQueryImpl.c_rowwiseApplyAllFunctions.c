#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_27__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_10__ ;

/* Type definitions */
typedef  size_t int64_t ;
typedef  size_t int32_t ;
typedef  size_t int16_t ;
struct TYPE_42__ {scalar_t__ startOffset; } ;
struct TYPE_35__ {int /*<<< orphan*/  order; } ;
struct TYPE_41__ {size_t numOfOutputCols; size_t numOfFilterCols; int checkBufferInLoop; size_t pointsOffset; size_t pos; scalar_t__ lastKey; TYPE_5__* pSelectExpr; TYPE_2__ order; TYPE_6__* pFilterInfo; int /*<<< orphan*/  precision; int /*<<< orphan*/  intervalTimeUnit; int /*<<< orphan*/  nAggTimeInterval; scalar_t__ ekey; scalar_t__ skey; int /*<<< orphan*/  pGroupbyExpr; } ;
struct TYPE_40__ {TYPE_12__* pTSBuf; int /*<<< orphan*/  scanFlag; int /*<<< orphan*/  blockStatus; TYPE_8__* pQuery; TYPE_9__* pCtx; } ;
struct TYPE_31__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  type; int /*<<< orphan*/  colId; } ;
struct TYPE_33__ {size_t colIdxInBuf; size_t colIdx; TYPE_10__ data; } ;
struct TYPE_39__ {TYPE_1__ info; int /*<<< orphan*/  pData; } ;
struct TYPE_37__ {size_t functionId; } ;
struct TYPE_38__ {TYPE_4__ pBase; } ;
struct TYPE_36__ {int /*<<< orphan*/  order; } ;
struct TYPE_34__ {int /*<<< orphan*/  (* xFunctionF ) (TYPE_9__*,size_t) ;} ;
struct TYPE_32__ {TYPE_3__ cur; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_6__ SSingleColumnFilterInfo ;
typedef  TYPE_7__ SQueryRuntimeEnv ;
typedef  TYPE_8__ SQuery ;
typedef  TYPE_9__ SQLFunctionCtx ;
typedef  int /*<<< orphan*/  SQInfo ;
typedef  int /*<<< orphan*/  SField ;
typedef  TYPE_10__ SColumnInfo ;
typedef  int /*<<< orphan*/  SBlockInfo ;
typedef  int /*<<< orphan*/  SArithmeticSupport ;

/* Variables and functions */
 size_t GET_COL_DATA_POS (TYPE_8__*,size_t,size_t) ; 
 size_t GET_FORWARD_DIRECTION_FACTOR (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_QINFO_ADDR (TYPE_8__*) ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_8__*) ; 
 int /*<<< orphan*/  QUERY_NO_DATA_TO_CHECK ; 
 size_t TSDB_CODE_SUCCESS ; 
 size_t TS_JOIN_TAG_NOT_EQUALS ; 
 size_t TS_JOIN_TS_EQUAL ; 
 size_t TS_JOIN_TS_NOT_EQUALS ; 
 TYPE_27__* aAggs ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 int /*<<< orphan*/  doGetDataBlocks (int,TYPE_7__*,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t doTSJoinFilter (TYPE_7__*,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ functionNeedToExecute (TYPE_7__*,TYPE_9__*,size_t) ; 
 char* getDataBlocks (TYPE_7__*,char*,int /*<<< orphan*/ *,size_t,size_t,int) ; 
 char* getGroupbyColumnData (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,size_t*,size_t*) ; 
 size_t getNumOfResult (TYPE_7__*) ; 
 int hasNullVal (TYPE_8__*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int isGroupbyNormalCol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qTrace (char*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setExecParams (TYPE_8__*,TYPE_9__*,size_t,char*,char*,size_t,size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t setGroupResultForKey (TYPE_7__*,char*,size_t,char*) ; 
 int /*<<< orphan*/  setQueryStatus (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*,size_t) ; 
 size_t taosGetIntervalStartTimestamp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsBufNextPos (TYPE_12__*) ; 
 int /*<<< orphan*/  vnodeDoFilterData (TYPE_8__*,size_t) ; 

__attribute__((used)) static int32_t rowwiseApplyAllFunctions(SQueryRuntimeEnv *pRuntimeEnv, int32_t *forwardStep, TSKEY *primaryKeyCol,
                                        char *data, SField *pFields, SBlockInfo *pBlockInfo, bool isDiskFileBlock) {
  SQLFunctionCtx *pCtx = pRuntimeEnv->pCtx;
  SQuery *        pQuery = pRuntimeEnv->pQuery;

  int64_t prevNumOfRes = 0;
  bool    groupbyStateValue = isGroupbyNormalCol(pQuery->pGroupbyExpr);

  if (!groupbyStateValue) {
    prevNumOfRes = getNumOfResult(pRuntimeEnv);
  }

  SArithmeticSupport *sasArray = calloc((size_t)pQuery->numOfOutputCols, sizeof(SArithmeticSupport));

  int16_t type = 0;
  int16_t bytes = 0;

  char *groupbyColumnData = NULL;
  if (groupbyStateValue) {
    groupbyColumnData = getGroupbyColumnData(pRuntimeEnv, pFields, pBlockInfo, data, isDiskFileBlock, &type, &bytes);
  }

  for (int32_t k = 0; k < pQuery->numOfOutputCols; ++k) {
    int32_t functionId = pQuery->pSelectExpr[k].pBase.functionId;

    bool  hasNull = hasNullVal(pQuery, k, pBlockInfo, pFields, isDiskFileBlock);
    char *dataBlock = getDataBlocks(pRuntimeEnv, data, &sasArray[k], k, *forwardStep, isDiskFileBlock);

    TSKEY   ts = QUERY_IS_ASC_QUERY(pQuery) ? pQuery->skey : pQuery->ekey;
    int64_t alignedTimestamp = taosGetIntervalStartTimestamp(ts, pQuery->nAggTimeInterval, pQuery->intervalTimeUnit,
                                                             pQuery->precision);

    setExecParams(pQuery, &pCtx[k], alignedTimestamp, dataBlock, (char *)primaryKeyCol, (*forwardStep), functionId,
                  pFields, hasNull, pRuntimeEnv->blockStatus, &sasArray[k], pRuntimeEnv->scanFlag);
  }

  // set the input column data
  for (int32_t k = 0; k < pQuery->numOfFilterCols; ++k) {
    SSingleColumnFilterInfo *pFilterInfo = &pQuery->pFilterInfo[k];
    int32_t                  colIdx = isDiskFileBlock ? pFilterInfo->info.colIdxInBuf : pFilterInfo->info.colIdx;
    SColumnInfo *            pColumnInfo = &pFilterInfo->info.data;

    /*
     * NOTE: here the tbname/tags column cannot reach here, since it will never be a filter column,
     * so we do NOT check if is a tag or not
     */
    pFilterInfo->pData = doGetDataBlocks(isDiskFileBlock, pRuntimeEnv, data, colIdx, pColumnInfo->colId,
                                         pColumnInfo->type, pColumnInfo->bytes, pFilterInfo->info.colIdxInBuf);
  }

  int32_t numOfRes = 0;
  int32_t step = GET_FORWARD_DIRECTION_FACTOR(pQuery->order.order);

  // from top to bottom in desc
  // from bottom to top in asc order
  if (pRuntimeEnv->pTSBuf != NULL) {
    SQInfo *pQInfo = (SQInfo *)GET_QINFO_ADDR(pQuery);
    qTrace("QInfo:%p process data rows, numOfRows:%d, query order:%d, ts comp order:%d", pQInfo, *forwardStep,
           pQuery->order.order, pRuntimeEnv->pTSBuf->cur.order);
  }

  for (int32_t j = 0; j < (*forwardStep); ++j) {
    int32_t offset = GET_COL_DATA_POS(pQuery, j, step);

    if (pRuntimeEnv->pTSBuf != NULL) {
      int32_t r = doTSJoinFilter(pRuntimeEnv, offset);

      if (r == TS_JOIN_TAG_NOT_EQUALS) {
        break;
      } else if (r == TS_JOIN_TS_NOT_EQUALS) {
        continue;
      } else {
        assert(r == TS_JOIN_TS_EQUAL);
      }
    }

    if (pQuery->numOfFilterCols > 0 && (!vnodeDoFilterData(pQuery, offset))) {
      continue;
    }

    // decide which group this rows belongs to according to current state value
    if (groupbyStateValue) {
      char *stateVal = groupbyColumnData + bytes * offset;

      int32_t ret = setGroupResultForKey(pRuntimeEnv, stateVal, type, groupbyColumnData);
      if (ret != TSDB_CODE_SUCCESS) {  // null data, too many state code
        continue;
      }
    }

    // all startOffset are identical
    offset -= pCtx[0].startOffset;

    for (int32_t k = 0; k < pQuery->numOfOutputCols; ++k) {
      int32_t functionId = pQuery->pSelectExpr[k].pBase.functionId;
      if (functionNeedToExecute(pRuntimeEnv, &pCtx[k], functionId)) {
        aAggs[functionId].xFunctionF(&pCtx[k], offset);
      }
    }

    if (pRuntimeEnv->pTSBuf != NULL) {
      // if timestamp filter list is empty, quit current query
      if (!tsBufNextPos(pRuntimeEnv->pTSBuf)) {
        setQueryStatus(pQuery, QUERY_NO_DATA_TO_CHECK);
        break;
      }
    }

    /*
     * pointsOffset is the maximum available space in result buffer update the actual forward step for query that
     * requires checking buffer during loop
     */
    if ((pQuery->checkBufferInLoop == 1) && (++numOfRes) >= pQuery->pointsOffset) {
      pQuery->lastKey = primaryKeyCol[pQuery->pos + j * step] + step;
      *forwardStep = j + 1;
      break;
    }
  }

  free(sasArray);

  /*
   * No need to calculate the number of output results for groupby normal columns
   * because the results of group by normal column is put into intermediate buffer.
   */
  int32_t num = 0;
  if (!groupbyStateValue) {
    num = getNumOfResult(pRuntimeEnv) - prevNumOfRes;
  }

  return num;
}