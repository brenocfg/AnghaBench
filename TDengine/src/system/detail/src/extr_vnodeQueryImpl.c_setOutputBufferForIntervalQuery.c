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

/* Type definitions */
struct TYPE_18__ {scalar_t__ numOfElems; } ;
typedef  TYPE_3__ tFilePage ;
typedef  size_t int32_t ;
struct TYPE_21__ {int numOfPages; size_t* pageList; int /*<<< orphan*/ * resultInfo; } ;
struct TYPE_19__ {scalar_t__ numOfRowsPerPage; TYPE_2__* pCtx; TYPE_1__* pQuery; } ;
struct TYPE_20__ {TYPE_4__ runtimeEnv; } ;
struct TYPE_17__ {int /*<<< orphan*/ * resultInfo; int /*<<< orphan*/  aOutputBuf; } ;
struct TYPE_16__ {size_t numOfOutputCols; } ;
typedef  TYPE_4__ SQueryRuntimeEnv ;
typedef  TYPE_5__ SMeterQuerySupportObj ;
typedef  TYPE_6__ SMeterQueryInfo ;

/* Variables and functions */
 TYPE_3__* addDataPageForMeterQueryInfo (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* getFilePage (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  getOutputResPos (TYPE_4__*,TYPE_3__*,scalar_t__,size_t) ; 

void setOutputBufferForIntervalQuery(SMeterQuerySupportObj *pSupporter, SMeterQueryInfo *pMeterQueryInfo) {
  SQueryRuntimeEnv *pRuntimeEnv = &pSupporter->runtimeEnv;
  tFilePage *       pData = NULL;

  // in the first scan, new space needed for results
  if (pMeterQueryInfo->numOfPages == 0) {
    pData = addDataPageForMeterQueryInfo(pMeterQueryInfo, pSupporter);
  } else {
    int32_t lastPageId = pMeterQueryInfo->pageList[pMeterQueryInfo->numOfPages - 1];
    pData = getFilePage(pSupporter, lastPageId);

    if (pData->numOfElems >= pRuntimeEnv->numOfRowsPerPage) {
      pData = addDataPageForMeterQueryInfo(pMeterQueryInfo, pSupporter);
      assert(pData->numOfElems == 0);  // number of elements must be 0 for new allocated buffer
    }
  }

  for (int32_t i = 0; i < pRuntimeEnv->pQuery->numOfOutputCols; ++i) {
    pRuntimeEnv->pCtx[i].aOutputBuf = getOutputResPos(pRuntimeEnv, pData, pData->numOfElems, i);
    pRuntimeEnv->pCtx[i].resultInfo = &pMeterQueryInfo->resultInfo[i];
  }
}