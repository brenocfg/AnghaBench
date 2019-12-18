#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_10__ {scalar_t__ numOfRes; } ;
struct TYPE_9__ {scalar_t__ functionId; } ;
struct TYPE_7__ {scalar_t__ numOfExprs; } ;
struct TYPE_8__ {TYPE_1__ exprsInfo; } ;
typedef  TYPE_2__ SSqlCmd ;
typedef  int /*<<< orphan*/  SQLFunctionCtx ;

/* Variables and functions */
 TYPE_6__* GET_RES_INFO (int /*<<< orphan*/ *) ; 
 scalar_t__ TSDB_FUNC_TAG ; 
 scalar_t__ TSDB_FUNC_TAGPRJ ; 
 scalar_t__ TSDB_FUNC_TS ; 
 TYPE_3__* tscSqlExprGet (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int64_t getNumOfResultLocal(SSqlCmd *pCmd, SQLFunctionCtx *pCtx) {
  int64_t maxOutput = 0;

  for (int32_t j = 0; j < pCmd->exprsInfo.numOfExprs; ++j) {
    int32_t functionId = tscSqlExprGet(pCmd, j)->functionId;

    /*
     * ts, tag, tagprj function can not decide the output number of current query
     * the number of output result is decided by main output
     */
    if (functionId == TSDB_FUNC_TS || functionId == TSDB_FUNC_TAG || functionId == TSDB_FUNC_TAGPRJ) {
      continue;
    }

    if (maxOutput < GET_RES_INFO(&pCtx[j])->numOfRes) {
      maxOutput = GET_RES_INFO(&pCtx[j])->numOfRes;
    }
  }
  return maxOutput;
}