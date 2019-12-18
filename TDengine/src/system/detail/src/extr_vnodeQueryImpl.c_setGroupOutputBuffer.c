#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_20__ {int /*<<< orphan*/ * resultInfo; TYPE_1__** result; } ;
struct TYPE_19__ {int outputBytes; int /*<<< orphan*/ * resultInfo; scalar_t__ aOutputBuf; scalar_t__ ptsOutputBuf; } ;
struct TYPE_18__ {size_t numOfOutputCols; int /*<<< orphan*/  pGroupbyExpr; TYPE_3__* pSelectExpr; } ;
struct TYPE_17__ {TYPE_7__* pCtx; TYPE_6__* pQuery; } ;
struct TYPE_16__ {int superTableQ; } ;
struct TYPE_14__ {size_t functionId; } ;
struct TYPE_15__ {TYPE_2__ pBase; } ;
struct TYPE_13__ {int numOfElems; scalar_t__ data; } ;
typedef  TYPE_4__ SResultInfo ;
typedef  TYPE_5__ SQueryRuntimeEnv ;
typedef  TYPE_6__ SQuery ;
typedef  TYPE_7__ SQLFunctionCtx ;
typedef  TYPE_8__ SOutputRes ;

/* Variables and functions */
 TYPE_4__* GET_RES_INFO (TYPE_7__*) ; 
 size_t TSDB_FUNC_BOTTOM ; 
 size_t TSDB_FUNC_DIFF ; 
 size_t TSDB_FUNC_TOP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  isGroupbyNormalCol (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setGroupOutputBuffer(SQueryRuntimeEnv *pRuntimeEnv, SOutputRes *pResult) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  // Note: pResult->result[i]->numOfElems == 0, there is only fixed number of results for each group
  for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
    assert(pResult->result[i]->numOfElems == 0 || pResult->result[i]->numOfElems == 1);

    SQLFunctionCtx *pCtx = &pRuntimeEnv->pCtx[i];
    pCtx->aOutputBuf = pResult->result[i]->data + pCtx->outputBytes * pResult->result[i]->numOfElems;

    int32_t functionId = pQuery->pSelectExpr[i].pBase.functionId;
    if (functionId == TSDB_FUNC_TOP || functionId == TSDB_FUNC_BOTTOM || functionId == TSDB_FUNC_DIFF) {
      pCtx->ptsOutputBuf = pRuntimeEnv->pCtx[0].aOutputBuf;
    }

    /*
     * set the output buffer information and intermediate buffer
     * not all queries require the interResultBuf, such as COUNT
     */
    pCtx->resultInfo = &pResult->resultInfo[i];

    // set super table query flag
    SResultInfo *pResInfo = GET_RES_INFO(pCtx);
    if (!isGroupbyNormalCol(pQuery->pGroupbyExpr)) {
      pResInfo->superTableQ = true;
    }
  }
}