#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_21__ {TYPE_7__* pResult; TYPE_1__* pSidSet; } ;
struct TYPE_20__ {int nAlloc; } ;
struct TYPE_19__ {TYPE_5__* pSelectExpr; int /*<<< orphan*/  pGroupbyExpr; } ;
struct TYPE_17__ {scalar_t__ functionId; TYPE_3__* arg; } ;
struct TYPE_18__ {scalar_t__ resType; TYPE_4__ pBase; } ;
struct TYPE_15__ {int i64; } ;
struct TYPE_16__ {TYPE_2__ argValue; } ;
struct TYPE_14__ {int numOfSubSet; } ;
typedef  TYPE_5__ SSqlFunctionExpr ;
typedef  TYPE_6__ SQuery ;
typedef  TYPE_7__ SOutputRes ;
typedef  TYPE_8__ SMeterQuerySupportObj ;

/* Variables and functions */
 int TSDB_CODE_SERV_OUT_OF_MEMORY ; 
 int TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 scalar_t__ TSDB_FUNC_BOTTOM ; 
 scalar_t__ TSDB_FUNC_TOP ; 
 TYPE_7__* calloc (int,int) ; 
 int /*<<< orphan*/  createGroupResultBuf (TYPE_6__*,TYPE_7__*,int) ; 
 scalar_t__ isGroupbyNormalCol (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t allocateOutputBufForGroup(SMeterQuerySupportObj *pSupporter, SQuery *pQuery, bool isMetricQuery) {
  int32_t slot = 0;

  if (isGroupbyNormalCol(pQuery->pGroupbyExpr)) {
    slot = 10000;
  } else {
    slot = pSupporter->pSidSet->numOfSubSet;
  }

  pSupporter->pResult = calloc(1, sizeof(SOutputRes) * slot);
  if (pSupporter->pResult == NULL) {
    return TSDB_CODE_SERV_OUT_OF_MEMORY;
  }

  // create group result buffer
  for (int32_t k = 0; k < slot; ++k) {
    SOutputRes *pOneRes = &pSupporter->pResult[k];

    /*
     * for top/bottom query, the output for group by normal column, the output rows is equals to the
     * maximum rows, instead of 1.
     */
    SSqlFunctionExpr *pExpr = &pQuery->pSelectExpr[1];
    if ((pExpr->pBase.functionId == TSDB_FUNC_TOP || pExpr->pBase.functionId == TSDB_FUNC_BOTTOM) &&
        pExpr->resType != TSDB_DATA_TYPE_BINARY) {
      pOneRes->nAlloc = pExpr->pBase.arg[0].argValue.i64;
    } else {
      pOneRes->nAlloc = 1;
    }

    createGroupResultBuf(pQuery, pOneRes, isMetricQuery);
  }

  return TSDB_CODE_SUCCESS;
}