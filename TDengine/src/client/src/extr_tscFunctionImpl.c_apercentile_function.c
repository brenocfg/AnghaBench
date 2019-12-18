#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_13__ {int /*<<< orphan*/  pHisto; } ;
struct TYPE_12__ {scalar_t__ size; scalar_t__ hasNull; int /*<<< orphan*/  inputType; } ;
struct TYPE_11__ {int /*<<< orphan*/  hasResult; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;
typedef  TYPE_3__ SAPercentileInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 double GET_DOUBLE_VAL (char*) ; 
 double GET_FLOAT_VAL (char*) ; 
 char* GET_INPUT_CHAR_INDEX (TYPE_2__*,scalar_t__) ; 
 double GET_INT16_VAL (char*) ; 
 double GET_INT32_VAL (char*) ; 
 double GET_INT64_VAL (char*) ; 
 double GET_INT8_VAL (char*) ; 
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_2__*,scalar_t__,int) ; 
#define  TSDB_DATA_TYPE_BIGINT 132 
#define  TSDB_DATA_TYPE_DOUBLE 131 
#define  TSDB_DATA_TYPE_FLOAT 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* getAPerctInfo (TYPE_2__*) ; 
 scalar_t__ isNull (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tHistogramAdd (int /*<<< orphan*/ *,double) ; 

__attribute__((used)) static void apercentile_function(SQLFunctionCtx *pCtx) {
  int32_t notNullElems = 0;

  SResultInfo *     pResInfo = GET_RES_INFO(pCtx);
  SAPercentileInfo *pInfo = getAPerctInfo(pCtx);

  for (int32_t i = 0; i < pCtx->size; ++i) {
    char *data = GET_INPUT_CHAR_INDEX(pCtx, i);
    if (pCtx->hasNull && isNull(data, pCtx->inputType)) {
      continue;
    }

    notNullElems += 1;
    double v = 0;

    switch (pCtx->inputType) {
      case TSDB_DATA_TYPE_TINYINT:
        v = GET_INT8_VAL(data);
        break;
      case TSDB_DATA_TYPE_SMALLINT:
        v = GET_INT16_VAL(data);
        break;
      case TSDB_DATA_TYPE_BIGINT:
        v = GET_INT64_VAL(data);
        break;
      case TSDB_DATA_TYPE_FLOAT:
        v = GET_FLOAT_VAL(data);
        break;
      case TSDB_DATA_TYPE_DOUBLE:
        v = GET_DOUBLE_VAL(data);
        break;
      default:
        v = GET_INT32_VAL(data);
        break;
    }

    tHistogramAdd(&pInfo->pHisto, v);
  }

  if (!pCtx->hasNull) {
    assert(pCtx->size == notNullElems);
  }

  SET_VAL(pCtx, notNullElems, 1);

  if (notNullElems > 0) {
    pResInfo->hasResult = DATA_SET_FLAG;
  }
}