#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  double int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {int /*<<< orphan*/  hasResult; } ;
struct TYPE_7__ {double* aOutputBuf; int /*<<< orphan*/  inputType; scalar_t__ hasNull; } ;
typedef  TYPE_1__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 scalar_t__ GET_DOUBLE_VAL (void*) ; 
 scalar_t__ GET_FLOAT_VAL (void*) ; 
 void* GET_INPUT_CHAR_INDEX (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_INT16_VAL (void*) ; 
 scalar_t__ GET_INT32_VAL (void*) ; 
 scalar_t__ GET_INT64_VAL (void*) ; 
 scalar_t__ GET_INT8_VAL (void*) ; 
 TYPE_4__* GET_RES_INFO (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_BIGINT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_DOUBLE ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_FLOAT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_INT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_SMALLINT ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_TINYINT ; 
 scalar_t__ isNull (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_sum_f(SQLFunctionCtx *pCtx, int32_t index) {
  void *pData = GET_INPUT_CHAR_INDEX(pCtx, index);
  if (pCtx->hasNull && isNull(pData, pCtx->inputType)) {
    return;
  }

  SET_VAL(pCtx, 1, 1);
  int64_t *res = pCtx->aOutputBuf;

  if (pCtx->inputType == TSDB_DATA_TYPE_TINYINT) {
    *res += GET_INT8_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_SMALLINT) {
    *res += GET_INT16_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_INT) {
    *res += GET_INT32_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_BIGINT) {
    *res += GET_INT64_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_DOUBLE) {
    double *retVal = pCtx->aOutputBuf;
    *retVal += GET_DOUBLE_VAL(pData);
  } else if (pCtx->inputType == TSDB_DATA_TYPE_FLOAT) {
    double *retVal = pCtx->aOutputBuf;
    *retVal += GET_FLOAT_VAL(pData);
  }

  GET_RES_INFO(pCtx)->hasResult = DATA_SET_FLAG;
}