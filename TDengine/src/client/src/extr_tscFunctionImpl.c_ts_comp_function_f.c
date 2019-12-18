#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {int /*<<< orphan*/  i64Key; } ;
struct TYPE_13__ {int /*<<< orphan*/  size; TYPE_1__ tag; int /*<<< orphan*/  inputType; scalar_t__ hasNull; } ;
struct TYPE_12__ {int /*<<< orphan*/  hasResult; TYPE_2__* interResultBuf; } ;
struct TYPE_11__ {int /*<<< orphan*/ * pTSBuf; } ;
typedef  TYPE_2__ STSCompInfo ;
typedef  int /*<<< orphan*/  STSBuf ;
typedef  TYPE_3__ SResultInfo ;
typedef  TYPE_4__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 void* GET_INPUT_CHAR_INDEX (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* GET_RES_INFO (TYPE_4__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TSDB_KEYSIZE ; 
 scalar_t__ isNull (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsBufAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ts_comp_function_f(SQLFunctionCtx *pCtx, int32_t index) {
  void *pData = GET_INPUT_CHAR_INDEX(pCtx, index);
  if (pCtx->hasNull && isNull(pData, pCtx->inputType)) {
    return;
  }

  SResultInfo *pResInfo = GET_RES_INFO(pCtx);
  STSCompInfo *pInfo = pResInfo->interResultBuf;

  STSBuf *pTSbuf = pInfo->pTSBuf;

  tsBufAppend(pTSbuf, 0, pCtx->tag.i64Key, pData, TSDB_KEYSIZE);
  SET_VAL(pCtx, pCtx->size, 1);

  pResInfo->hasResult = DATA_SET_FLAG;
}