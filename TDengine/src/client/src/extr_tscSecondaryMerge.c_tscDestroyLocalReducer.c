#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_12__ {TYPE_6__* pTags; TYPE_6__* prevValues; } ;
struct TYPE_18__ {size_t numOfBuffer; scalar_t__ numOfCompleted; TYPE_6__** pLocalDataSrc; int /*<<< orphan*/  numOfVnode; int /*<<< orphan*/  resColModel; int /*<<< orphan*/  pDesc; int /*<<< orphan*/  pExtMemBuffer; TYPE_6__* discardData; TYPE_6__* pFinalRes; TYPE_6__* pBufForInterpo; TYPE_6__* pLoserTree; TYPE_6__* pResInfo; TYPE_6__* pResultBuf; TYPE_6__* pTempBuffer; TYPE_6__* prevRowOfInput; TYPE_6__* pCtx; TYPE_1__ interpolationInfo; int /*<<< orphan*/  status; } ;
struct TYPE_17__ {struct TYPE_17__* param; struct TYPE_17__* interResultBuf; int /*<<< orphan*/  tag; } ;
struct TYPE_13__ {size_t numOfOutputCols; } ;
struct TYPE_16__ {TYPE_2__ fieldsInfo; } ;
struct TYPE_14__ {int /*<<< orphan*/ * pLocalReducer; } ;
struct TYPE_15__ {TYPE_5__ cmd; TYPE_3__ res; } ;
typedef  TYPE_3__ SSqlRes ;
typedef  TYPE_4__ SSqlObj ;
typedef  TYPE_5__ SSqlCmd ;
typedef  TYPE_6__ SQLFunctionCtx ;
typedef  TYPE_7__ SLocalReducer ;

/* Variables and functions */
 size_t TSC_LOCALREDUCE_IN_PROGRESS ; 
 int /*<<< orphan*/  TSC_LOCALREDUCE_READY ; 
 int /*<<< orphan*/  TSC_LOCALREDUCE_TOBE_FREED ; 
 scalar_t__ atomic_exchange_ptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 size_t atomic_val_compare_exchange_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_7__*) ; 
 int /*<<< orphan*/  tVariantDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosMsleep (int) ; 
 int /*<<< orphan*/  tfree (TYPE_6__*) ; 
 int /*<<< orphan*/  tscLocalReducerEnvDestroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_4__*,...) ; 

void tscDestroyLocalReducer(SSqlObj *pSql) {
  if (pSql == NULL) {
    return;
  }

  tscTrace("%p start to free local reducer", pSql);
  SSqlRes *pRes = &(pSql->res);
  if (pRes->pLocalReducer == NULL) {
    tscTrace("%p local reducer has been freed, abort", pSql);
    return;
  }

  SSqlCmd *pCmd = &pSql->cmd;

  // there is no more result, so we release all allocated resource
  SLocalReducer *pLocalReducer = (SLocalReducer*)atomic_exchange_ptr(&pRes->pLocalReducer, NULL);
  if (pLocalReducer != NULL) {
    int32_t status = 0;
    while ((status = atomic_val_compare_exchange_32(&pLocalReducer->status, TSC_LOCALREDUCE_READY,
                                                    TSC_LOCALREDUCE_TOBE_FREED)) == TSC_LOCALREDUCE_IN_PROGRESS) {
      taosMsleep(100);
      tscTrace("%p waiting for delete procedure, status: %d", pSql, status);
    }

    tfree(pLocalReducer->interpolationInfo.prevValues);
    tfree(pLocalReducer->interpolationInfo.pTags);

    if (pLocalReducer->pCtx != NULL) {
      for(int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
        SQLFunctionCtx *pCtx = &pLocalReducer->pCtx[i];
        tVariantDestroy(&pCtx->tag);
      }

      tfree(pLocalReducer->pCtx);
    }


    tfree(pLocalReducer->prevRowOfInput);

    tfree(pLocalReducer->pTempBuffer);
    tfree(pLocalReducer->pResultBuf);

    if (pLocalReducer->pResInfo != NULL) {
      for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
        tfree(pLocalReducer->pResInfo[i].interResultBuf);
      }

      tfree(pLocalReducer->pResInfo);
    }

    if (pLocalReducer->pLoserTree) {
      tfree(pLocalReducer->pLoserTree->param);
      tfree(pLocalReducer->pLoserTree);
    }

    tfree(pLocalReducer->pBufForInterpo);

    tfree(pLocalReducer->pFinalRes);
    tfree(pLocalReducer->discardData);

    tscLocalReducerEnvDestroy(pLocalReducer->pExtMemBuffer, pLocalReducer->pDesc, pLocalReducer->resColModel,
                              pLocalReducer->numOfVnode);
    for (int32_t i = 0; i < pLocalReducer->numOfBuffer; ++i) {
      tfree(pLocalReducer->pLocalDataSrc[i]);
    }

    pLocalReducer->numOfBuffer = 0;
    pLocalReducer->numOfCompleted = 0;
    free(pLocalReducer);
  } else {
    tscTrace("%p already freed or another free function is invoked", pSql);
  }

  tscTrace("%p free local reducer finished", pSql);
}