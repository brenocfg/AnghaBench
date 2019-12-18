#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ currentStage; scalar_t__ inputType; scalar_t__ aOutputBuf; int /*<<< orphan*/  outputBytes; int /*<<< orphan*/  outputType; TYPE_1__* param; } ;
struct TYPE_11__ {scalar_t__ hasResult; TYPE_2__* interResultBuf; } ;
struct TYPE_10__ {scalar_t__ hasResult; double max; double min; } ;
struct TYPE_9__ {double dKey; } ;
typedef  TYPE_2__ SSpreadInfo ;
typedef  TYPE_3__ SResultInfo ;
typedef  TYPE_4__ SQLFunctionCtx ;

/* Variables and functions */
 scalar_t__ DATA_SET_FLAG ; 
 TYPE_3__* GET_RES_INFO (TYPE_4__*) ; 
 scalar_t__ SECONDARY_STAGE_MERGE ; 
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 scalar_t__ TSDB_DATA_TYPE_DOUBLE ; 
 scalar_t__ TSDB_DATA_TYPE_TIMESTAMP ; 
 scalar_t__ TSDB_DATA_TYPE_TINYINT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  resetResultInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  setNull (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void spread_function_finalizer(SQLFunctionCtx *pCtx) {
  /*
   * here we do not check the input data types, because in case of metric query,
   * the type of intermediate data is binary
   */
  SResultInfo *pResInfo = GET_RES_INFO(pCtx);

  if (pCtx->currentStage == SECONDARY_STAGE_MERGE) {
    assert(pCtx->inputType == TSDB_DATA_TYPE_BINARY);

    if (pResInfo->hasResult != DATA_SET_FLAG) {
      setNull(pCtx->aOutputBuf, pCtx->outputType, pCtx->outputBytes);
      return;
    }

    *(double *)pCtx->aOutputBuf = pCtx->param[3].dKey - pCtx->param[0].dKey;
  } else {
    assert((pCtx->inputType >= TSDB_DATA_TYPE_TINYINT && pCtx->inputType <= TSDB_DATA_TYPE_DOUBLE) ||
           (pCtx->inputType == TSDB_DATA_TYPE_TIMESTAMP));

    SSpreadInfo *pInfo = GET_RES_INFO(pCtx)->interResultBuf;
    if (pInfo->hasResult != DATA_SET_FLAG) {
      setNull(pCtx->aOutputBuf, pCtx->outputType, pCtx->outputBytes);
      return;
    }

    *(double *)pCtx->aOutputBuf = pInfo->max - pInfo->min;
  }

  //  SET_VAL(pCtx, pCtx->numOfIteratedElems, 1);
  resetResultInfo(GET_RES_INFO(pCtx));
}