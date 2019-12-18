#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_11__ {int num; int /*<<< orphan*/  sum; } ;
struct TYPE_10__ {int /*<<< orphan*/  aOutputBuf; int /*<<< orphan*/  inputType; scalar_t__ hasNull; } ;
struct TYPE_9__ {scalar_t__ interResultBuf; scalar_t__ superTableQ; int /*<<< orphan*/  hasResult; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;
typedef  TYPE_3__ SAvgInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 scalar_t__ GET_DOUBLE_VAL (void*) ; 
 scalar_t__ GET_FLOAT_VAL (void*) ; 
 void* GET_INPUT_CHAR_INDEX (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_INT16_VAL (void*) ; 
 scalar_t__ GET_INT32_VAL (void*) ; 
 scalar_t__ GET_INT64_VAL (void*) ; 
 scalar_t__ GET_INT8_VAL (void*) ; 
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_BIGINT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_DOUBLE ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_FLOAT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_INT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_SMALLINT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_TINYINT ; 
 scalar_t__ isNull (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void avg_function_f(SQLFunctionCtx *pCtx, int32_t index) {
  void *pData = GET_INPUT_CHAR_INDEX(pCtx, index);
  if (pCtx->hasNull && isNull(pData, pCtx->inputType)) {
    return;
  }

  SET_VAL(pCtx, 1, 1);

  // NOTE: keep the intermediate result into the interResultBuf
  SResultInfo *pResInfo = GET_RES_INFO(pCtx);

  SAvgInfo *pAvgInfo = (SAvgInfo *)pResInfo->interResultBuf;

  if (pCtx->inputType == TSDB_DATA_TYPE_TINYINT) {
    pAvgInfo->sum += GET_INT8_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_SMALLINT) {
    pAvgInfo->sum += GET_INT16_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_INT) {
    pAvgInfo->sum += GET_INT32_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_BIGINT) {
    pAvgInfo->sum += GET_INT64_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_DOUBLE) {
    pAvgInfo->sum += GET_DOUBLE_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_FLOAT) {
    pAvgInfo->sum += GET_FLOAT_VAL(pData);
  }

  // restore sum and count of elements
  pAvgInfo->num += 1;

  // set has result flag
  pResInfo->hasResult = DATA_SET_FLAG;

  // keep the data into the final output buffer for super table query since this execution may be the last one
  if (pResInfo->superTableQ) {
    memcpy(pCtx->aOutputBuf, pResInfo->interResultBuf, sizeof(SAvgInfo));
  }
}