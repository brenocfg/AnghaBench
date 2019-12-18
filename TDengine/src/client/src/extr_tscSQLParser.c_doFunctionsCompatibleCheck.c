#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_21__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_30__ {scalar_t__ colId; } ;
struct TYPE_29__ {int /*<<< orphan*/  pMeterMeta; } ;
struct TYPE_24__ {scalar_t__ numOfGroupCols; TYPE_8__* columnInfo; } ;
struct TYPE_22__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_28__ {scalar_t__ command; scalar_t__ nAggTimeInterval; TYPE_2__ groupbyExpr; TYPE_1__ fieldsInfo; } ;
struct TYPE_25__ {scalar_t__ colId; scalar_t__ colIdx; } ;
struct TYPE_27__ {scalar_t__ functionId; TYPE_3__ colInfo; } ;
struct TYPE_26__ {TYPE_6__ cmd; } ;
struct TYPE_23__ {int /*<<< orphan*/  nStatus; } ;
typedef  TYPE_4__ SSqlObj ;
typedef  TYPE_5__ SSqlExpr ;
typedef  TYPE_6__ SSqlCmd ;
typedef  int /*<<< orphan*/  SSchema ;
typedef  TYPE_7__ SMeterMetaInfo ;
typedef  TYPE_8__ SColIndexEx ;

/* Variables and functions */
 scalar_t__ IS_MULTIOUTPUT (int /*<<< orphan*/ ) ; 
 scalar_t__ PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_FUNC_BOTTOM ; 
 scalar_t__ TSDB_FUNC_COUNT ; 
 scalar_t__ TSDB_FUNC_PRJ ; 
 scalar_t__ TSDB_FUNC_TAGPRJ ; 
 scalar_t__ TSDB_FUNC_TOP ; 
 scalar_t__ TSDB_SQL_RETRIEVE_TAGS ; 
 scalar_t__ TSDB_TBNAME_COLUMN_INDEX ; 
 TYPE_21__* aAggs ; 
 scalar_t__ allTagPrjInGroupby (TYPE_6__*) ; 
 scalar_t__ checkUpdateTagPrjFunctions (TYPE_6__*) ; 
 scalar_t__ doAddGroupbyColumnsOnDemand (TYPE_6__*) ; 
 scalar_t__ onlyTagPrjFunction (TYPE_6__*) ; 
 int /*<<< orphan*/  setErrMsg (TYPE_6__*,char const*) ; 
 int /*<<< orphan*/ * tsGetSchema (int /*<<< orphan*/ ) ; 
 TYPE_7__* tscGetMeterMetaInfo (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tscProjectionQueryOnMetric (TYPE_6__*) ; 
 TYPE_5__* tscSqlExprGet (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  updateTagPrjFunction (TYPE_6__*) ; 

int32_t doFunctionsCompatibleCheck(SSqlObj* pSql) {
  const char* msg1 = "functions/columns not allowed in group by query";
  const char* msg2 = "interval not allowed in group by normal column";
  const char* msg3 = "group by not allowed on projection query";
  const char* msg4 = "tags retrieve not compatible with group by";
  const char* msg5 = "retrieve tags not compatible with group by or interval query";

  SSqlCmd*        pCmd = &pSql->cmd;
  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  // only retrieve tags, group by is not supportted
  if (pCmd->command == TSDB_SQL_RETRIEVE_TAGS) {
    if (pCmd->groupbyExpr.numOfGroupCols > 0 || pCmd->nAggTimeInterval > 0) {
      setErrMsg(pCmd, msg5);
      return TSDB_CODE_INVALID_SQL;
    } else {
      return TSDB_CODE_SUCCESS;
    }
  }

  if (pCmd->groupbyExpr.numOfGroupCols > 0) {
    SSchema* pSchema = tsGetSchema(pMeterMetaInfo->pMeterMeta);
    int16_t  bytes = 0;
    int16_t  type = 0;
    char*    name = NULL;

    // check if all the tags prj columns belongs to the group by columns
    if (onlyTagPrjFunction(pCmd) && allTagPrjInGroupby(pCmd)) {
      updateTagPrjFunction(pCmd);
      return doAddGroupbyColumnsOnDemand(pCmd);
    }

    // check all query functions in selection clause, multi-output functions are not allowed
    for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
      SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);
      int32_t   functId = pExpr->functionId;

      /*
       * group by normal columns.
       * Check if the column projection is identical to the group by column or not
       */
      if (functId == TSDB_FUNC_PRJ && pExpr->colInfo.colId != PRIMARYKEY_TIMESTAMP_COL_INDEX) {
        bool qualified = false;
        for (int32_t j = 0; j < pCmd->groupbyExpr.numOfGroupCols; ++j) {
          SColIndexEx* pColIndex = &pCmd->groupbyExpr.columnInfo[j];
          if (pColIndex->colId == pExpr->colInfo.colId) {
            qualified = true;
            break;
          }
        }

        if (!qualified) {
          return TSDB_CODE_INVALID_SQL;
        }
      }

      if (IS_MULTIOUTPUT(aAggs[functId].nStatus) && functId != TSDB_FUNC_TOP && functId != TSDB_FUNC_BOTTOM &&
          functId != TSDB_FUNC_TAGPRJ &&
          (functId == TSDB_FUNC_PRJ && pExpr->colInfo.colId != PRIMARYKEY_TIMESTAMP_COL_INDEX)) {
        setErrMsg(pCmd, msg1);
        return TSDB_CODE_INVALID_SQL;
      }

      if (functId == TSDB_FUNC_COUNT && pExpr->colInfo.colIdx == TSDB_TBNAME_COLUMN_INDEX) {
        setErrMsg(pCmd, msg1);
        return TSDB_CODE_INVALID_SQL;
      }
    }

    if (checkUpdateTagPrjFunctions(pCmd) != TSDB_CODE_SUCCESS) {
      return TSDB_CODE_INVALID_SQL;
    }

    /*
     * group by tag function must be not changed the function name, otherwise, the group operation may fail to
     * divide the subset of final result.
     */
    if (doAddGroupbyColumnsOnDemand(pCmd) != TSDB_CODE_SUCCESS) {
      return TSDB_CODE_INVALID_SQL;
    }

    // projection query on metric does not compatible with "group by" syntax
    if (tscProjectionQueryOnMetric(pCmd)) {
      setErrMsg(pCmd, msg3);
      return TSDB_CODE_INVALID_SQL;
    }
  } else {
    return checkUpdateTagPrjFunctions(pCmd);
  }
}