#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_59__   TYPE_9__ ;
typedef  struct TYPE_58__   TYPE_8__ ;
typedef  struct TYPE_57__   TYPE_7__ ;
typedef  struct TYPE_56__   TYPE_6__ ;
typedef  struct TYPE_55__   TYPE_5__ ;
typedef  struct TYPE_54__   TYPE_4__ ;
typedef  struct TYPE_53__   TYPE_3__ ;
typedef  struct TYPE_52__   TYPE_2__ ;
typedef  struct TYPE_51__   TYPE_1__ ;
typedef  struct TYPE_50__   TYPE_19__ ;
typedef  struct TYPE_49__   TYPE_17__ ;
typedef  struct TYPE_48__   TYPE_12__ ;
typedef  struct TYPE_47__   TYPE_11__ ;
typedef  struct TYPE_46__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_57__ {scalar_t__ order; } ;
struct TYPE_52__ {scalar_t__ offset; } ;
struct TYPE_58__ {scalar_t__ skey; scalar_t__ ekey; scalar_t__ lastKey; scalar_t__ pos; scalar_t__ slot; TYPE_7__ order; int /*<<< orphan*/  precision; int /*<<< orphan*/  intervalTimeUnit; int /*<<< orphan*/  nAggTimeInterval; TYPE_6__* pSelectExpr; TYPE_2__ limit; int /*<<< orphan*/  pGroupbyExpr; scalar_t__ pointsRead; } ;
struct TYPE_59__ {int over; int /*<<< orphan*/  dataReady; scalar_t__ pointsRead; TYPE_8__ query; } ;
struct TYPE_55__ {TYPE_4__* arg; } ;
struct TYPE_56__ {TYPE_5__ pBase; } ;
struct TYPE_53__ {scalar_t__ i64; } ;
struct TYPE_54__ {TYPE_3__ argValue; } ;
struct TYPE_51__ {int vnodeIndex; } ;
struct TYPE_50__ {scalar_t__ tsOrder; } ;
struct TYPE_49__ {int /*<<< orphan*/  interpoInfo; int /*<<< orphan*/  pResult; scalar_t__ usedIndex; int /*<<< orphan*/  hashList; TYPE_19__* pTSBuf; TYPE_1__ cur; TYPE_8__* pQuery; int /*<<< orphan*/  loadCompBlockInfo; int /*<<< orphan*/  loadBlockInfo; } ;
struct TYPE_48__ {scalar_t__ lastKey; int /*<<< orphan*/  vnode; } ;
struct TYPE_47__ {scalar_t__ rawSKey; scalar_t__ rawEKey; int numOfMeters; TYPE_17__ runtimeEnv; int /*<<< orphan*/  pResult; } ;
struct TYPE_46__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_8__ SQuery ;
typedef  TYPE_9__ SQInfo ;
typedef  TYPE_10__ SPointInterpoSupporter ;
typedef  TYPE_11__ SMeterQuerySupportObj ;
typedef  TYPE_12__ SMeterObj ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_8__*) ; 
 int /*<<< orphan*/  QUERY_NOT_COMPLETED ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSQL_SO_ASC ; 
 int /*<<< orphan*/  TSQL_SO_DESC ; 
 int /*<<< orphan*/  allocMemForInterpo (TYPE_11__*,TYPE_8__*,TYPE_12__*) ; 
 scalar_t__ allocateOutputBufForGroup (TYPE_11__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  changeExecuteScanOrder (TYPE_8__*,int) ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_9__*,...) ; 
 int /*<<< orphan*/  forwardQueryStartPosIfNeeded (TYPE_9__*,TYPE_11__*,int,int) ; 
 scalar_t__ isFirstLastRowQuery (TYPE_8__*) ; 
 scalar_t__ isFixedOutputQuery (TYPE_8__*) ; 
 scalar_t__ isGroupbyNormalCol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isPointInterpoQuery (TYPE_8__*) ; 
 scalar_t__ isTopBottomQuery (TYPE_8__*) ; 
 int normalizedFirstQueryRange (int,int,TYPE_11__*,TYPE_10__*) ; 
 int /*<<< orphan*/  pointInterpSupporterDestroy (TYPE_10__*) ; 
 int /*<<< orphan*/  pointInterpSupporterInit (TYPE_8__*,TYPE_10__*) ; 
 int /*<<< orphan*/  pointInterpSupporterSetData (TYPE_9__*,TYPE_10__*) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setQueryStatus (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setScanLimitationByResultBuffer (TYPE_8__*) ; 
 scalar_t__ setupQueryRuntimeEnv (TYPE_12__*,TYPE_8__*,TYPE_17__*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  taosGetIntervalStartTimestamp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosHashInt ; 
 int /*<<< orphan*/  taosInitIntHash (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosInitInterpoInfo (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsBufSetTraverseOrder (TYPE_19__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeCheckIfDataExists (TYPE_17__*,TYPE_12__*,int*,int*) ; 
 int /*<<< orphan*/  vnodeInitDataBlockInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeInitLoadCompBlockInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeOpenAllFiles (TYPE_9__*,int /*<<< orphan*/ ) ; 

int32_t vnodeQuerySingleMeterPrepare(SQInfo *pQInfo, SMeterObj *pMeterObj, SMeterQuerySupportObj *pSupporter,
                                     void *param) {
  SQuery *pQuery = &pQInfo->query;

  if ((QUERY_IS_ASC_QUERY(pQuery) && (pQuery->skey > pQuery->ekey)) ||
      (!QUERY_IS_ASC_QUERY(pQuery) && (pQuery->ekey > pQuery->skey))) {
    dTrace("QInfo:%p no result in time range %lld-%lld, order %d", pQInfo, pQuery->skey, pQuery->ekey,
           pQuery->order.order);

    sem_post(&pQInfo->dataReady);
    pQInfo->over = 1;

    return TSDB_CODE_SUCCESS;
  }

  setScanLimitationByResultBuffer(pQuery);
  changeExecuteScanOrder(pQuery, false);

  pQInfo->over = 0;
  pQInfo->pointsRead = 0;
  pQuery->pointsRead = 0;

  // dataInCache requires lastKey value
  pQuery->lastKey = pQuery->skey;

  vnodeInitDataBlockInfo(&pSupporter->runtimeEnv.loadBlockInfo);
  vnodeInitLoadCompBlockInfo(&pSupporter->runtimeEnv.loadCompBlockInfo);

  // check data in file or cache
  bool dataInCache = true;
  bool dataInDisk = true;
  pSupporter->runtimeEnv.pQuery = pQuery;

  vnodeCheckIfDataExists(&pSupporter->runtimeEnv, pMeterObj, &dataInDisk, &dataInCache);

  /* data in file or cache is not qualified for the query. abort */
  if (!(dataInCache || dataInDisk)) {
    dTrace("QInfo:%p no result in query", pQInfo);
    sem_post(&pQInfo->dataReady);
    pQInfo->over = 1;

    return TSDB_CODE_SUCCESS;
  }

  pSupporter->runtimeEnv.pTSBuf = param;
  pSupporter->runtimeEnv.cur.vnodeIndex = -1;
  if (param != NULL) {
    int16_t order = (pQuery->order.order == pSupporter->runtimeEnv.pTSBuf->tsOrder) ? TSQL_SO_ASC : TSQL_SO_DESC;
    tsBufSetTraverseOrder(pSupporter->runtimeEnv.pTSBuf, order);
  }

  // create runtime environment
  int32_t ret = setupQueryRuntimeEnv(pMeterObj, pQuery, &pSupporter->runtimeEnv, NULL, pQuery->order.order, false);
  if (ret != TSDB_CODE_SUCCESS) {
    return ret;
  }

  vnodeOpenAllFiles(pQInfo, pMeterObj->vnode);

  if (isGroupbyNormalCol(pQuery->pGroupbyExpr)) {
    if ((ret = allocateOutputBufForGroup(pSupporter, pQuery, false)) != TSDB_CODE_SUCCESS) {
      return ret;
    }

    pSupporter->runtimeEnv.hashList = taosInitIntHash(10039, sizeof(void *), taosHashInt);
    pSupporter->runtimeEnv.usedIndex = 0;
    pSupporter->runtimeEnv.pResult = pSupporter->pResult;
  }

  // in case of last_row query, we set the query timestamp to pMeterObj->lastKey;
  if (isFirstLastRowQuery(pQuery)) {
    pQuery->skey = pMeterObj->lastKey;
    pQuery->ekey = pMeterObj->lastKey;
    pQuery->lastKey = pQuery->skey;
  }

  pSupporter->rawSKey = pQuery->skey;
  pSupporter->rawEKey = pQuery->ekey;

  /* query on single table */
  pSupporter->numOfMeters = 1;
  setQueryStatus(pQuery, QUERY_NOT_COMPLETED);

  SPointInterpoSupporter interpInfo = {0};
  pointInterpSupporterInit(pQuery, &interpInfo);

  if ((normalizedFirstQueryRange(dataInDisk, dataInCache, pSupporter, &interpInfo) == false) ||
      (isFixedOutputQuery(pQuery) && !isTopBottomQuery(pQuery) && (pQuery->limit.offset > 0)) ||
      (isTopBottomQuery(pQuery) && pQuery->limit.offset >= pQuery->pSelectExpr[1].pBase.arg[0].argValue.i64)) {
    sem_post(&pQInfo->dataReady);
    pQInfo->over = 1;

    pointInterpSupporterDestroy(&interpInfo);
    return TSDB_CODE_SUCCESS;
  }

  /*
   * here we set the value for before and after the specified time into the
   * parameter for interpolation query
   */
  pointInterpSupporterSetData(pQInfo, &interpInfo);
  pointInterpSupporterDestroy(&interpInfo);

  if (!forwardQueryStartPosIfNeeded(pQInfo, pSupporter, dataInDisk, dataInCache)) {
    return TSDB_CODE_SUCCESS;
  }

  int64_t rs = taosGetIntervalStartTimestamp(pSupporter->rawSKey, pQuery->nAggTimeInterval, pQuery->intervalTimeUnit,
                                             pQuery->precision);
  taosInitInterpoInfo(&pSupporter->runtimeEnv.interpoInfo, pQuery->order.order, rs, 0, 0);
  allocMemForInterpo(pSupporter, pQuery, pMeterObj);

  if (!isPointInterpoQuery(pQuery)) {
    assert(pQuery->pos >= 0 && pQuery->slot >= 0);
  }

  // the pQuery->skey is changed during normalizedFirstQueryRange, so set the newest lastkey value
  pQuery->lastKey = pQuery->skey;
  return TSDB_CODE_SUCCESS;
}