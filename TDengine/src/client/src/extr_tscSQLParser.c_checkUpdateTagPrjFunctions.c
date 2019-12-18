#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_13__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_15__ {TYPE_2__ fieldsInfo; } ;
struct TYPE_12__ {scalar_t__ colId; } ;
struct TYPE_14__ {scalar_t__ functionId; TYPE_1__ colInfo; } ;
struct TYPE_11__ {int nStatus; } ;
typedef  TYPE_3__ SSqlExpr ;
typedef  TYPE_4__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int TSDB_FUNCSTATE_SELECTIVITY ; 
 scalar_t__ TSDB_FUNC_LAST_ROW ; 
 scalar_t__ TSDB_FUNC_PRJ ; 
 scalar_t__ TSDB_FUNC_TAGPRJ ; 
 scalar_t__ TSDB_FUNC_TS ; 
 TYPE_10__* aAggs ; 
 int /*<<< orphan*/  doUpdateSqlFunctionForTagPrj (TYPE_4__*) ; 
 int /*<<< orphan*/  setErrMsg (TYPE_4__*,char const*) ; 
 TYPE_3__* tscSqlExprGet (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static int32_t checkUpdateTagPrjFunctions(SSqlCmd* pCmd) {
  const char* msg1 = "only one selectivity function allowed in presence of tags function";
  const char* msg2 = "functions not allowed";

  bool    tagColExists = false;
  int16_t numOfTimestamp = 0;  // primary timestamp column
  int16_t numOfSelectivity = 0;
  int16_t numOfAggregation = 0;

  for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);
    if (pExpr->functionId == TSDB_FUNC_TAGPRJ ||
        (pExpr->functionId == TSDB_FUNC_PRJ && pExpr->colInfo.colId == PRIMARYKEY_TIMESTAMP_COL_INDEX)) {
      tagColExists = true;
      break;
    }
  }

  if (tagColExists) {  // check if the selectivity function exists
    for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
      int16_t functionId = tscSqlExprGet(pCmd, i)->functionId;
      if (functionId == TSDB_FUNC_TAGPRJ || functionId == TSDB_FUNC_PRJ || functionId == TSDB_FUNC_TS) {
        continue;
      }

      if ((aAggs[functionId].nStatus & TSDB_FUNCSTATE_SELECTIVITY) != 0) {
        numOfSelectivity++;
      } else {
        numOfAggregation++;
      }
    }

    // When the tag projection function on tag column that is not in the group by clause, aggregation function and
    // selectivity function exist in select clause is not allowed.
    if (numOfAggregation > 0) {
      setErrMsg(pCmd, msg1);
      return TSDB_CODE_INVALID_SQL;
    }

    /*
     *  if numOfSelectivity equals to 0, it is a super table projection query
     */
    if (numOfSelectivity == 1) {
      doUpdateSqlFunctionForTagPrj(pCmd);
    } else if (numOfSelectivity > 1) {
      /*
       * If more than one selectivity functions exist, all the selectivity functions must be last_row.
       * Otherwise, return with error code.
       */
      for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
        int16_t functionId = tscSqlExprGet(pCmd, i)->functionId;
        if (functionId == TSDB_FUNC_TAGPRJ) {
          continue;
        }

        if (((aAggs[functionId].nStatus & TSDB_FUNCSTATE_SELECTIVITY) != 0) && (functionId != TSDB_FUNC_LAST_ROW)) {
          setErrMsg(pCmd, msg1);
          return TSDB_CODE_INVALID_SQL;
        }
      }

      doUpdateSqlFunctionForTagPrj(pCmd);
    }
  }

  return TSDB_CODE_SUCCESS;
}