#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_14__ {TYPE_4__* pCtx; } ;
struct TYPE_13__ {char* aOutputBuf; scalar_t__ outputBytes; } ;
struct TYPE_10__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_12__ {TYPE_1__ fieldsInfo; } ;
struct TYPE_11__ {scalar_t__ resBytes; scalar_t__ functionId; } ;
typedef  TYPE_2__ SSqlExpr ;
typedef  TYPE_3__ SSqlCmd ;
typedef  TYPE_4__ SQLFunctionCtx ;
typedef  TYPE_5__ SLocalReducer ;

/* Variables and functions */
 scalar_t__ TSDB_FUNC_TAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_2__* tscSqlExprGet (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void fillMultiRowsOfTagsVal(SSqlCmd *pCmd, int32_t numOfRes, SLocalReducer *pLocalReducer) {
  int32_t maxBufSize = 0;  // find the max tags column length to prepare the buffer
  for (int32_t k = 0; k < pCmd->fieldsInfo.numOfOutputCols; ++k) {
    SSqlExpr *pExpr = tscSqlExprGet(pCmd, k);
    if (maxBufSize < pExpr->resBytes && pExpr->functionId == TSDB_FUNC_TAG) {
      maxBufSize = pExpr->resBytes;
    }
  }

  assert(maxBufSize >= 0);

  char *buf = malloc((size_t) maxBufSize);
  for (int32_t k = 0; k < pCmd->fieldsInfo.numOfOutputCols; ++k) {
    SSqlExpr *pExpr = tscSqlExprGet(pCmd, k);
    if (pExpr->functionId != TSDB_FUNC_TAG) {
      continue;
    }

    int32_t inc = numOfRes - 1;  // tsdb_func_tag function only produce one row of result
    memset(buf, 0, (size_t)maxBufSize);

    SQLFunctionCtx *pCtx = &pLocalReducer->pCtx[k];
    memcpy(buf, pCtx->aOutputBuf, (size_t)pCtx->outputBytes);

    for (int32_t i = 0; i < inc; ++i) {
      pCtx->aOutputBuf += pCtx->outputBytes;
      memcpy(pCtx->aOutputBuf, buf, (size_t)pCtx->outputBytes);
    }
  }

  free(buf);
}