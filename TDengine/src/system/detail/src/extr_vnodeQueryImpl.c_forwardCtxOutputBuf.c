#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int64_t ;
typedef  size_t int32_t ;
struct TYPE_15__ {int /*<<< orphan*/  nStatus; } ;
struct TYPE_9__ {int /*<<< orphan*/  order; } ;
struct TYPE_14__ {size_t numOfOutputCols; TYPE_3__* pSelectExpr; TYPE_1__ order; } ;
struct TYPE_13__ {TYPE_4__* pCtx; TYPE_6__* pQuery; } ;
struct TYPE_12__ {size_t aOutputBuf; size_t outputBytes; size_t ptsOutputBuf; int /*<<< orphan*/  resultInfo; } ;
struct TYPE_10__ {size_t functionId; } ;
struct TYPE_11__ {TYPE_2__ pBase; } ;
typedef  TYPE_5__ SQueryRuntimeEnv ;
typedef  TYPE_6__ SQuery ;

/* Variables and functions */
 size_t GET_FORWARD_DIRECTION_FACTOR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_OUTER_FORWARD (int /*<<< orphan*/ ) ; 
 size_t TSDB_FUNC_BOTTOM ; 
 size_t TSDB_FUNC_DIFF ; 
 size_t TSDB_FUNC_TOP ; 
 size_t TSDB_KEYSIZE ; 
 TYPE_8__* aAggs ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  resetResultInfo (int /*<<< orphan*/ ) ; 

void forwardCtxOutputBuf(SQueryRuntimeEnv *pRuntimeEnv, int64_t output) {
  SQuery *pQuery = pRuntimeEnv->pQuery;
  int32_t factor = GET_FORWARD_DIRECTION_FACTOR(pQuery->order.order);

  // reset the execution contexts
  for (int32_t j = 0; j < pQuery->numOfOutputCols; ++j) {
    int32_t functionId = pQuery->pSelectExpr[j].pBase.functionId;
    assert(functionId != TSDB_FUNC_DIFF);

    // set next output position
    if (IS_OUTER_FORWARD(aAggs[functionId].nStatus)) {
      pRuntimeEnv->pCtx[j].aOutputBuf += pRuntimeEnv->pCtx[j].outputBytes * output * factor;
    }

    if (functionId == TSDB_FUNC_TOP || functionId == TSDB_FUNC_BOTTOM) {
      /*
       * NOTE: for top/bottom query, the value of first column of output (timestamp) are assigned
       * in the procedure of top/bottom routine
       * the output buffer in top/bottom routine is ptsOutputBuf, so we need to forward the output buffer
       *
       * diff function is handled in multi-output function
       */
      pRuntimeEnv->pCtx[j].ptsOutputBuf += TSDB_KEYSIZE * output * factor;
    }

    resetResultInfo(pRuntimeEnv->pCtx[j].resultInfo);
  }
}