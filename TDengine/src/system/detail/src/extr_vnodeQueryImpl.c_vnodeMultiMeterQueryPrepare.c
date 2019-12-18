#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_16__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/ * pSchema; } ;
typedef  TYPE_4__ tTagSchema ;
typedef  int /*<<< orphan*/  tFilePage ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_36__ {int /*<<< orphan*/  vnode; } ;
struct TYPE_30__ {int vnodeIndex; } ;
struct TYPE_28__ {int numOfRowsPerPage; int /*<<< orphan*/  interpoInfo; int /*<<< orphan*/  pResult; scalar_t__ usedIndex; int /*<<< orphan*/  hashList; TYPE_12__* pTSBuf; TYPE_2__ cur; int /*<<< orphan*/  loadCompBlockInfo; int /*<<< orphan*/  loadBlockInfo; } ;
struct TYPE_35__ {scalar_t__ rawEKey; scalar_t__ rawSKey; int numOfPages; int numOfMeters; int lastPageId; int bufSize; scalar_t__ meterOutputMMapBuf; TYPE_16__ runtimeEnv; int /*<<< orphan*/  extBufFile; int /*<<< orphan*/  meterOutputFd; int /*<<< orphan*/  pResult; TYPE_13__* pSidSet; int /*<<< orphan*/  pMeterObj; } ;
struct TYPE_34__ {int over; scalar_t__ pointsRead; int /*<<< orphan*/  dataReady; TYPE_7__* pMeterQuerySupporter; } ;
struct TYPE_31__ {scalar_t__ order; } ;
struct TYPE_33__ {scalar_t__ skey; scalar_t__ ekey; scalar_t__ lastKey; scalar_t__ nAggTimeInterval; int rowSize; TYPE_3__ order; int /*<<< orphan*/  precision; int /*<<< orphan*/  intervalTimeUnit; int /*<<< orphan*/  interpoType; int /*<<< orphan*/  pGroupbyExpr; scalar_t__ pointsRead; } ;
struct TYPE_29__ {int /*<<< orphan*/  sid; } ;
struct TYPE_27__ {TYPE_1__** pSids; TYPE_4__* pTagSchema; } ;
struct TYPE_26__ {scalar_t__ tsOrder; } ;
typedef  int /*<<< orphan*/  TSKEY ;
typedef  int /*<<< orphan*/  SSchema ;
typedef  TYPE_5__ SQuery ;
typedef  TYPE_6__ SQInfo ;
typedef  TYPE_7__ SMeterQuerySupportObj ;
typedef  TYPE_8__ SMeterObj ;

