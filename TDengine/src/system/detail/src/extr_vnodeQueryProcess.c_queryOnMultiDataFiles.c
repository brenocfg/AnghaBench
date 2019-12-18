#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_72__   TYPE_9__ ;
typedef  struct TYPE_71__   TYPE_8__ ;
typedef  struct TYPE_70__   TYPE_7__ ;
typedef  struct TYPE_69__   TYPE_6__ ;
typedef  struct TYPE_68__   TYPE_5__ ;
typedef  struct TYPE_67__   TYPE_4__ ;
typedef  struct TYPE_66__   TYPE_3__ ;
typedef  struct TYPE_65__   TYPE_2__ ;
typedef  struct TYPE_64__   TYPE_21__ ;
typedef  struct TYPE_63__   TYPE_1__ ;
typedef  struct TYPE_62__   TYPE_16__ ;
typedef  struct TYPE_61__   TYPE_15__ ;
typedef  struct TYPE_60__   TYPE_14__ ;
typedef  struct TYPE_59__   TYPE_13__ ;
typedef  struct TYPE_58__   TYPE_12__ ;
typedef  struct TYPE_57__   TYPE_11__ ;
typedef  struct TYPE_56__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  size_t int64_t ;
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  __block_search_fn_t ;
struct TYPE_67__ {int /*<<< orphan*/  order; } ;
struct TYPE_72__ {size_t fileId; scalar_t__ nAggTimeInterval; scalar_t__ lastKey; scalar_t__ ekey; size_t pos; int /*<<< orphan*/  skey; TYPE_4__ order; } ;
struct TYPE_71__ {size_t fileTimeUs; int /*<<< orphan*/  numOfTables; int /*<<< orphan*/  readDiskBlocks; int /*<<< orphan*/  skippedFileBlocks; int /*<<< orphan*/  numOfFiles; } ;
struct TYPE_70__ {char* pHeaderFileData; int /*<<< orphan*/  dataFilePath; } ;
struct TYPE_68__ {size_t fileId; } ;
struct TYPE_69__ {int /*<<< orphan*/  numOfFiles; scalar_t__ colDataBuffer; int /*<<< orphan*/  blockStatus; TYPE_1__* primaryColBuffer; TYPE_13__* pMeterObj; TYPE_7__* pHeaderFiles; TYPE_5__ startPos; TYPE_8__ summary; } ;
struct TYPE_66__ {int /*<<< orphan*/  sid; } ;
struct TYPE_65__ {int /*<<< orphan*/  fields; TYPE_16__* compBlock; } ;
struct TYPE_64__ {int /*<<< orphan*/  numOfSids; } ;
struct TYPE_63__ {scalar_t__ data; } ;
struct TYPE_62__ {size_t numOfPoints; scalar_t__ keyFirst; scalar_t__ keyLast; } ;
struct TYPE_61__ {TYPE_2__ pBlock; int /*<<< orphan*/  blockIndex; TYPE_14__* pMeterDataInfo; } ;
struct TYPE_60__ {int /*<<< orphan*/  meterOrderIdx; int /*<<< orphan*/  groupIdx; TYPE_13__* pMeterObj; TYPE_12__* pMeterQInfo; } ;
struct TYPE_59__ {size_t searchAlgorithm; size_t vnode; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; } ;
struct TYPE_58__ {int /*<<< orphan*/  queryRangeSet; } ;
struct TYPE_57__ {TYPE_21__* pSidSet; int /*<<< orphan*/  pResult; TYPE_3__** pMeterSidExtInfo; int /*<<< orphan*/  pMeterObj; TYPE_6__ runtimeEnv; } ;
struct TYPE_56__ {int killed; TYPE_13__* pObj; void* code; TYPE_11__* pMeterQuerySupporter; TYPE_9__ query; } ;
typedef  int /*<<< orphan*/  TSKEY ;
typedef  TYPE_6__ SQueryRuntimeEnv ;
typedef  TYPE_7__ SQueryFileInfo ;
typedef  TYPE_8__ SQueryCostSummary ;
typedef  TYPE_9__ SQuery ;
typedef  TYPE_10__ SQInfo ;
typedef  TYPE_11__ SMeterQuerySupportObj ;
typedef  TYPE_12__ SMeterQueryInfo ;
typedef  TYPE_13__ SMeterObj ;
typedef  TYPE_14__ SMeterDataInfo ;
typedef  TYPE_15__ SMeterDataBlockInfoEx ;
typedef  TYPE_16__ SCompBlock ;
typedef  int /*<<< orphan*/  SBlockInfo ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_FILE_BLOCK ; 
 size_t DISK_DATA_LOADED ; 
 size_t GET_FORWARD_DIRECTION_FACTOR (int /*<<< orphan*/ ) ; 
 int INT32_MAX ; 
 scalar_t__ IS_DATA_BLOCK_LOADED (int /*<<< orphan*/ ) ; 
 size_t LoadDatablockOnDemand (TYPE_16__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_9__*) ; 
 int /*<<< orphan*/  QUERY_NOT_COMPLETED ; 
 void* TSDB_CODE_SERV_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t createDataBlocksInfoEx (TYPE_14__**,size_t,TYPE_15__**,int,size_t*,size_t) ; 
 int /*<<< orphan*/  dError (char*,TYPE_10__*) ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_10__*,int,...) ; 
 int /*<<< orphan*/  doCheckWithPrevQueryRange (TYPE_10__*,int /*<<< orphan*/ ,TYPE_14__*) ; 
 int /*<<< orphan*/  freeMeterBlockInfoEx (TYPE_15__*,size_t) ; 
 int /*<<< orphan*/  getBlockBasicInfo (TYPE_16__*,int /*<<< orphan*/ ) ; 
 int getDataBlocksForMeters (TYPE_11__*,TYPE_9__*,char*,size_t,TYPE_7__*,TYPE_14__**) ; 
 TYPE_13__* getMeterObj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isQueryKilled (TYPE_9__*) ; 
 scalar_t__ needPrimaryTimestampCol (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int onDemandLoadDatablock (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qTrace (char*,TYPE_10__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  queryOnBlock (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restoreIntervalQueryRange (TYPE_6__*,TYPE_12__*) ; 
 int /*<<< orphan*/  setExecutionContext (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_12__*) ; 
 int /*<<< orphan*/  setIntervalQueryExecutionContext (TYPE_11__*,int /*<<< orphan*/ ,TYPE_12__*) ; 
 int /*<<< orphan*/  setQueryStatus (TYPE_9__*,int /*<<< orphan*/ ) ; 
 size_t taosGetTimestampMs () ; 
 size_t taosGetTimestampUs () ; 
 int /*<<< orphan*/  tfree (TYPE_14__**) ; 
 TYPE_14__** vnodeFilterQualifiedMeters (TYPE_10__*,size_t,TYPE_7__*,TYPE_21__*,TYPE_14__*,size_t*) ; 
 size_t vnodeGetVnodeHeaderFileIdx (size_t*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vnodeSearchKeyFunc ; 

__attribute__((used)) static SMeterDataInfo *queryOnMultiDataFiles(SQInfo *pQInfo, SMeterDataInfo *pMeterDataInfo) {
  SQuery *               pQuery = &pQInfo->query;
  SMeterQuerySupportObj *pSupporter = pQInfo->pMeterQuerySupporter;
  SQueryRuntimeEnv *     pRuntimeEnv = &pSupporter->runtimeEnv;
  SMeterDataBlockInfoEx *pDataBlockInfoEx = NULL;
  int32_t                nAllocBlocksInfoSize = 0;

  SMeterObj *         pTempMeter = getMeterObj(pSupporter->pMeterObj, pSupporter->pMeterSidExtInfo[0]->sid);
  __block_search_fn_t searchFn = vnodeSearchKeyFunc[pTempMeter->searchAlgorithm];

  int32_t vnodeId = pTempMeter->vnode;
  dTrace("QInfo:%p start to check data blocks in %d files", pQInfo, pRuntimeEnv->numOfFiles);

  int32_t            fid = QUERY_IS_ASC_QUERY(pQuery) ? -1 : INT32_MAX;
  int32_t            step = GET_FORWARD_DIRECTION_FACTOR(pQuery->order.order);
  SQueryCostSummary *pSummary = &pRuntimeEnv->summary;

  int64_t totalBlocks = 0;
  int64_t st = taosGetTimestampUs();

  while (1) {
    if (isQueryKilled(pQuery)) {
      break;
    }

    int32_t fileIdx = vnodeGetVnodeHeaderFileIdx(&fid, pRuntimeEnv, pQuery->order.order);
    if (fileIdx < 0) {  // no valid file, abort current search
      break;
    }

    pRuntimeEnv->startPos.fileId = fid;
    pQuery->fileId = fid;
    pSummary->numOfFiles++;

    SQueryFileInfo *pQueryFileInfo = &pRuntimeEnv->pHeaderFiles[fileIdx];
    char *          pHeaderData = pQueryFileInfo->pHeaderFileData;

    int32_t          numOfQualifiedMeters = 0;
    SMeterDataInfo **pReqMeterDataInfo = vnodeFilterQualifiedMeters(
        pQInfo, vnodeId, pQueryFileInfo, pSupporter->pSidSet, pMeterDataInfo, &numOfQualifiedMeters);
    dTrace("QInfo:%p file:%s, %d meters qualified", pQInfo, pQueryFileInfo->dataFilePath, numOfQualifiedMeters);

    if (pReqMeterDataInfo == NULL) {
      dError("QInfo:%p failed to allocate memory to perform query processing, abort", pQInfo);

      pQInfo->code = TSDB_CODE_SERV_OUT_OF_MEMORY;
      pQInfo->killed = 1;
      return NULL;
    }

    // none of meters in query set have pHeaderData in this file, try next file
    if (numOfQualifiedMeters == 0) {
      fid += step;
      tfree(pReqMeterDataInfo);
      continue;
    }

    uint32_t numOfBlocks = getDataBlocksForMeters(pSupporter, pQuery, pHeaderData, numOfQualifiedMeters, pQueryFileInfo,
                                                  pReqMeterDataInfo);

    dTrace("QInfo:%p file:%s, %d meters contains %d blocks to be checked", pQInfo, pQueryFileInfo->dataFilePath,
           numOfQualifiedMeters, numOfBlocks);
    if (numOfBlocks == 0) {
      fid += step;
      tfree(pReqMeterDataInfo);
      continue;
    }

    int32_t n = createDataBlocksInfoEx(pReqMeterDataInfo, numOfQualifiedMeters, &pDataBlockInfoEx, numOfBlocks,
                                       &nAllocBlocksInfoSize, (int64_t)pQInfo);
    if (n < 0) {  // failed to create data blocks
      dError("QInfo:%p failed to allocate memory to perform query processing, abort", pQInfo);
      tfree(pReqMeterDataInfo);

      pQInfo->code = TSDB_CODE_SERV_OUT_OF_MEMORY;
      pQInfo->killed = 1;
      return NULL;
    }

    dTrace("QInfo:%p start to load %d blocks and check", pQInfo, numOfBlocks);
    int64_t TRACE_OUTPUT_BLOCK_CNT = 10000;
    int64_t stimeUnit = 0;
    int64_t etimeUnit = 0;

    totalBlocks += numOfBlocks;

    // sequentially scan the pHeaderData file
    int32_t j = QUERY_IS_ASC_QUERY(pQuery) ? 0 : numOfBlocks - 1;

    for (; j < numOfBlocks && j >= 0; j += step) {
      if (isQueryKilled(pQuery)) {
        break;
      }

      /* output elapsed time for log every TRACE_OUTPUT_BLOCK_CNT blocks */
      if (j == 0) {
        stimeUnit = taosGetTimestampMs();
      } else if ((j % TRACE_OUTPUT_BLOCK_CNT) == 0) {
        etimeUnit = taosGetTimestampMs();
        dTrace("QInfo:%p load and check %ld blocks, and continue. elapsed:%ldms", pQInfo, TRACE_OUTPUT_BLOCK_CNT,
               etimeUnit - stimeUnit);
        stimeUnit = taosGetTimestampMs();
      }

      SMeterDataBlockInfoEx *pInfoEx = &pDataBlockInfoEx[j];
      SMeterDataInfo *       pOneMeterDataInfo = pInfoEx->pMeterDataInfo;
      SMeterQueryInfo *      pMeterQueryInfo = pOneMeterDataInfo->pMeterQInfo;
      SMeterObj *            pMeterObj = pOneMeterDataInfo->pMeterObj;

      pQInfo->pObj = pMeterObj;
      pRuntimeEnv->pMeterObj = pMeterObj;

      restoreIntervalQueryRange(pRuntimeEnv, pMeterQueryInfo);

      if (pQuery->nAggTimeInterval == 0) {  // normal query
        if ((pQuery->lastKey > pQuery->ekey && QUERY_IS_ASC_QUERY(pQuery)) ||
            (pQuery->lastKey < pQuery->ekey && !QUERY_IS_ASC_QUERY(pQuery))) {
          qTrace(
              "QInfo:%p vid:%d sid:%d id:%s, query completed, no need to scan this data block. qrange:%lld-%lld, "
              "lastKey:%lld",
              pQInfo, pMeterObj->vnode, pMeterObj->sid, pMeterObj->meterId, pQuery->skey, pQuery->ekey,
              pQuery->lastKey);

          continue;
        }

        setExecutionContext(pSupporter, pSupporter->pResult, pOneMeterDataInfo->meterOrderIdx,
                            pOneMeterDataInfo->groupIdx, pMeterQueryInfo);
      } else {  // interval query
        setIntervalQueryExecutionContext(pSupporter, pOneMeterDataInfo->meterOrderIdx, pMeterQueryInfo);
      }

      SCompBlock *pBlock = pInfoEx->pBlock.compBlock;
      bool        ondemandLoad = onDemandLoadDatablock(pQuery, pMeterQueryInfo->queryRangeSet);
      int32_t     ret = LoadDatablockOnDemand(pBlock, &pInfoEx->pBlock.fields, &pRuntimeEnv->blockStatus, pRuntimeEnv,
                                          fileIdx, pInfoEx->blockIndex, searchFn, ondemandLoad);
      if (ret != DISK_DATA_LOADED) {
        pSummary->skippedFileBlocks++;
        continue;
      }

      SBlockInfo binfo = getBlockBasicInfo(pBlock, BLK_FILE_BLOCK);

      assert(pQuery->pos >= 0 && pQuery->pos < pBlock->numOfPoints);
      TSKEY *primaryKeys = (TSKEY *)pRuntimeEnv->primaryColBuffer->data;

      if (IS_DATA_BLOCK_LOADED(pRuntimeEnv->blockStatus) && needPrimaryTimestampCol(pQuery, &binfo)) {
        TSKEY nextKey = primaryKeys[pQuery->pos];
        if (!doCheckWithPrevQueryRange(pQInfo, nextKey, pOneMeterDataInfo)) {
          continue;
        }
      } else {
        // if data block is not loaded, it must be the intermediate blocks
        assert((pBlock->keyFirst >= pQuery->lastKey && pBlock->keyLast <= pQuery->ekey && QUERY_IS_ASC_QUERY(pQuery)) ||
               (pBlock->keyFirst >= pQuery->ekey && pBlock->keyLast <= pQuery->lastKey && !QUERY_IS_ASC_QUERY(pQuery)));
      }

      queryOnBlock(pSupporter, primaryKeys, pRuntimeEnv->blockStatus, (char *)pRuntimeEnv->colDataBuffer, &binfo,
                   pOneMeterDataInfo, pInfoEx->pBlock.fields, searchFn);
    }

    tfree(pReqMeterDataInfo);

    // try next file
    fid += step;
  }

  int64_t time = taosGetTimestampUs() - st;
  dTrace("QInfo:%p complete check %d files, %d blocks, elapsed time:%.3fms", pQInfo, pRuntimeEnv->numOfFiles,
         totalBlocks, time / 1000.0);

  pSummary->fileTimeUs += time;
  pSummary->readDiskBlocks += totalBlocks;
  pSummary->numOfTables = pSupporter->pSidSet->numOfSids;

  setQueryStatus(pQuery, QUERY_NOT_COMPLETED);
  freeMeterBlockInfoEx(pDataBlockInfoEx, nAllocBlocksInfoSize);

  return pMeterDataInfo;
}