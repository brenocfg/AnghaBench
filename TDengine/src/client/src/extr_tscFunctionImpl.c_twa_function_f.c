#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_14__ {int* ptsList; scalar_t__ nStartQueryTimestamp; int /*<<< orphan*/  aOutputBuf; int /*<<< orphan*/  inputType; scalar_t__ hasNull; } ;
struct TYPE_13__ {TYPE_1__* interResultBuf; scalar_t__ superTableQ; void* hasResult; } ;
struct TYPE_12__ {scalar_t__ lastKey; int dOutput; int dLastValue; int iOutput; int iLastValue; void* hasResult; } ;
typedef  int TSKEY ;
typedef  TYPE_1__ STwaInfo ;
typedef  TYPE_2__ SResultInfo ;
typedef  TYPE_3__ SQLFunctionCtx ;

/* Variables and functions */
 void* DATA_SET_FLAG ; 
 void* GET_INPUT_CHAR_INDEX (TYPE_3__*,size_t) ; 
 TYPE_2__* GET_RES_INFO (TYPE_3__*) ; 
 scalar_t__ INT64_MIN ; 
 int /*<<< orphan*/  SET_VAL (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_DOUBLE ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_FLOAT ; 
 scalar_t__ isNull (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  setTWALastVal (TYPE_3__*,void*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static bool twa_function_f(SQLFunctionCtx *pCtx, int32_t index) {
  void *pData = GET_INPUT_CHAR_INDEX(pCtx, index);
  if (pCtx->hasNull && isNull(pData, pCtx->inputType)) {
    return true;
  }

  SET_VAL(pCtx, 1, 1);

  TSKEY *primaryKey = pCtx->ptsList;

  SResultInfo *pResInfo = GET_RES_INFO(pCtx);
  STwaInfo *   pInfo = pResInfo->interResultBuf;

  if (pInfo->lastKey == INT64_MIN) {
    pInfo->lastKey = pCtx->nStartQueryTimestamp;
    setTWALastVal(pCtx, pData, 0, pInfo);

    pInfo->hasResult = DATA_SET_FLAG;
  }

  if (pCtx->inputType == TSDB_DATA_TYPE_FLOAT || pCtx->inputType == TSDB_DATA_TYPE_DOUBLE) {
    pInfo->dOutput += pInfo->dLastValue * (primaryKey[index] - pInfo->lastKey);
  } else {
    pInfo->iOutput += pInfo->iLastValue * (primaryKey[index] - pInfo->lastKey);
  }

  // record the last key/value
  pInfo->lastKey = primaryKey[index];
  setTWALastVal(pCtx, pData, 0, pInfo);

  //  pCtx->numOfIteratedElems += 1;
  pResInfo->hasResult = DATA_SET_FLAG;

  if (pResInfo->superTableQ) {
    memcpy(pCtx->aOutputBuf, pResInfo->interResultBuf, sizeof(STwaInfo));
  }

  return true;
}