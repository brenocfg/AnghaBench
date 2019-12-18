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
typedef  scalar_t__ int32_t ;
struct TYPE_11__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_10__ {scalar_t__ numOfExprs; } ;
struct TYPE_13__ {scalar_t__ command; TYPE_2__ fieldsInfo; TYPE_1__ exprsInfo; } ;
struct TYPE_12__ {scalar_t__ functionId; } ;
typedef  TYPE_3__ SSqlExpr ;
typedef  TYPE_4__ SSqlCmd ;
typedef  int /*<<< orphan*/  SMeterMetaInfo ;

/* Variables and functions */
 scalar_t__ TSDB_FUNC_PRJ ; 
 scalar_t__ TSDB_FUNC_TAG ; 
 scalar_t__ TSDB_FUNC_TAGPRJ ; 
 scalar_t__ TSDB_FUNC_TS ; 
 scalar_t__ TSDB_SQL_RETRIEVE_EMPTY_RESULT ; 
 int /*<<< orphan*/  UTIL_METER_IS_METRIC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tscGetMeterMetaInfo (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tscQueryMetricTags (TYPE_4__*) ; 
 TYPE_3__* tscSqlExprGet (TYPE_4__*,scalar_t__) ; 

bool tscProjectionQueryOnMetric(SSqlCmd* pCmd) {
  assert(pCmd != NULL);

  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  /*
   * In following cases, return false for project query on metric
   * 1. failed to get metermeta from server; 2. not a metric; 3. limit 0; 4. show query, instead of a select query
   */
  if (pMeterMetaInfo == NULL || !UTIL_METER_IS_METRIC(pMeterMetaInfo) ||
      pCmd->command == TSDB_SQL_RETRIEVE_EMPTY_RESULT || pCmd->exprsInfo.numOfExprs == 0) {
    return false;
  }

  // only query on tag, not a projection query
  if (tscQueryMetricTags(pCmd)) {
    return false;
  }

  //for project query, only the following two function is allowed
  for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);
    int32_t functionId = pExpr->functionId;
    if (functionId != TSDB_FUNC_PRJ && functionId != TSDB_FUNC_TAGPRJ &&
        functionId != TSDB_FUNC_TAG && functionId != TSDB_FUNC_TS) {
      return false;
    }
  }

  return true;
}