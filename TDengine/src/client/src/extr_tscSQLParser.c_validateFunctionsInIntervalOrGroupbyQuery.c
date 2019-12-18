#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_14__ {int nStatus; } ;
struct TYPE_11__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_13__ {TYPE_2__ fieldsInfo; } ;
struct TYPE_10__ {scalar_t__ colId; } ;
struct TYPE_12__ {scalar_t__ functionId; TYPE_1__ colInfo; } ;
typedef  TYPE_3__ SSqlExpr ;
typedef  TYPE_4__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int TSDB_FUNCSTATE_SELECTIVITY ; 
 scalar_t__ TSDB_FUNC_ARITHM ; 
 scalar_t__ TSDB_FUNC_DIFF ; 
 scalar_t__ TSDB_FUNC_PRJ ; 
 TYPE_9__* aAggs ; 
 int /*<<< orphan*/  setErrMsg (TYPE_4__*,char const*) ; 
 TYPE_3__* tscSqlExprGet (TYPE_4__*,scalar_t__) ; 

int32_t validateFunctionsInIntervalOrGroupbyQuery(SSqlCmd* pCmd) {
  bool        isProjectionFunction = false;
  const char* msg1 = "column projection is not compatible with interval";
  const char* msg2 = "interval not allowed for tag queries";
  
  // multi-output set/ todo refactor
  for (int32_t k = 0; k < pCmd->fieldsInfo.numOfOutputCols; ++k) {
    SSqlExpr* pExpr = tscSqlExprGet(pCmd, k);
    
    // projection query on primary timestamp, the selectivity function needs to be present.
    if (pExpr->functionId == TSDB_FUNC_PRJ && pExpr->colInfo.colId == PRIMARYKEY_TIMESTAMP_COL_INDEX) {
      bool hasSelectivity = false;
      for(int32_t j = 0; j < pCmd->fieldsInfo.numOfOutputCols; ++j) {
        SSqlExpr* pEx = tscSqlExprGet(pCmd, j);
        if ((aAggs[pEx->functionId].nStatus & TSDB_FUNCSTATE_SELECTIVITY) == TSDB_FUNCSTATE_SELECTIVITY) {
          hasSelectivity = true;
          break;
        }
      }
      
      if (hasSelectivity) {
        continue;
      }
    }
    
    if (pExpr->functionId == TSDB_FUNC_PRJ || pExpr->functionId == TSDB_FUNC_DIFF ||
       pExpr->functionId == TSDB_FUNC_ARITHM) {
      isProjectionFunction = true;
    }
  }

  if (isProjectionFunction) {
    setErrMsg(pCmd, msg1);
  }

  return isProjectionFunction == true ? TSDB_CODE_INVALID_SQL : TSDB_CODE_SUCCESS;
}