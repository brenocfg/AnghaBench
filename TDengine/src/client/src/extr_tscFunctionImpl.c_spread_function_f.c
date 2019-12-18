#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_12__ {int /*<<< orphan*/  aOutputBuf; int /*<<< orphan*/  inputType; scalar_t__ hasNull; } ;
struct TYPE_11__ {TYPE_1__* interResultBuf; scalar_t__ superTableQ; void* hasResult; } ;
struct TYPE_10__ {double max; double min; void* hasResult; } ;
typedef  TYPE_1__ SSpreadInfo ;
typedef  TYPE_2__ SResultInfo ;
typedef  TYPE_3__ SQLFunctionCtx ;

/* Variables and functions */
 void* DATA_SET_FLAG ; 
 double GET_DOUBLE_VAL (void*) ; 
 double GET_FLOAT_VAL (void*) ; 
 void* GET_INPUT_CHAR_INDEX (TYPE_3__*,int /*<<< orphan*/ ) ; 
 double GET_INT16_VAL (void*) ; 
 double GET_INT32_VAL (void*) ; 
 double GET_INT64_VAL (void*) ; 
 double GET_INT8_VAL (void*) ; 
 TYPE_2__* GET_RES_INFO (TYPE_3__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_BIGINT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_DOUBLE ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_FLOAT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_INT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_SMALLINT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_TIMESTAMP ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_TINYINT ; 
 scalar_t__ isNull (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static void spread_function_f(SQLFunctionCtx *pCtx, int32_t index) {
  void *pData = GET_INPUT_CHAR_INDEX(pCtx, index);
  if (pCtx->hasNull && isNull(pData, pCtx->inputType)) {
    return;
  }

  SET_VAL(pCtx, 1, 1);

  SResultInfo *pResInfo = GET_RES_INFO(pCtx);
  SSpreadInfo *pInfo = pResInfo->interResultBuf;

  double val = 0.0;
  if (pCtx->inputType == TSDB_DATA_TYPE_TINYINT) {
    val = GET_INT8_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_SMALLINT) {
    val = GET_INT16_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_INT) {
    val = GET_INT32_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_BIGINT || pCtx->inputType == TSDB_DATA_TYPE_TIMESTAMP) {
    val = GET_INT64_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_DOUBLE) {
    val = GET_DOUBLE_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_FLOAT) {
    val = GET_FLOAT_VAL(pData);
  }

  // keep the result data in output buffer, not in the intermediate buffer
  if (val > pInfo->max) {
    pInfo->max = val;
  }

  if (val < pInfo->min) {
    pInfo->min = val;
  }

  pResInfo->hasResult = DATA_SET_FLAG;
  pInfo->hasResult = DATA_SET_FLAG;

  if (pResInfo->superTableQ) {
    memcpy(pCtx->aOutputBuf, pResInfo->interResultBuf, sizeof(SSpreadInfo));
  }
}