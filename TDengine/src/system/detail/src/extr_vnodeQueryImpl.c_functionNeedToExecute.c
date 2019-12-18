#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {scalar_t__ complete; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  int /*<<< orphan*/  SQueryRuntimeEnv ;
typedef  int /*<<< orphan*/  SQLFunctionCtx ;

/* Variables and functions */
 TYPE_1__* GET_RES_INFO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_MASTER_SCAN (int /*<<< orphan*/ *) ; 
 scalar_t__ TSDB_FUNC_FIRST ; 
 scalar_t__ TSDB_FUNC_FIRST_DST ; 
 scalar_t__ TSDB_FUNC_LAST ; 
 scalar_t__ TSDB_FUNC_LAST_DST ; 
 scalar_t__ TSDB_FUNC_TAG ; 
 scalar_t__ TSDB_FUNC_TAG_DUMMY ; 
 scalar_t__ TSDB_FUNC_TS ; 
 scalar_t__ TSDB_FUNC_TS_DUMMY ; 

__attribute__((used)) static bool functionNeedToExecute(SQueryRuntimeEnv *pRuntimeEnv, SQLFunctionCtx *pCtx, int32_t functionId) {
  SResultInfo *pResInfo = GET_RES_INFO(pCtx);

  if (pResInfo->complete || functionId == TSDB_FUNC_TAG_DUMMY || functionId == TSDB_FUNC_TS_DUMMY) {
    return false;
  }

  if (!IS_MASTER_SCAN(pRuntimeEnv) &&
      !(functionId == TSDB_FUNC_LAST_DST || functionId == TSDB_FUNC_FIRST_DST || functionId == TSDB_FUNC_FIRST ||
        functionId == TSDB_FUNC_LAST || functionId == TSDB_FUNC_TAG || functionId == TSDB_FUNC_TS)) {
    return false;
  }

  return true;
}