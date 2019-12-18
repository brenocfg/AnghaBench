#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_26__ {int vnodeIndex; } ;
struct TYPE_25__ {TYPE_9__ cur; } ;
struct TYPE_24__ {scalar_t__ lastResRows; TYPE_9__ cur; int /*<<< orphan*/  tag; scalar_t__ reverseFillRes; } ;
struct TYPE_21__ {TYPE_8__* pTSBuf; TYPE_2__* pCtx; TYPE_4__* pQuery; } ;
struct TYPE_23__ {TYPE_3__ runtimeEnv; int /*<<< orphan*/ * pMeterSidExtInfo; int /*<<< orphan*/  pSidSet; } ;
struct TYPE_22__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_19__ {int /*<<< orphan*/  i64Key; } ;
struct TYPE_20__ {TYPE_1__ tag; } ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;
typedef  TYPE_5__ SMeterQuerySupportObj ;
typedef  TYPE_6__ SMeterQueryInfo ;

/* Variables and functions */
 scalar_t__ IS_MASTER_SCAN (TYPE_3__*) ; 
 int /*<<< orphan*/  initCtxOutputBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  setCtxOutputPointerForSupplementScan (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  setOutputBufferForIntervalQuery (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  tsBufGetElemStartPos (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsBufSetCursor (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  vnodeSetTagValueInParam (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

void setIntervalQueryExecutionContext(SMeterQuerySupportObj *pSupporter, int32_t meterIdx,
                                      SMeterQueryInfo *pMeterQueryInfo) {
  SQueryRuntimeEnv *pRuntimeEnv = &pSupporter->runtimeEnv;
  SQuery *          pQuery = pRuntimeEnv->pQuery;

  if (IS_MASTER_SCAN(pRuntimeEnv)) {
    setOutputBufferForIntervalQuery(pSupporter, pMeterQueryInfo);

    if (pMeterQueryInfo->lastResRows == 0) {
      initCtxOutputBuf(pRuntimeEnv);
    }

    // reset the number of iterated elements, once this function is called. since the pCtx for different
    for (int32_t j = 0; j < pQuery->numOfOutputCols; ++j) {
      //      pRuntimeEnv->pCtx[j].numOfIteratedElems = 0;
    }

  } else {
    if (pMeterQueryInfo->reverseFillRes) {
      setCtxOutputPointerForSupplementScan(pSupporter, pMeterQueryInfo);
    } else {
      /*
       * set output buffer for reverse scan data blocks
       * find the correct output position of existed results during
       *
       * If the master scan does not produce any results, new spaces needed to be allocated during supplement scan
       */
      setOutputBufferForIntervalQuery(pSupporter, pMeterQueryInfo);
    }
  }

  vnodeSetTagValueInParam(pSupporter->pSidSet, pRuntimeEnv, pSupporter->pMeterSidExtInfo[meterIdx]);

  // both the master and supplement scan needs to set the correct ts comp start position
  if (pSupporter->runtimeEnv.pTSBuf != NULL) {
    if (pMeterQueryInfo->cur.vnodeIndex == -1) {
      pMeterQueryInfo->tag = pRuntimeEnv->pCtx[0].tag.i64Key;

      tsBufGetElemStartPos(pSupporter->runtimeEnv.pTSBuf, 0, pMeterQueryInfo->tag);

      // keep the cursor info of current meter
      pMeterQueryInfo->cur = pSupporter->runtimeEnv.pTSBuf->cur;
    } else {
      tsBufSetCursor(pSupporter->runtimeEnv.pTSBuf, &pMeterQueryInfo->cur);
    }
  }
}