#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_12__ {size_t numOfSubSet; } ;
struct TYPE_11__ {size_t numOfMeters; struct TYPE_11__* pResult; struct TYPE_11__* pMeterDataInfo; int /*<<< orphan*/  pBlock; int /*<<< orphan*/  pMeterQInfo; TYPE_6__* pSidSet; int /*<<< orphan*/  extBufFile; int /*<<< orphan*/  meterOutputFd; int /*<<< orphan*/  bufSize; int /*<<< orphan*/ * meterOutputMMapBuf; int /*<<< orphan*/ * pMeterObj; struct TYPE_11__* pMeterSidExtInfo; int /*<<< orphan*/  runtimeEnv; } ;
struct TYPE_9__ {int /*<<< orphan*/  numOfOutputCols; int /*<<< orphan*/  pGroupbyExpr; } ;
struct TYPE_10__ {TYPE_3__* pMeterQuerySupporter; TYPE_1__ query; } ;
typedef  TYPE_1__ SQuery ;
typedef  TYPE_2__ SQInfo ;
typedef  TYPE_3__ SMeterQuerySupportObj ;

/* Variables and functions */
 scalar_t__ VALIDFD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroyGroupResultBuf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroyMeterQueryInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ isGroupbyNormalCol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tSidSetDestroy (TYPE_6__**) ; 
 int /*<<< orphan*/  taosCleanUpIntHash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teardownQueryRuntimeEnv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (TYPE_3__*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void vnodeQueryFreeQInfoEx(SQInfo *pQInfo) {
  if (pQInfo == NULL || pQInfo->pMeterQuerySupporter == NULL) {
    return;
  }

  SQuery *               pQuery = &pQInfo->query;
  SMeterQuerySupportObj *pSupporter = pQInfo->pMeterQuerySupporter;

  teardownQueryRuntimeEnv(&pSupporter->runtimeEnv);
  tfree(pSupporter->pMeterSidExtInfo);

  if (pSupporter->pMeterObj != NULL) {
    taosCleanUpIntHash(pSupporter->pMeterObj);
    pSupporter->pMeterObj = NULL;
  }

  if (pSupporter->pSidSet != NULL || isGroupbyNormalCol(pQInfo->query.pGroupbyExpr)) {
    int32_t size = 0;
    if (isGroupbyNormalCol(pQInfo->query.pGroupbyExpr)) {
      size = 10000;
    } else if (pSupporter->pSidSet != NULL) {
      size = pSupporter->pSidSet->numOfSubSet;
    }

    for (int32_t i = 0; i < size; ++i) {
      destroyGroupResultBuf(&pSupporter->pResult[i], pQInfo->query.numOfOutputCols);
    }
  }

  if (VALIDFD(pSupporter->meterOutputFd)) {
    assert(pSupporter->meterOutputMMapBuf != NULL);
    dTrace("QInfo:%p disk-based output buffer during query:%lld bytes", pQInfo, pSupporter->bufSize);
    munmap(pSupporter->meterOutputMMapBuf, pSupporter->bufSize);
    tclose(pSupporter->meterOutputFd);

    unlink(pSupporter->extBufFile);
  }

  tSidSetDestroy(&pSupporter->pSidSet);

  if (pSupporter->pMeterDataInfo != NULL) {
    for (int32_t j = 0; j < pSupporter->numOfMeters; ++j) {
      destroyMeterQueryInfo(pSupporter->pMeterDataInfo[j].pMeterQInfo, pQuery->numOfOutputCols);
      free(pSupporter->pMeterDataInfo[j].pBlock);
    }
  }

  tfree(pSupporter->pMeterDataInfo);

  tfree(pSupporter->pResult);
  tfree(pQInfo->pMeterQuerySupporter);
}