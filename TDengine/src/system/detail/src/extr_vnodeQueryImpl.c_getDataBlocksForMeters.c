#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int64_t ;
typedef  size_t int32_t ;
struct TYPE_28__ {int numOfBlocks; scalar_t__ uid; } ;
struct TYPE_27__ {int /*<<< orphan*/  numOfBlocks; int /*<<< orphan*/  start; TYPE_6__* pMeterObj; int /*<<< orphan*/  offsetInHeaderFile; } ;
struct TYPE_26__ {scalar_t__ uid; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; int /*<<< orphan*/  vnode; } ;
struct TYPE_23__ {int /*<<< orphan*/  loadCompInfoUs; int /*<<< orphan*/  totalCompInfoSize; int /*<<< orphan*/  readCompInfo; } ;
struct TYPE_21__ {TYPE_3__ summary; } ;
struct TYPE_25__ {int /*<<< orphan*/  rawEKey; TYPE_1__ runtimeEnv; } ;
struct TYPE_24__ {int killed; } ;
struct TYPE_22__ {int /*<<< orphan*/  headerFilePath; } ;
typedef  int /*<<< orphan*/  TSKEY ;
typedef  int /*<<< orphan*/  TSCKSUM ;
typedef  TYPE_2__ SQueryFileInfo ;
typedef  TYPE_3__ SQueryCostSummary ;
typedef  int /*<<< orphan*/  SQuery ;
typedef  TYPE_4__ SQInfo ;
typedef  TYPE_5__ SMeterQuerySupportObj ;
typedef  TYPE_6__ SMeterObj ;
typedef  TYPE_7__ SMeterDataInfo ;
typedef  TYPE_8__ SCompInfo ;
typedef  int /*<<< orphan*/  SCompBlock ;

/* Variables and functions */
 scalar_t__ GET_QINFO_ADDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clearMeterDataBlockInfo (TYPE_7__*) ; 
 int /*<<< orphan*/  getValidDataBlocksRangeIndex (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  qTrace (char*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setCurrentQueryRange (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setValidDataBlocks (TYPE_7__*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ taosGetTimestampUs () ; 
 size_t validateCompBlockInfoSegment (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 size_t validateCompBlockSegment (TYPE_4__*,int /*<<< orphan*/ ,TYPE_8__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t getDataBlocksForMeters(SMeterQuerySupportObj *pSupporter, SQuery *pQuery, char *pHeaderData,
                                int32_t numOfMeters, SQueryFileInfo *pQueryFileInfo, SMeterDataInfo **pMeterDataInfo) {
  uint32_t           numOfBlocks = 0;
  SQInfo *           pQInfo = (SQInfo *)GET_QINFO_ADDR(pQuery);
  SQueryCostSummary *pSummary = &pSupporter->runtimeEnv.summary;

  TSKEY minval, maxval;

  // sequentially scan this header file to extract the compHeader info
  for (int32_t j = 0; j < numOfMeters; ++j) {
    SMeterObj *pMeterObj = pMeterDataInfo[j]->pMeterObj;

    SCompInfo *compInfo = (SCompInfo *)(pHeaderData + pMeterDataInfo[j]->offsetInHeaderFile);
    int32_t    ret = validateCompBlockInfoSegment(pQInfo, pQueryFileInfo->headerFilePath, pMeterObj->vnode, compInfo,
                                               pMeterDataInfo[j]->offsetInHeaderFile);
    if (ret != 0) {
      clearMeterDataBlockInfo(pMeterDataInfo[j]);
      continue;
    }

    if (compInfo->numOfBlocks <= 0 || compInfo->uid != pMeterDataInfo[j]->pMeterObj->uid) {
      clearMeterDataBlockInfo(pMeterDataInfo[j]);
      continue;
    }

    int32_t     size = compInfo->numOfBlocks * sizeof(SCompBlock);
    SCompBlock *pCompBlock = (SCompBlock *)((char *)compInfo + sizeof(SCompInfo));

    int64_t st = taosGetTimestampUs();

    // check compblock integrity
    TSCKSUM checksum = *(TSCKSUM *)((char *)compInfo + sizeof(SCompInfo) + size);
    ret = validateCompBlockSegment(pQInfo, pQueryFileInfo->headerFilePath, compInfo, (char *)pCompBlock,
                                   pMeterObj->vnode, checksum);
    if (ret < 0) {
      clearMeterDataBlockInfo(pMeterDataInfo[j]);
      continue;
    }

    int64_t et = taosGetTimestampUs();

    pSummary->readCompInfo++;
    pSummary->totalCompInfoSize += (size + sizeof(SCompInfo) + sizeof(TSCKSUM));
    pSummary->loadCompInfoUs += (et - st);

    if (!setCurrentQueryRange(pMeterDataInfo[j], pQuery, pSupporter->rawEKey, &minval, &maxval)) {
      clearMeterDataBlockInfo(pMeterDataInfo[j]);
      continue;
    }

    int32_t end = 0;
    if (!getValidDataBlocksRangeIndex(pMeterDataInfo[j], pQuery, pCompBlock, compInfo->numOfBlocks, minval, maxval,
                                      &end)) {
      clearMeterDataBlockInfo(pMeterDataInfo[j]);
      continue;
    }

    if (!setValidDataBlocks(pMeterDataInfo[j], pCompBlock, end)) {
      clearMeterDataBlockInfo(pMeterDataInfo[j]);
      pQInfo->killed = 1;  // todo set query kill, abort current query since no
                           // memory available
      return 0;
    }

    qTrace("QInfo:%p vid:%d sid:%d id:%s, startIndex:%d, %d blocks qualified", pQInfo, pMeterObj->vnode, pMeterObj->sid,
           pMeterObj->meterId, pMeterDataInfo[j]->start, pMeterDataInfo[j]->numOfBlocks);

    numOfBlocks += pMeterDataInfo[j]->numOfBlocks;
  }

  return numOfBlocks;
}