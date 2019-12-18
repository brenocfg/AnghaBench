#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_9__ ;
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_12__ ;
typedef  struct TYPE_39__   TYPE_11__ ;
typedef  struct TYPE_38__   TYPE_10__ ;

/* Type definitions */
struct TYPE_44__ {size_t numOfSubSet; size_t* starterPos; size_t numOfSids; } ;
typedef  TYPE_4__ tSidSet ;
typedef  scalar_t__ int64_t ;
typedef  size_t int32_t ;
struct TYPE_49__ {TYPE_2__* resultInfo; int /*<<< orphan*/  numOfRows; } ;
struct TYPE_48__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_43__ {scalar_t__ offset; scalar_t__ limit; } ;
struct TYPE_46__ {scalar_t__ pointsRead; scalar_t__ pointsToRead; size_t numOfOutputCols; scalar_t__ numOfFilterCols; scalar_t__ pointsOffset; TYPE_3__ limit; scalar_t__ skey; int /*<<< orphan*/  pGroupbyExpr; int /*<<< orphan*/  over; scalar_t__ lastKey; scalar_t__ ekey; } ;
struct TYPE_47__ {int /*<<< orphan*/  pointsReturned; int /*<<< orphan*/  pointsRead; TYPE_11__* pMeterQuerySupporter; TYPE_6__ query; } ;
struct TYPE_45__ {size_t usedIndex; size_t numOfFiles; TYPE_9__* pResult; TYPE_1__* pTSBuf; int /*<<< orphan*/  cur; int /*<<< orphan*/  pMeterObj; int /*<<< orphan*/ * pHeaderFiles; int /*<<< orphan*/  hashList; } ;
struct TYPE_42__ {int /*<<< orphan*/  numOfRes; } ;
struct TYPE_41__ {int /*<<< orphan*/  cur; } ;
struct TYPE_40__ {scalar_t__ lastKey; int /*<<< orphan*/  vnode; } ;
struct TYPE_39__ {size_t subgroupIdx; size_t meterIdx; size_t numOfMeters; TYPE_4__* pSidSet; scalar_t__ rawEKey; scalar_t__ rawSKey; TYPE_9__* pResult; int /*<<< orphan*/  pMeterObj; TYPE_5__ runtimeEnv; TYPE_10__** pMeterSidExtInfo; } ;
struct TYPE_38__ {int /*<<< orphan*/  sid; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_5__ SQueryRuntimeEnv ;
typedef  TYPE_6__ SQuery ;
typedef  TYPE_7__ SQInfo ;
typedef  TYPE_8__ SPointInterpoSupporter ;
typedef  TYPE_9__ SOutputRes ;
typedef  TYPE_10__ SMeterSidExtInfo ;
typedef  TYPE_11__ SMeterQuerySupportObj ;
typedef  TYPE_12__ SMeterObj ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POINTER_BYTES ; 
 int QUERY_COMPLETED ; 
 int QUERY_NO_DATA_TO_CHECK ; 
 int QUERY_RESBUF_FULL ; 
 int Q_STATUS_EQUAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clearGroupResultBuf (TYPE_9__*,size_t) ; 
 int /*<<< orphan*/  copyFromGroupBuf (TYPE_7__*,TYPE_9__*) ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_7__*,int /*<<< orphan*/ ,size_t,size_t,...) ; 
 scalar_t__ doCheckMetersInGroup (TYPE_7__*,size_t,size_t) ; 
 int /*<<< orphan*/  doFinalizeResult (TYPE_5__*) ; 
 scalar_t__ doRevisedResultsByLimit (TYPE_7__*) ; 
 int /*<<< orphan*/  doSkipResults (TYPE_5__*) ; 
 int /*<<< orphan*/  forwardQueryStartPosition (TYPE_5__*) ; 
 TYPE_12__* getMeterObj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getNumOfResult (TYPE_5__*) ; 
 scalar_t__ isFirstLastRowQuery (TYPE_6__*) ; 
 scalar_t__ isGroupbyEachTable (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ isGroupbyNormalCol (int /*<<< orphan*/ ) ; 
 scalar_t__ isPointInterpoQuery (TYPE_6__*) ; 
 scalar_t__ isQueryKilled (TYPE_6__*) ; 
 int /*<<< orphan*/  moveDescOrderResultsToFront (TYPE_5__*) ; 
 int /*<<< orphan*/  multimeterMultioutputHelper (TYPE_7__*,int*,int*,size_t,int /*<<< orphan*/ ) ; 
 int normalizedFirstQueryRange (int,int,TYPE_11__*,TYPE_8__*) ; 
 int /*<<< orphan*/  resetCtxOutputBuf (TYPE_5__*) ; 
 int /*<<< orphan*/  resetMMapWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setQueryStatus (TYPE_6__*,int) ; 
 int /*<<< orphan*/  taosCleanUpIntHash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosHashInt ; 
 int /*<<< orphan*/  taosInitIntHash (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeScanAllData (TYPE_5__*) ; 
 int /*<<< orphan*/  vnodeUpdateFilterColumnIndex (TYPE_6__*) ; 
 int /*<<< orphan*/  vnodeUpdateQueryColumnIndex (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vnodeMultiMeterMultiOutputProcessor(SQInfo *pQInfo) {
  SMeterQuerySupportObj *pSupporter = pQInfo->pMeterQuerySupporter;

  SMeterSidExtInfo **pMeterSidExtInfo = pSupporter->pMeterSidExtInfo;
  SQueryRuntimeEnv * pRuntimeEnv = &pSupporter->runtimeEnv;

  SQuery * pQuery = &pQInfo->query;
  tSidSet *pSids = pSupporter->pSidSet;

  SMeterObj *pOneMeter = getMeterObj(pSupporter->pMeterObj, pMeterSidExtInfo[0]->sid);

  resetCtxOutputBuf(pRuntimeEnv);

  if (isPointInterpoQuery(pQuery)) {
    assert(pQuery->limit.offset == 0 && pQuery->limit.limit != 0);

    while (pSupporter->subgroupIdx < pSids->numOfSubSet) {
      int32_t start = pSids->starterPos[pSupporter->subgroupIdx];
      int32_t end = pSids->starterPos[pSupporter->subgroupIdx + 1] - 1;

      if (isFirstLastRowQuery(pQuery)) {
        dTrace("QInfo:%p last_row query on vid:%d, numOfGroups:%d, current group:%d", pQInfo, pOneMeter->vnode,
               pSids->numOfSubSet, pSupporter->subgroupIdx);

        TSKEY   key = -1;
        int32_t index = -1;

        // choose the last key for one group
        pSupporter->meterIdx = start;

        for (int32_t k = start; k <= end; ++k, pSupporter->meterIdx++) {
          if (isQueryKilled(pQuery)) {
            setQueryStatus(pQuery, QUERY_NO_DATA_TO_CHECK);
            return;
          }

          // get the last key of meters that belongs to this group
          SMeterObj *pMeterObj = getMeterObj(pSupporter->pMeterObj, pMeterSidExtInfo[k]->sid);
          if (pMeterObj != NULL) {
            if (key < pMeterObj->lastKey) {
              key = pMeterObj->lastKey;
              index = k;
            }
          }
        }

        pQuery->skey = key;
        pQuery->ekey = key;
        pSupporter->rawSKey = key;
        pSupporter->rawEKey = key;

        int64_t num = doCheckMetersInGroup(pQInfo, index, start);
        assert(num >= 0);
      } else {
        dTrace("QInfo:%p interp query on vid:%d, numOfGroups:%d, current group:%d", pQInfo, pOneMeter->vnode,
               pSids->numOfSubSet, pSupporter->subgroupIdx);

        for (int32_t k = start; k <= end; ++k) {
          if (isQueryKilled(pQuery)) {
            setQueryStatus(pQuery, QUERY_NO_DATA_TO_CHECK);
            return;
          }

          pQuery->skey = pSupporter->rawSKey;
          pQuery->ekey = pSupporter->rawEKey;

          int64_t num = doCheckMetersInGroup(pQInfo, k, start);
          if (num == 1) {
            break;
          }
        }
      }

      pSupporter->subgroupIdx++;

      // output buffer is full, return to client
      if (pQuery->pointsRead >= pQuery->pointsToRead) {
        break;
      }
    }
  } else {
    // this procedure treats all tables as single group
    assert(pSupporter->meterIdx >= 0);

    /*
     * if the subgroup index is larger than 0, results generated by group by tbname,k is existed.
     * we need to return it to client in the first place.
     */
    if (pSupporter->subgroupIdx > 0) {
      copyFromGroupBuf(pQInfo, pSupporter->pResult);
      pQInfo->pointsRead += pQuery->pointsRead;

      if (pQuery->pointsRead > 0) {
        return;
      }
    }

    if (pSupporter->meterIdx >= pSids->numOfSids) {
      return;
    }

    for (int32_t i = 0; i < pRuntimeEnv->usedIndex; ++i) {
      SOutputRes *pOneRes = &pRuntimeEnv->pResult[i];
      clearGroupResultBuf(pOneRes, pQuery->numOfOutputCols);
    }

    pRuntimeEnv->usedIndex = 0;
    taosCleanUpIntHash(pRuntimeEnv->hashList);

    int32_t primeHashSlot = 10039;
    pRuntimeEnv->hashList = taosInitIntHash(primeHashSlot, POINTER_BYTES, taosHashInt);

    while (pSupporter->meterIdx < pSupporter->numOfMeters) {
      int32_t k = pSupporter->meterIdx;

      if (isQueryKilled(pQuery)) {
        setQueryStatus(pQuery, QUERY_NO_DATA_TO_CHECK);
        return;
      }

      bool dataInDisk = true;
      bool dataInCache = true;
      if (!multimeterMultioutputHelper(pQInfo, &dataInDisk, &dataInCache, k, 0)) {
        pQuery->skey = pSupporter->rawSKey;
        pQuery->ekey = pSupporter->rawEKey;

        pSupporter->meterIdx++;
        continue;
      }

#if DEFAULT_IO_ENGINE == IO_ENGINE_MMAP
      for (int32_t i = 0; i < pRuntimeEnv->numOfFiles; ++i) {
        resetMMapWindow(&pRuntimeEnv->pHeaderFiles[i]);
      }
#endif

      SPointInterpoSupporter pointInterpSupporter = {0};
      if (normalizedFirstQueryRange(dataInDisk, dataInCache, pSupporter, &pointInterpSupporter) == false) {
        pQuery->skey = pSupporter->rawSKey;
        pQuery->ekey = pSupporter->rawEKey;

        pSupporter->meterIdx++;
        continue;
      }

      // TODO handle the limit problem
      if (pQuery->numOfFilterCols == 0 && pQuery->limit.offset > 0) {
        forwardQueryStartPosition(pRuntimeEnv);

        if (Q_STATUS_EQUAL(pQuery->over, QUERY_NO_DATA_TO_CHECK | QUERY_COMPLETED)) {
          pQuery->skey = pSupporter->rawSKey;
          pQuery->ekey = pSupporter->rawEKey;

          pSupporter->meterIdx++;
          continue;
        }
      }

      vnodeUpdateQueryColumnIndex(pQuery, pRuntimeEnv->pMeterObj);
      vnodeUpdateFilterColumnIndex(pQuery);

      vnodeScanAllData(pRuntimeEnv);

      pQuery->pointsRead = getNumOfResult(pRuntimeEnv);
      doSkipResults(pRuntimeEnv);

      // the limitation of output result is reached, set the query completed
      if (doRevisedResultsByLimit(pQInfo)) {
        pSupporter->meterIdx = pSupporter->pSidSet->numOfSids;
        break;
      }

      if (Q_STATUS_EQUAL(pQuery->over, QUERY_NO_DATA_TO_CHECK | QUERY_COMPLETED)) {
        /*
         * query range is identical in terms of all meters involved in query,
         * so we need to restore them at the *beginning* of query on each meter,
         * not the consecutive query on meter on which is aborted due to buffer limitation
         * to ensure that, we can reset the query range once query on a meter is completed.
         */
        pQuery->skey = pSupporter->rawSKey;
        pQuery->ekey = pSupporter->rawEKey;
        pSupporter->meterIdx++;

        // if the buffer is full or group by each table, we need to jump out of the loop
        if (Q_STATUS_EQUAL(pQuery->over, QUERY_RESBUF_FULL) ||
            isGroupbyEachTable(pQuery->pGroupbyExpr, pSupporter->pSidSet)) {
          break;
        }

      } else {
        // forward query range
        pQuery->skey = pQuery->lastKey;

        // all data in the result buffer are skipped due to the offset, continue to retrieve data from current meter
        if (pQuery->pointsRead == 0) {
          assert(!Q_STATUS_EQUAL(pQuery->over, QUERY_RESBUF_FULL));
          continue;
        } else {
          // buffer is full, wait for the next round to retrieve data from current meter
          assert(Q_STATUS_EQUAL(pQuery->over, QUERY_RESBUF_FULL));
          break;
        }
      }
    }
  }

  if (!isGroupbyNormalCol(pQuery->pGroupbyExpr) && !isFirstLastRowQuery(pQuery)) {
    doFinalizeResult(pRuntimeEnv);
  }

  if (pRuntimeEnv->pTSBuf != NULL) {
    pRuntimeEnv->cur = pRuntimeEnv->pTSBuf->cur;
  }

  if (isGroupbyNormalCol(pQuery->pGroupbyExpr)) {
    for (int32_t i = 0; i < pRuntimeEnv->usedIndex; ++i) {
      SOutputRes *buf = &pRuntimeEnv->pResult[i];
      for (int32_t j = 0; j < pQuery->numOfOutputCols; ++j) {
        buf->numOfRows = MAX(buf->numOfRows, buf->resultInfo[j].numOfRes);
      }
    }

    pQInfo->pMeterQuerySupporter->subgroupIdx = 0;
    pQuery->pointsRead = 0;
    copyFromGroupBuf(pQInfo, pRuntimeEnv->pResult);
  }

  pQInfo->pointsRead += pQuery->pointsRead;
  pQuery->pointsOffset = pQuery->pointsToRead;

  moveDescOrderResultsToFront(pRuntimeEnv);

  dTrace(
      "QInfo %p vid:%d, numOfMeters:%d, index:%d, numOfGroups:%d, %d points returned, totalRead:%d totalReturn:%d,"
      "next skey:%lld, offset:%lld",
      pQInfo, pOneMeter->vnode, pSids->numOfSids, pSupporter->meterIdx, pSids->numOfSubSet, pQuery->pointsRead,
      pQInfo->pointsRead, pQInfo->pointsReturned, pQuery->skey, pQuery->limit.offset);
}