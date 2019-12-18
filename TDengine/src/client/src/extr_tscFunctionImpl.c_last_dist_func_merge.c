#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ hasResult; scalar_t__ ts; } ;
struct TYPE_10__ {int size; int inputBytes; int aOutputBuf; } ;
struct TYPE_9__ {scalar_t__ superTableQ; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;
typedef  TYPE_3__ SFirstLastInfo ;

/* Variables and functions */
 scalar_t__ DATA_SET_FLAG ; 
 int /*<<< orphan*/  DO_UPDATE_TAG_COLUMNS (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* GET_INPUT_CHAR (TYPE_2__*) ; 
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int,char*,int) ; 

__attribute__((used)) static void last_dist_func_merge(SQLFunctionCtx *pCtx) {
  char *pData = GET_INPUT_CHAR(pCtx);

  SResultInfo *pResInfo = GET_RES_INFO(pCtx);
  assert(pCtx->size == 1 && pResInfo->superTableQ);

  // the input data is null
  SFirstLastInfo *pInput = (SFirstLastInfo *)(pData + pCtx->inputBytes);
  if (pInput->hasResult != DATA_SET_FLAG) {
    return;
  }

  SFirstLastInfo *pOutput = (SFirstLastInfo *)(pCtx->aOutputBuf + pCtx->inputBytes);
  if (pOutput->hasResult != DATA_SET_FLAG || pOutput->ts < pInput->ts) {
    memcpy(pCtx->aOutputBuf, pData, pCtx->inputBytes + sizeof(SFirstLastInfo));

    DO_UPDATE_TAG_COLUMNS(pCtx, 0);
  }
}