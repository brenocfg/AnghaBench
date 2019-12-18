#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  size_t int32_t ;
struct TYPE_11__ {scalar_t__ nStartQueryTimestamp; scalar_t__ aOutputBuf; } ;
struct TYPE_10__ {size_t numOfOutputCols; TYPE_2__* pSelectExpr; } ;
struct TYPE_9__ {scalar_t__ scanFlag; TYPE_5__* pCtx; TYPE_4__* pQuery; } ;
struct TYPE_7__ {size_t functionId; } ;
struct TYPE_8__ {TYPE_1__ pBase; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;
typedef  TYPE_5__ SQLFunctionCtx ;

/* Variables and functions */
 scalar_t__ SUPPLEMENTARY_SCAN ; 
 size_t TSDB_FUNC_TS ; 
 int /*<<< orphan*/  assert (int) ; 

void validateTimestampForSupplementResult(SQueryRuntimeEnv *pRuntimeEnv, int64_t numOfIncrementRes) {
  SQuery *        pQuery = pRuntimeEnv->pQuery;
  SQLFunctionCtx *pCtx = pRuntimeEnv->pCtx;

  if (pRuntimeEnv->scanFlag == SUPPLEMENTARY_SCAN && numOfIncrementRes > 0) {
    for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
      int32_t functionId = pQuery->pSelectExpr[i].pBase.functionId;
      if (functionId == TSDB_FUNC_TS) {
        assert(*(TSKEY *)pCtx[i].aOutputBuf == pCtx[i].nStartQueryTimestamp);
      }
    }
  }
}