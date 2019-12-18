#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  double int8_t ;
typedef  double int64_t ;
typedef  scalar_t__ int32_t ;
typedef  double int16_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* xFunction ) (TYPE_3__*) ;} ;
struct TYPE_11__ {scalar_t__ numOfTagCols; TYPE_3__** pTagCtxList; } ;
struct TYPE_13__ {scalar_t__ size; TYPE_1__ tagInfo; } ;
struct TYPE_12__ {int /*<<< orphan*/  superTableQ; } ;
typedef  TYPE_2__ SResultInfo ;
typedef  TYPE_3__ SQLFunctionCtx ;

/* Variables and functions */
 char DATA_SET_FLAG ; 
 int /*<<< orphan*/  DUPATE_DATA_WITHOUT_TS (TYPE_3__*,double,double,scalar_t__,int) ; 
 double GET_DOUBLE_VAL (char*) ; 
 float GET_FLOAT_VAL (char*) ; 
 char* GET_INPUT_CHAR_INDEX (TYPE_3__*,scalar_t__) ; 
 double GET_INT16_VAL (char*) ; 
 scalar_t__ GET_INT32_VAL (char*) ; 
 double GET_INT64_VAL (char*) ; 
 double GET_INT8_VAL (char*) ; 
 TYPE_2__* GET_RES_INFO (TYPE_3__*) ; 
 int /*<<< orphan*/  GET_TRUE_DATA_TYPE () ; 
#define  TSDB_DATA_TYPE_BIGINT 133 
#define  TSDB_DATA_TYPE_DOUBLE 132 
#define  TSDB_DATA_TYPE_FLOAT 131 
#define  TSDB_DATA_TYPE_INT 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 size_t TSDB_FUNC_TAG ; 
 TYPE_6__* aAggs ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int type ; 

__attribute__((used)) static int32_t minmax_merge_impl(SQLFunctionCtx *pCtx, int32_t bytes, char *output, bool isMin) {
  int32_t notNullElems = 0;

  GET_TRUE_DATA_TYPE();

  SResultInfo *pResInfo = GET_RES_INFO(pCtx);
  assert(pResInfo->superTableQ);

  for (int32_t i = 0; i < pCtx->size; ++i) {
    char *input = GET_INPUT_CHAR_INDEX(pCtx, i);
    if (input[bytes] != DATA_SET_FLAG) {
      continue;
    }

    switch (type) {
      case TSDB_DATA_TYPE_TINYINT: {
        int8_t v = GET_INT8_VAL(input);
        DUPATE_DATA_WITHOUT_TS(pCtx, *(int8_t *)output, v, notNullElems, isMin);
        break;
      };
      case TSDB_DATA_TYPE_SMALLINT: {
        int16_t v = GET_INT16_VAL(input);
        DUPATE_DATA_WITHOUT_TS(pCtx, *(int16_t *)output, v, notNullElems, isMin);
        break;
      }
      case TSDB_DATA_TYPE_INT: {
        int32_t v = GET_INT32_VAL(input);
        if ((*(int32_t *)output < v) ^ isMin) {
          *(int32_t *)output = v;

          for (int32_t i = 0; i < pCtx->tagInfo.numOfTagCols; ++i) {
            SQLFunctionCtx *__ctx = pCtx->tagInfo.pTagCtxList[i];
            aAggs[TSDB_FUNC_TAG].xFunction(__ctx);
          }

          notNullElems++;
        }
        break;
      }
      case TSDB_DATA_TYPE_FLOAT: {
        float v = GET_FLOAT_VAL(input);
        DUPATE_DATA_WITHOUT_TS(pCtx, *(float *)output, v, notNullElems, isMin);
        break;
      }
      case TSDB_DATA_TYPE_DOUBLE: {
        double v = GET_DOUBLE_VAL(input);
        DUPATE_DATA_WITHOUT_TS(pCtx, *(double *)output, v, notNullElems, isMin);
        break;
      }
      case TSDB_DATA_TYPE_BIGINT: {
        int64_t v = GET_INT64_VAL(input);
        DUPATE_DATA_WITHOUT_TS(pCtx, *(int64_t *)output, v, notNullElems, isMin);
        break;
      };
      default:
        break;
    }
  }

  return notNullElems;
}