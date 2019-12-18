#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {void* hasResult; int /*<<< orphan*/  ts; } ;
struct TYPE_13__ {int size; TYPE_1__* param; scalar_t__ inputBytes; scalar_t__ aOutputBuf; int /*<<< orphan*/  inputType; } ;
struct TYPE_12__ {scalar_t__ superTableQ; scalar_t__ interResultBuf; } ;
struct TYPE_11__ {int /*<<< orphan*/  i64Key; } ;
typedef  TYPE_2__ SResultInfo ;
typedef  TYPE_3__ SQLFunctionCtx ;
typedef  TYPE_4__ SLastrowInfo ;

/* Variables and functions */
 void* DATA_SET_FLAG ; 
 int /*<<< orphan*/  DO_UPDATE_TAG_COLUMNS (TYPE_3__*,int /*<<< orphan*/ ) ; 
 char* GET_INPUT_CHAR (TYPE_3__*) ; 
 TYPE_2__* GET_RES_INFO (TYPE_3__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assignVal (scalar_t__,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void last_row_function(SQLFunctionCtx *pCtx) {
  assert(pCtx->size == 1);

  char *pData = GET_INPUT_CHAR(pCtx);
  assignVal(pCtx->aOutputBuf, pData, pCtx->inputBytes, pCtx->inputType);

  SResultInfo *pResInfo = GET_RES_INFO(pCtx);

  SLastrowInfo *pInfo = (SLastrowInfo *)pResInfo->interResultBuf;
  pInfo->ts = pCtx->param[0].i64Key;
  pInfo->hasResult = DATA_SET_FLAG;

  // set the result to final result buffer
  if (pResInfo->superTableQ) {
    SLastrowInfo *pInfo1 = (SLastrowInfo *)(pCtx->aOutputBuf + pCtx->inputBytes);
    pInfo1->ts = pCtx->param[0].i64Key;
    pInfo1->hasResult = DATA_SET_FLAG;

    DO_UPDATE_TAG_COLUMNS(pCtx, 0);
  }

  SET_VAL(pCtx, pCtx->size, 1);
}