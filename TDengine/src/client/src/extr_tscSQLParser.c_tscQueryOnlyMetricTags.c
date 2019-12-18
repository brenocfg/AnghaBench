#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_9__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_11__ {TYPE_2__ fieldsInfo; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {scalar_t__ colIdx; } ;
struct TYPE_10__ {scalar_t__ functionId; TYPE_1__ colInfo; } ;
typedef  TYPE_3__ SSqlExpr ;
typedef  TYPE_4__ SSqlCmd ;

/* Variables and functions */
 int /*<<< orphan*/  QUERY_IS_STABLE_QUERY (int /*<<< orphan*/ ) ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_FUNC_COUNT ; 
 scalar_t__ TSDB_FUNC_TAGPRJ ; 
 scalar_t__ TSDB_TBNAME_COLUMN_INDEX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__* tscSqlExprGet (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static int32_t tscQueryOnlyMetricTags(SSqlCmd* pCmd, bool* queryOnMetricTags) {
  assert(QUERY_IS_STABLE_QUERY(pCmd->type));

  *queryOnMetricTags = true;
  for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);

    if (pExpr->functionId != TSDB_FUNC_TAGPRJ &&
        !(pExpr->functionId == TSDB_FUNC_COUNT && pExpr->colInfo.colIdx == TSDB_TBNAME_COLUMN_INDEX)) {
      *queryOnMetricTags = false;
      break;
    }
  }

  return TSDB_CODE_SUCCESS;
}