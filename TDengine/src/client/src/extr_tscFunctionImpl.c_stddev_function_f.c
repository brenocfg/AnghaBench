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
struct TYPE_12__ {int /*<<< orphan*/  inputType; scalar_t__ hasNull; } ;
struct TYPE_11__ {TYPE_1__* interResultBuf; } ;
struct TYPE_10__ {scalar_t__ stage; double avg; int /*<<< orphan*/  res; } ;
typedef  TYPE_1__ SStddevInfo ;
typedef  TYPE_2__ SResultInfo ;
typedef  TYPE_3__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  GET_DOUBLE_VAL (void*) ; 
 int /*<<< orphan*/  GET_FLOAT_VAL (void*) ; 
 void* GET_INPUT_CHAR_INDEX (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_INT16_VAL (void*) ; 
 int /*<<< orphan*/  GET_INT32_VAL (void*) ; 
 int /*<<< orphan*/  GET_INT64_VAL (void*) ; 
 int /*<<< orphan*/  GET_INT8_VAL (void*) ; 
 TYPE_2__* GET_RES_INFO (TYPE_3__*) ; 
 int /*<<< orphan*/  POW2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_3__*,int,int) ; 
#define  TSDB_DATA_TYPE_BIGINT 133 
#define  TSDB_DATA_TYPE_DOUBLE 132 
#define  TSDB_DATA_TYPE_FLOAT 131 
#define  TSDB_DATA_TYPE_INT 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int /*<<< orphan*/  avg_function_f (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ isNull (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pError (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stddev_function_f(SQLFunctionCtx *pCtx, int32_t index) {
  // the second stage to calculate standard deviation
  SResultInfo *pResInfo = GET_RES_INFO(pCtx);
  SStddevInfo *pStd = pResInfo->interResultBuf;

  /* the first stage is to calculate average value */
  if (pStd->stage == 0) {
    avg_function_f(pCtx, index);
  } else {
    double avg = pStd->avg;
    void * pData = GET_INPUT_CHAR_INDEX(pCtx, index);

    if (pCtx->hasNull && isNull(pData, pCtx->inputType)) {
      return;
    }

    switch (pCtx->inputType) {
      case TSDB_DATA_TYPE_INT: {
        pStd->res += POW2(GET_INT32_VAL(pData) - avg);
        break;
      }
      case TSDB_DATA_TYPE_FLOAT: {
        pStd->res += POW2(GET_FLOAT_VAL(pData) - avg);
        break;
      }
      case TSDB_DATA_TYPE_DOUBLE: {
        pStd->res += POW2(GET_DOUBLE_VAL(pData) - avg);
        break;
      }
      case TSDB_DATA_TYPE_BIGINT: {
        pStd->res += POW2(GET_INT64_VAL(pData) - avg);
        break;
      }
      case TSDB_DATA_TYPE_SMALLINT: {
        pStd->res += POW2(GET_INT16_VAL(pData) - avg);
        break;
      }
      case TSDB_DATA_TYPE_TINYINT: {
        pStd->res += POW2(GET_INT8_VAL(pData) - avg);
        break;
      }
      default:
        pError("stddev function not support data type:%d", pCtx->inputType);
    }

    SET_VAL(pCtx, 1, 1);
  }
}