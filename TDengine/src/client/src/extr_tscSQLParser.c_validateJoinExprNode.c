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

/* Type definitions */
struct TYPE_12__ {scalar_t__ nSQLOptr; int /*<<< orphan*/  colInfo; struct TYPE_12__* pRight; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  scalar_t__ int16_t ;
struct TYPE_15__ {scalar_t__ tableIndex; size_t columnIndex; } ;
struct TYPE_14__ {int /*<<< orphan*/  pMeterMeta; } ;
struct TYPE_13__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_2__ SSchema ;
typedef  TYPE_3__ SMeterMetaInfo ;
typedef  TYPE_4__ SColumnIndex ;

/* Variables and functions */
 TYPE_4__ COLUMN_INDEX_INITIALIZER ; 
 scalar_t__ TK_EQ ; 
 scalar_t__ TK_ID ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 scalar_t__ TSDB_DATA_TYPE_NCHAR ; 
 scalar_t__ UTIL_METER_IS_METRIC (TYPE_3__*) ; 
 scalar_t__ getColumnIndexByNameEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  setErrMsg (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* tsGetSchema (int /*<<< orphan*/ ) ; 
 TYPE_3__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static bool validateJoinExprNode(SSqlCmd* pCmd, tSQLExpr* pExpr, SColumnIndex* pLeftIndex) {
  const char* msg1 = "illegal column name";
  const char* msg2 = "= is expected in join expression";
  const char* msg3 = "join column must have same type";
  const char* msg4 = "self join is not allowed";
  const char* msg5 = "join table must be the same type(table to table, super table to super table)";
  const char* msg6 = "tags in join condition not support binary/nchar types";

  tSQLExpr* pRight = pExpr->pRight;

  if (pRight->nSQLOptr != TK_ID) {
    return true;
  }

  if (pExpr->nSQLOptr != TK_EQ) {
    setErrMsg(pCmd, msg2);
    return false;
  }

  SColumnIndex rightIndex = COLUMN_INDEX_INITIALIZER;

  if (getColumnIndexByNameEx(&pRight->colInfo, pCmd, &rightIndex) != TSDB_CODE_SUCCESS) {
    setErrMsg(pCmd, msg1);
    return false;
  }

  // todo extract function
  SMeterMetaInfo* pLeftMeterMeta = tscGetMeterMetaInfo(pCmd, pLeftIndex->tableIndex);
  SSchema*        pLeftSchema = tsGetSchema(pLeftMeterMeta->pMeterMeta);
  int16_t         leftType = pLeftSchema[pLeftIndex->columnIndex].type;

  SMeterMetaInfo* pRightMeterMeta = tscGetMeterMetaInfo(pCmd, rightIndex.tableIndex);
  SSchema*        pRightSchema = tsGetSchema(pRightMeterMeta->pMeterMeta);
  int16_t         rightType = pRightSchema[rightIndex.columnIndex].type;

  if (leftType != rightType) {
    setErrMsg(pCmd, msg3);
    return false;
  } else if (pLeftIndex->tableIndex == rightIndex.tableIndex) {
    setErrMsg(pCmd, msg4);
    return false;
  } else if (leftType == TSDB_DATA_TYPE_BINARY || leftType == TSDB_DATA_TYPE_NCHAR) {
    setErrMsg(pCmd, msg6);
    return false;
  }

  // table to table/ super table to super table are allowed
  if (UTIL_METER_IS_METRIC(pLeftMeterMeta) != UTIL_METER_IS_METRIC(pRightMeterMeta)) {
    setErrMsg(pCmd, msg5);
    return false;
  }

  return true;
}