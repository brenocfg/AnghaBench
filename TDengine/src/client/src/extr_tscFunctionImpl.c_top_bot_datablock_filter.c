#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  dKey; int /*<<< orphan*/  i64Key; } ;
struct TYPE_11__ {TYPE_2__ v; } ;
typedef  TYPE_3__ tValuePair ;
typedef  scalar_t__ int32_t ;
struct TYPE_14__ {scalar_t__ interResultBuf; } ;
struct TYPE_13__ {int inputType; TYPE_1__* param; } ;
struct TYPE_12__ {scalar_t__ num; TYPE_3__* res; } ;
struct TYPE_9__ {scalar_t__ i64Key; } ;
typedef  TYPE_4__ STopBotInfo ;
typedef  TYPE_5__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  GET_DOUBLE_VAL (char*) ; 
 int /*<<< orphan*/  GET_FLOAT_VAL (char*) ; 
 int /*<<< orphan*/  GET_INT16_VAL (char*) ; 
 int /*<<< orphan*/  GET_INT32_VAL (char*) ; 
 int /*<<< orphan*/  GET_INT64_VAL (char*) ; 
 int /*<<< orphan*/  GET_INT8_VAL (char*) ; 
 TYPE_7__* GET_RES_INFO (TYPE_5__*) ; 
#define  TSDB_DATA_TYPE_BIGINT 133 
#define  TSDB_DATA_TYPE_DOUBLE 132 
#define  TSDB_DATA_TYPE_FLOAT 131 
#define  TSDB_DATA_TYPE_INT 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 scalar_t__ TSDB_FUNC_TOP ; 

bool top_bot_datablock_filter(SQLFunctionCtx *pCtx, int32_t functionId, char *minval, char *maxval) {
  STopBotInfo *pTopBotInfo = (STopBotInfo *)GET_RES_INFO(pCtx)->interResultBuf;

  int32_t numOfExistsRes = pTopBotInfo->num;

  // required number of results are not reached, continue load data block
  if (numOfExistsRes < pCtx->param[0].i64Key) {
    return true;
  }

  tValuePair *pRes = pTopBotInfo->res;

  if (functionId == TSDB_FUNC_TOP) {
    switch (pCtx->inputType) {
      case TSDB_DATA_TYPE_TINYINT:
        return GET_INT8_VAL(maxval) > pRes[0].v.i64Key;
      case TSDB_DATA_TYPE_SMALLINT:
        return GET_INT16_VAL(maxval) > pRes[0].v.i64Key;
      case TSDB_DATA_TYPE_INT:
        return GET_INT32_VAL(maxval) > pRes[0].v.i64Key;
      case TSDB_DATA_TYPE_BIGINT:
        return GET_INT64_VAL(maxval) > pRes[0].v.i64Key;
      case TSDB_DATA_TYPE_FLOAT:
        return GET_FLOAT_VAL(maxval) > pRes[0].v.dKey;
      case TSDB_DATA_TYPE_DOUBLE:
        return GET_DOUBLE_VAL(maxval) > pRes[0].v.dKey;
      default:
        return true;
    }
  } else {
    switch (pCtx->inputType) {
      case TSDB_DATA_TYPE_TINYINT:
        return GET_INT8_VAL(minval) < pRes[0].v.i64Key;
      case TSDB_DATA_TYPE_SMALLINT:
        return GET_INT16_VAL(minval) < pRes[0].v.i64Key;
      case TSDB_DATA_TYPE_INT:
        return GET_INT32_VAL(minval) < pRes[0].v.i64Key;
      case TSDB_DATA_TYPE_BIGINT:
        return GET_INT64_VAL(minval) < pRes[0].v.i64Key;
      case TSDB_DATA_TYPE_FLOAT:
        return GET_FLOAT_VAL(minval) < pRes[0].v.dKey;
      case TSDB_DATA_TYPE_DOUBLE:
        return GET_DOUBLE_VAL(minval) < pRes[0].v.dKey;
      default:
        return true;
    }
  }
}