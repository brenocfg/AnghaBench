#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_17__ {int vnodeIndex; } ;
struct TYPE_16__ {TYPE_7__ cur; int /*<<< orphan*/  tag; } ;
struct TYPE_14__ {int /*<<< orphan*/ * pTSBuf; TYPE_2__* pCtx; } ;
struct TYPE_15__ {TYPE_3__ runtimeEnv; int /*<<< orphan*/ * pMeterSidExtInfo; int /*<<< orphan*/  pSidSet; } ;
struct TYPE_12__ {int /*<<< orphan*/  i64Key; } ;
struct TYPE_13__ {TYPE_1__ tag; } ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  int /*<<< orphan*/  SOutputRes ;
typedef  TYPE_4__ SMeterQuerySupportObj ;
typedef  TYPE_5__ SMeterQueryInfo ;

/* Variables and functions */
 int /*<<< orphan*/  initCtxOutputBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  setGroupOutputBuffer (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsBufGetElemStartPos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsBufSetCursor (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  vnodeSetTagValueInParam (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

void setExecutionContext(SMeterQuerySupportObj *pSupporter, SOutputRes *outputRes, int32_t meterIdx, int32_t groupIdx,
                         SMeterQueryInfo *pMeterQueryInfo) {
  SQueryRuntimeEnv *pRuntimeEnv = &pSupporter->runtimeEnv;

  setGroupOutputBuffer(pRuntimeEnv, &outputRes[groupIdx]);
  initCtxOutputBuf(pRuntimeEnv);

  vnodeSetTagValueInParam(pSupporter->pSidSet, pRuntimeEnv, pSupporter->pMeterSidExtInfo[meterIdx]);

  // set the right cursor position for ts buffer
  if (pSupporter->runtimeEnv.pTSBuf != NULL) {
    if (pMeterQueryInfo->cur.vnodeIndex == -1) {
      pMeterQueryInfo->tag = pRuntimeEnv->pCtx[0].tag.i64Key;

      tsBufGetElemStartPos(pSupporter->runtimeEnv.pTSBuf, 0, pMeterQueryInfo->tag);
    } else {
      tsBufSetCursor(pSupporter->runtimeEnv.pTSBuf, &pMeterQueryInfo->cur);
    }
  }
}