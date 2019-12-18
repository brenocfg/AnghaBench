#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double loadCompInfoUs; double readField; double loadFieldUs; double loadBlocksUs; double fileTimeUs; double cacheTimeUs; int /*<<< orphan*/  numOfSeek; int /*<<< orphan*/  numOfTables; int /*<<< orphan*/  numOfFiles; int /*<<< orphan*/  tmpBufferInDisk; int /*<<< orphan*/  blocksInCache; int /*<<< orphan*/  totalGenData; int /*<<< orphan*/  skippedFileBlocks; int /*<<< orphan*/  totalBlockSize; int /*<<< orphan*/  readDiskBlocks; scalar_t__ totalFieldSize; int /*<<< orphan*/  totalCompInfoSize; int /*<<< orphan*/  readCompInfo; } ;
struct TYPE_5__ {TYPE_2__ summary; int /*<<< orphan*/ * pQuery; } ;
struct TYPE_7__ {int /*<<< orphan*/  bufSize; TYPE_1__ runtimeEnv; } ;
typedef  TYPE_1__ SQueryRuntimeEnv ;
typedef  TYPE_2__ SQueryCostSummary ;
typedef  int /*<<< orphan*/  SQuery ;
typedef  int /*<<< orphan*/  SQInfo ;
typedef  TYPE_3__ SMeterQuerySupportObj ;

/* Variables and functions */
 scalar_t__ GET_QINFO_ADDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dTrace (char*,int /*<<< orphan*/ *,double,...) ; 

void vnodePrintQueryStatistics(SMeterQuerySupportObj *pSupporter) {
  SQueryRuntimeEnv *pRuntimeEnv = &pSupporter->runtimeEnv;

  SQuery *pQuery = pRuntimeEnv->pQuery;
  SQInfo *pQInfo = (SQInfo *)GET_QINFO_ADDR(pQuery);

  SQueryCostSummary *pSummary = &pRuntimeEnv->summary;
  pSummary->tmpBufferInDisk = pSupporter->bufSize;

  dTrace("QInfo:%p statis: comp blocks:%d, size:%d Bytes, elapsed time:%.2f ms", pQInfo, pSummary->readCompInfo,
         pSummary->totalCompInfoSize, pSummary->loadCompInfoUs / 1000.0);

  dTrace("QInfo:%p statis: field info: %d, size:%d Bytes, avg size:%.2f Bytes, elapsed time:%.2f ms", pQInfo,
         pSummary->readField, pSummary->totalFieldSize, (double)pSummary->totalFieldSize / pSummary->readField,
         pSummary->loadFieldUs / 1000.0);

  dTrace(
      "QInfo:%p statis: file blocks:%d, size:%d Bytes, elapsed time:%.2f ms, skipped:%d, in-memory gen null:%d Bytes",
      pQInfo, pSummary->readDiskBlocks, pSummary->totalBlockSize, pSummary->loadBlocksUs / 1000.0,
      pSummary->skippedFileBlocks, pSummary->totalGenData);

  dTrace("QInfo:%p statis: cache blocks:%d", pQInfo, pSummary->blocksInCache, 0);
  dTrace("QInfo:%p statis: temp file:%d Bytes", pQInfo, pSummary->tmpBufferInDisk);

  dTrace("QInfo:%p statis: file:%d, table:%d", pQInfo, pSummary->numOfFiles, pSummary->numOfTables);
  dTrace("QInfo:%p statis: seek ops:%d", pQInfo, pSummary->numOfSeek);

  double total = pSummary->fileTimeUs + pSummary->cacheTimeUs;
  double io = pSummary->loadCompInfoUs + pSummary->loadBlocksUs + pSummary->loadFieldUs;
  //    assert(io <= pSummary->fileTimeUs);

  // todo add the intermediate result save cost!!
  double computing = total - io;

  dTrace(
      "QInfo:%p statis: total elapsed time:%.2f ms, file:%.2f ms(%.2f%), cache:%.2f ms(%.2f%). io:%.2f ms(%.2f%),"
      "comput:%.2fms(%.2f%)",
      pQInfo, total / 1000.0, pSummary->fileTimeUs / 1000.0, pSummary->fileTimeUs * 100 / total,
      pSummary->cacheTimeUs / 1000.0, pSummary->cacheTimeUs * 100 / total, io / 1000.0, io * 100 / total,
      computing / 1000.0, computing * 100 / total);
}