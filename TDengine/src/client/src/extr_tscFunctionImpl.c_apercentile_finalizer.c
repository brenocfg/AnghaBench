#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ numOfElems; } ;
struct TYPE_13__ {TYPE_5__* pHisto; } ;
struct TYPE_12__ {scalar_t__ currentStage; int /*<<< orphan*/  outputBytes; int /*<<< orphan*/  outputType; int /*<<< orphan*/  aOutputBuf; TYPE_1__* param; } ;
struct TYPE_11__ {scalar_t__ hasResult; TYPE_4__* interResultBuf; } ;
struct TYPE_10__ {scalar_t__ nType; double i64Key; double dKey; } ;
typedef  TYPE_2__ SResultInfo ;
typedef  TYPE_3__ SQLFunctionCtx ;
typedef  TYPE_4__ SAPercentileInfo ;

/* Variables and functions */
 scalar_t__ DATA_SET_FLAG ; 
 TYPE_2__* GET_RES_INFO (TYPE_3__*) ; 
 scalar_t__ SECONDARY_STAGE_MERGE ; 
 scalar_t__ TSDB_DATA_TYPE_INT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (double*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,double*,int) ; 
 int /*<<< orphan*/  resetResultInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  setNull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double* tHistogramUniform (TYPE_5__*,double*,int) ; 

__attribute__((used)) static void apercentile_finalizer(SQLFunctionCtx *pCtx) {
  double v = (pCtx->param[0].nType == TSDB_DATA_TYPE_INT) ? pCtx->param[0].i64Key : pCtx->param[0].dKey;

  SResultInfo *     pResInfo = GET_RES_INFO(pCtx);
  SAPercentileInfo *pOutput = pResInfo->interResultBuf;

  if (pCtx->currentStage == SECONDARY_STAGE_MERGE) {
    if (pResInfo->hasResult == DATA_SET_FLAG) {  // check for null
      assert(pOutput->pHisto->numOfElems > 0);

      double  ratio[] = {v};
      double *res = tHistogramUniform(pOutput->pHisto, ratio, 1);

      memcpy(pCtx->aOutputBuf, res, sizeof(double));
      free(res);
    } else {
      setNull(pCtx->aOutputBuf, pCtx->outputType, pCtx->outputBytes);
      return;
    }
  } else {
    if (pOutput->pHisto->numOfElems > 0) {
      double ratio[] = {v};

      double *res = tHistogramUniform(pOutput->pHisto, ratio, 1);
      memcpy(pCtx->aOutputBuf, res, sizeof(double));
      free(res);
    } else {  // no need to free
      setNull(pCtx->aOutputBuf, pCtx->outputType, pCtx->outputBytes);
      return;
    }
  }

  resetResultInfo(pResInfo);
}