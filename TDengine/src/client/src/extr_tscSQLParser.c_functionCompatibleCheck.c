#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_17__ {scalar_t__ numOfGroupCols; TYPE_3__* columnInfo; } ;
struct TYPE_14__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_20__ {int type; TYPE_4__ groupbyExpr; TYPE_1__ fieldsInfo; } ;
struct TYPE_15__ {scalar_t__ colId; } ;
struct TYPE_19__ {scalar_t__ functionId; int numOfParams; TYPE_5__* param; TYPE_2__ colInfo; } ;
struct TYPE_18__ {int i64Key; } ;
struct TYPE_16__ {scalar_t__ colId; } ;
struct TYPE_13__ {int nStatus; } ;
typedef  TYPE_6__ SSqlExpr ;
typedef  TYPE_7__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 int TSDB_FUNCSTATE_SELECTIVITY ; 
 scalar_t__ TSDB_FUNC_ARITHM ; 
 scalar_t__ TSDB_FUNC_PRJ ; 
 scalar_t__ TSDB_FUNC_TAG ; 
 scalar_t__ TSDB_FUNC_TAGPRJ ; 
 scalar_t__ TSDB_FUNC_TS ; 
 scalar_t__ TSDB_FUNC_TS_DUMMY ; 
 int TSDB_QUERY_TYPE_PROJECTION_QUERY ; 
 TYPE_12__* aAggs ; 
 scalar_t__* funcCompatDefList ; 
 int /*<<< orphan*/  setErrMsg (TYPE_7__*,char const*) ; 
 TYPE_6__* tscSqlExprGet (TYPE_7__*,scalar_t__) ; 

__attribute__((used)) static bool functionCompatibleCheck(SSqlCmd* pCmd) {
  const char* msg1 = "column on select clause not allowed";

  int32_t startIdx = 0;
  int32_t functionID = tscSqlExprGet(pCmd, startIdx)->functionId;

  // ts function can be simultaneously used with any other functions.
  if (functionID == TSDB_FUNC_TS || functionID == TSDB_FUNC_TS_DUMMY) {
    startIdx++;
  }

  int32_t factor = funcCompatDefList[tscSqlExprGet(pCmd, startIdx)->functionId];

  // diff function cannot be executed with other function
  // arithmetic function can be executed with other arithmetic functions
  for (int32_t i = startIdx + 1; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);

    int16_t functionId = pExpr->functionId;
    if (functionId == TSDB_FUNC_TAGPRJ || functionId == TSDB_FUNC_TAG || functionId == TSDB_FUNC_TS) {
      continue;
    }

    if (functionId == TSDB_FUNC_PRJ && pExpr->colInfo.colId == PRIMARYKEY_TIMESTAMP_COL_INDEX) {
      continue;
    }

    if (funcCompatDefList[functionId] != factor) {
      return false;
    }
  }

  // additional check for select aggfuntion(column), column1 from table_name group by(column1);
  if ((pCmd->type & TSDB_QUERY_TYPE_PROJECTION_QUERY) == TSDB_QUERY_TYPE_PROJECTION_QUERY) {
    bool isAggFunc = false;
    for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
      int16_t functionId = tscSqlExprGet(pCmd, i)->functionId;

      if (functionId == TSDB_FUNC_PRJ || functionId == TSDB_FUNC_TAGPRJ || functionId == TSDB_FUNC_TS ||
          functionId == TSDB_FUNC_ARITHM) {
        continue;
      }

      if ((aAggs[functionId].nStatus & TSDB_FUNCSTATE_SELECTIVITY) == 0) {
        isAggFunc = true;
        break;
      }
    }

    // TODO change the type, the type is not correct
    if (isAggFunc) {
      pCmd->type &= (~TSDB_QUERY_TYPE_PROJECTION_QUERY);

      // agg function mixed up with project query without group by exists
      if (pCmd->groupbyExpr.numOfGroupCols == 0) {
        return false;
      }

      // get the project column
      int32_t numOfPrjColumn = 0;
      for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
        SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);
        if (pExpr->functionId == TSDB_FUNC_PRJ) {
          numOfPrjColumn += 1;

          bool qualifiedCol = false;
          for (int32_t j = 0; j < pCmd->groupbyExpr.numOfGroupCols; ++j) {
            if (pExpr->colInfo.colId == pCmd->groupbyExpr.columnInfo[j].colId) {
              qualifiedCol = true;

              pExpr->param[0].i64Key = 1;  // limit the output to be 1 for each state value
              pExpr->numOfParams = 1;
              break;
            }
          }

          if (!qualifiedCol) {
            setErrMsg(pCmd, msg1);
            return false;
          }
        }
      }
    }
  }

  return true;
}