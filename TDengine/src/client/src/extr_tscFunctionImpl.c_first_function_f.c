#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {scalar_t__ order; int /*<<< orphan*/  inputBytes; int /*<<< orphan*/  aOutputBuf; int /*<<< orphan*/  inputType; scalar_t__ hasNull; } ;
struct TYPE_9__ {int complete; int /*<<< orphan*/  hasResult; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 int /*<<< orphan*/  DO_UPDATE_TAG_COLUMNS (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* GET_INPUT_CHAR_INDEX (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_2__*,int,int) ; 
 scalar_t__ TSQL_SO_DESC ; 
 scalar_t__ isNull (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void first_function_f(SQLFunctionCtx *pCtx, int32_t index) {
  if (pCtx->order == TSQL_SO_DESC) {
    return;
  }

  void *pData = GET_INPUT_CHAR_INDEX(pCtx, index);
  if (pCtx->hasNull && isNull(pData, pCtx->inputType)) {
    return;
  }

  SET_VAL(pCtx, 1, 1);
  memcpy(pCtx->aOutputBuf, pData, pCtx->inputBytes);
  DO_UPDATE_TAG_COLUMNS(pCtx, 0);

  SResultInfo *pInfo = GET_RES_INFO(pCtx);
  pInfo->hasResult = DATA_SET_FLAG;
  pInfo->complete = true;  // get the first not-null data, completed
}