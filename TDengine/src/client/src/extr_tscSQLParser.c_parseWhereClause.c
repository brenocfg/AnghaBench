#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/ * pRight; int /*<<< orphan*/ * pLeft; } ;
typedef  TYPE_5__ tSQLExpr ;
typedef  scalar_t__ int32_t ;
struct TYPE_33__ {TYPE_3__* pJoinExpr; int /*<<< orphan*/  member_0; } ;
struct TYPE_32__ {TYPE_4__* pMeterMeta; } ;
struct TYPE_31__ {int /*<<< orphan*/  type; int /*<<< orphan*/  etime; scalar_t__ stime; } ;
struct TYPE_30__ {TYPE_7__ cmd; } ;
struct TYPE_28__ {scalar_t__ numOfColumns; } ;
struct TYPE_27__ {TYPE_2__* pRight; TYPE_1__* pLeft; } ;
struct TYPE_26__ {int /*<<< orphan*/  colInfo; } ;
struct TYPE_25__ {int /*<<< orphan*/  colInfo; } ;
struct TYPE_24__ {scalar_t__ columnIndex; int /*<<< orphan*/  tableIndex; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ SSqlObj ;
typedef  TYPE_7__ SSqlCmd ;
typedef  TYPE_8__ SMeterMetaInfo ;
typedef  TYPE_9__ SCondExpr ;
typedef  TYPE_10__ SColumnIndex ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MAX ; 
 scalar_t__ QUERY_IS_JOIN_QUERY (int /*<<< orphan*/ ) ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ UTIL_METER_IS_METRIC (TYPE_8__*) ; 
 int /*<<< orphan*/  addRequiredTagColumn (TYPE_7__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanQueryExpr (TYPE_9__*) ; 
 scalar_t__ doParseWhereClause (TYPE_6__*,TYPE_5__**,TYPE_9__*) ; 
 int /*<<< orphan*/  getColumnIndexByNameEx (int /*<<< orphan*/ *,TYPE_7__*,TYPE_10__*) ; 
 int /*<<< orphan*/  setErrMsg (TYPE_7__*,char const*) ; 
 TYPE_8__* tscGetMeterMetaInfo (TYPE_7__*,int /*<<< orphan*/ ) ; 

int32_t parseWhereClause(SSqlObj* pSql, tSQLExpr** pExpr) {
  SSqlCmd* pCmd = &pSql->cmd;

  if (pExpr == NULL) {
    return TSDB_CODE_SUCCESS;
  }

  pCmd->stime = 0;
  pCmd->etime = INT64_MAX;

  int32_t ret = TSDB_CODE_SUCCESS;

  const char* msg1 = "invalid expression";
  SCondExpr   condExpr = {0};

  if ((*pExpr)->pLeft == NULL || (*pExpr)->pRight == NULL) {
    setErrMsg(pCmd, msg1);
    return TSDB_CODE_INVALID_SQL;
  }

  ret = doParseWhereClause(pSql, pExpr, &condExpr);
  if (ret != TSDB_CODE_SUCCESS) {
    return ret;
  }

  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);
  if (QUERY_IS_JOIN_QUERY(pCmd->type) && UTIL_METER_IS_METRIC(pMeterMetaInfo)) {
    SColumnIndex index = {0};

    getColumnIndexByNameEx(&condExpr.pJoinExpr->pLeft->colInfo, pCmd, &index);
    pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, index.tableIndex);

    int32_t columnInfo = index.columnIndex - pMeterMetaInfo->pMeterMeta->numOfColumns;
    addRequiredTagColumn(pCmd, columnInfo, index.tableIndex);

    getColumnIndexByNameEx(&condExpr.pJoinExpr->pRight->colInfo, pCmd, &index);
    pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, index.tableIndex);

    columnInfo = index.columnIndex - pMeterMetaInfo->pMeterMeta->numOfColumns;
    addRequiredTagColumn(pCmd, columnInfo, index.tableIndex);
  }

  cleanQueryExpr(&condExpr);
  return ret;
}