/* Variables and functions */
 int DEFAULT_INTERN_BUF_SIZE ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_5__*) ; 
 scalar_t__ TSDB_CODE_SERV_OUT_OF_MEMORY ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_INTERPO_NONE ; 
 int /*<<< orphan*/  TSQL_SO_ASC ; 
 int /*<<< orphan*/  TSQL_SO_DESC ; 
 int /*<<< orphan*/  VALIDFD (int /*<<< orphan*/ ) ; 
 scalar_t__ allocateOutputBufForGroup (TYPE_7__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  changeExecuteScanOrder (TYPE_5__*,int) ; 
 int /*<<< orphan*/  dError (char*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_6__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ftruncate (int /*<<< orphan*/ ,int) ; 
 TYPE_8__* getMeterObj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getTmpfilePath (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isGroupbyNormalCol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isPointInterpoQuery (TYPE_5__*) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setScanLimitationByResultBuffer (TYPE_5__*) ; 
 scalar_t__ setupQueryRuntimeEnv (TYPE_8__*,TYPE_5__*,TYPE_16__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tSidSetSort (TYPE_13__*) ; 
 int /*<<< orphan*/  taosGetIntervalStartTimestamp (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosHashInt ; 
 int /*<<< orphan*/  taosInitIntHash (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosInitInterpoInfo (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsBufSetTraverseOrder (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeInitDataBlockInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeInitLoadCompBlockInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeOpenAllFiles (TYPE_6__*,int /*<<< orphan*/ ) ; 

int32_t vnodeMultiMeterQueryPrepare(SQInfo *pQInfo, SQuery *pQuery, void *param) {
  SMeterQuerySupportObj *pSupporter = pQInfo->pMeterQuerySupporter;

  if ((QUERY_IS_ASC_QUERY(pQuery) && (pQuery->skey > pQuery->ekey)) ||
      (!QUERY_IS_ASC_QUERY(pQuery) && (pQuery->ekey > pQuery->skey))) {
    dTrace("QInfo:%p no result in time range %lld-%lld, order %d", pQInfo, pQuery->skey, pQuery->ekey,
           pQuery->order.order);

    sem_post(&pQInfo->dataReady);
    pQInfo->over = 1;

    return TSDB_CODE_SUCCESS;
  }

  pQInfo->over = 0;
  pQInfo->pointsRead = 0;
  pQuery->pointsRead = 0;

  changeExecuteScanOrder(pQuery, true);

  vnodeInitDataBlockInfo(&pSupporter->runtimeEnv.loadBlockInfo);
  vnodeInitLoadCompBlockInfo(&pSupporter->runtimeEnv.loadCompBlockInfo);

  /*
   * since we employ the output control mechanism in main loop.
   * so, disable it during data block scan procedure.
   */
  setScanLimitationByResultBuffer(pQuery);

  // save raw query range for applying to each subgroup
  pSupporter->rawEKey = pQuery->ekey;
  pSupporter->rawSKey = pQuery->skey;
  pQuery->lastKey = pQuery->skey;

  // create runtime environment
  SSchema *pTagSchema = NULL;

  tTagSchema *pTagSchemaInfo = pSupporter->pSidSet->pTagSchema;
  if (pTagSchemaInfo != NULL) {
    pTagSchema = pTagSchemaInfo->pSchema;
  }

  // get one queried meter
  SMeterObj *pMeter = getMeterObj(pSupporter->pMeterObj, pSupporter->pSidSet->pSids[0]->sid);

  pSupporter->runtimeEnv.pTSBuf = param;
  pSupporter->runtimeEnv.cur.vnodeIndex = -1;

  // set the ts-comp file traverse order
  if (param != NULL) {
    int16_t order = (pQuery->order.order == pSupporter->runtimeEnv.pTSBuf->tsOrder) ? TSQL_SO_ASC : TSQL_SO_DESC;
    tsBufSetTraverseOrder(pSupporter->runtimeEnv.pTSBuf, order);
  }

  int32_t ret = setupQueryRuntimeEnv(pMeter, pQuery, &pSupporter->runtimeEnv, pTagSchema, TSQL_SO_ASC, true);
  if (ret != TSDB_CODE_SUCCESS) {
    return ret;
  }

  tSidSetSort(pSupporter->pSidSet);
  vnodeOpenAllFiles(pQInfo, pMeter->vnode);

  if ((ret = allocateOutputBufForGroup(pSupporter, pQuery, true)) != TSDB_CODE_SUCCESS) {
    return ret;
  }

  if (isGroupbyNormalCol(pQuery->pGroupbyExpr)) {  // group by columns not tags;
    pSupporter->runtimeEnv.hashList = taosInitIntHash(10039, sizeof(void *), taosHashInt);
    pSupporter->runtimeEnv.usedIndex = 0;
    pSupporter->runtimeEnv.pResult = pSupporter->pResult;
  }

  if (pQuery->nAggTimeInterval != 0) {
    getTmpfilePath("tb_metric_mmap", pSupporter->extBufFile);
    pSupporter->meterOutputFd = open(pSupporter->extBufFile, O_CREAT | O_RDWR, 0666);

    if (!VALIDFD(pSupporter->meterOutputFd)) {
      dError("QInfo:%p failed to create file: %s on disk. %s", pQInfo, pSupporter->extBufFile, strerror(errno));
      return TSDB_CODE_SERV_OUT_OF_MEMORY;
    }

    // set 4k page for each meter
    pSupporter->numOfPages = pSupporter->numOfMeters;

    ftruncate(pSupporter->meterOutputFd, pSupporter->numOfPages * DEFAULT_INTERN_BUF_SIZE);
    pSupporter->runtimeEnv.numOfRowsPerPage = (DEFAULT_INTERN_BUF_SIZE - sizeof(tFilePage)) / pQuery->rowSize;
    pSupporter->lastPageId = -1;
    pSupporter->bufSize = pSupporter->numOfPages * DEFAULT_INTERN_BUF_SIZE;

    pSupporter->meterOutputMMapBuf =
        mmap(NULL, pSupporter->bufSize, PROT_READ | PROT_WRITE, MAP_SHARED, pSupporter->meterOutputFd, 0);
    if (pSupporter->meterOutputMMapBuf == MAP_FAILED) {
      dError("QInfo:%p failed to map data file: %s to disk. %s", pQInfo, pSupporter->extBufFile, strerror(errno));
      return TSDB_CODE_SERV_OUT_OF_MEMORY;
    }
  }

  // metric query do not invoke interpolation, it will be done at the second-stage merge
  if (!isPointInterpoQuery(pQuery)) {
    pQuery->interpoType = TSDB_INTERPO_NONE;
  }

  TSKEY revisedStime = taosGetIntervalStartTimestamp(pSupporter->rawSKey, pQuery->nAggTimeInterval,
                                                     pQuery->intervalTimeUnit, pQuery->precision);
  taosInitInterpoInfo(&pSupporter->runtimeEnv.interpoInfo, pQuery->order.order, revisedStime, 0, 0);

  return TSDB_CODE_SUCCESS;
}