#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {int /*<<< orphan*/  inputType; scalar_t__ aOutputBuf; } ;
typedef  TYPE_1__ SQLFunctionCtx ;

/* Variables and functions */
 double DBL_MAX ; 
 float FLT_MAX ; 
 int /*<<< orphan*/  GET_TRUE_DATA_TYPE () ; 
 int /*<<< orphan*/  INT16_MAX ; 
 int /*<<< orphan*/  INT32_MAX ; 
 int /*<<< orphan*/  INT64_MAX ; 
 int /*<<< orphan*/  INT8_MAX ; 
#define  TSDB_DATA_TYPE_BIGINT 133 
#define  TSDB_DATA_TYPE_DOUBLE 132 
#define  TSDB_DATA_TYPE_FLOAT 131 
#define  TSDB_DATA_TYPE_INT 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int /*<<< orphan*/  function_setup (TYPE_1__*) ; 
 int /*<<< orphan*/  pError (char*,int /*<<< orphan*/ ) ; 
 int type ; 

__attribute__((used)) static bool min_func_setup(SQLFunctionCtx *pCtx) {
  if (!function_setup(pCtx)) {
    return false;  // not initialized since it has been initialized
  }

  GET_TRUE_DATA_TYPE();

  switch (type) {
    case TSDB_DATA_TYPE_INT:
      *((int32_t *)pCtx->aOutputBuf) = INT32_MAX;
      break;
    case TSDB_DATA_TYPE_FLOAT:
      *((float *)pCtx->aOutputBuf) = FLT_MAX;
      break;
    case TSDB_DATA_TYPE_DOUBLE:
      *((double *)pCtx->aOutputBuf) = DBL_MAX;
      break;
    case TSDB_DATA_TYPE_BIGINT:
      *((int64_t *)pCtx->aOutputBuf) = INT64_MAX;
      break;
    case TSDB_DATA_TYPE_SMALLINT:
      *((int16_t *)pCtx->aOutputBuf) = INT16_MAX;
      break;
    case TSDB_DATA_TYPE_TINYINT:
      *((int8_t *)pCtx->aOutputBuf) = INT8_MAX;
      break;
    default:
      pError("illegal data type:%d in min/max query", pCtx->inputType);
  }

  return true;
}