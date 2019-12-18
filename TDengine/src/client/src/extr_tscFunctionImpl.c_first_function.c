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
typedef  scalar_t__ int32_t ;
struct TYPE_10__ {scalar_t__ order; scalar_t__ size; int /*<<< orphan*/  inputBytes; int /*<<< orphan*/  aOutputBuf; int /*<<< orphan*/  inputType; scalar_t__ hasNull; int /*<<< orphan*/  blockStatus; } ;
struct TYPE_9__ {int complete; int /*<<< orphan*/  hasResult; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 int /*<<< orphan*/  DO_UPDATE_TAG_COLUMNS (TYPE_2__*,scalar_t__) ; 
 char* GET_INPUT_CHAR_INDEX (TYPE_2__*,scalar_t__) ; 
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  IS_DATA_BLOCK_LOADED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ TSQL_SO_DESC ; 
 scalar_t__ isNull (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void first_function(SQLFunctionCtx *pCtx) {
  if (!IS_DATA_BLOCK_LOADED(pCtx->blockStatus) || pCtx->order == TSQL_SO_DESC) {
    return;
  }

  int32_t notNullElems = 0;

  // handle the null value
  for (int32_t i = 0; i < pCtx->size; ++i) {
    char *data = GET_INPUT_CHAR_INDEX(pCtx, i);
    if (pCtx->hasNull && isNull(data, pCtx->inputType)) {
      continue;
    }

    memcpy(pCtx->aOutputBuf, data, pCtx->inputBytes);
    DO_UPDATE_TAG_COLUMNS(pCtx, i);

    SResultInfo *pInfo = GET_RES_INFO(pCtx);
    pInfo->hasResult = DATA_SET_FLAG;
    pInfo->complete = true;

    notNullElems++;
    break;
  }

  SET_VAL(pCtx, notNullElems, 1);
}