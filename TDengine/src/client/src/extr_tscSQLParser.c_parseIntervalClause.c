#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_31__ {scalar_t__ member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_30__ {TYPE_3__* pMeterMeta; } ;
struct TYPE_28__ {scalar_t__ type; int n; int /*<<< orphan*/ * z; } ;
struct TYPE_29__ {TYPE_6__ interval; } ;
struct TYPE_22__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_27__ {int nAggTimeInterval; scalar_t__ numOfTables; TYPE_1__ fieldsInfo; int /*<<< orphan*/  intervalTimeUnit; } ;
struct TYPE_24__ {int /*<<< orphan*/  flag; } ;
struct TYPE_26__ {scalar_t__ functionId; scalar_t__ uid; TYPE_2__ colInfo; } ;
struct TYPE_25__ {scalar_t__ precision; scalar_t__ uid; } ;
struct TYPE_23__ {int /*<<< orphan*/  aName; } ;
typedef  TYPE_4__ SSqlExpr ;
typedef  TYPE_5__ SSqlCmd ;
typedef  TYPE_6__ SSQLToken ;
typedef  TYPE_7__ SQuerySQL ;
typedef  TYPE_8__ SMeterMetaInfo ;
typedef  int /*<<< orphan*/  SColumnList ;
typedef  TYPE_9__ SColumnIndex ;

/* Variables and functions */
 scalar_t__ COLUMN_INDEX_INITIAL_VAL ; 
 int /*<<< orphan*/  PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_COL_IS_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_TIMESTAMP ; 
 scalar_t__ TSDB_FUNC_COUNT ; 
 size_t TSDB_FUNC_TS ; 
 int /*<<< orphan*/  TSDB_KEYSIZE ; 
 scalar_t__ TSDB_TIME_PRECISION_MILLI ; 
 TYPE_21__* aAggs ; 
 int /*<<< orphan*/  getColumnList (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getTimestampInUsFromStr (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ insertResultField (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isTopBottomQuery (TYPE_5__*) ; 
 int /*<<< orphan*/  setErrMsg (TYPE_5__*,char const*) ; 
 int tsMinIntervalTime ; 
 TYPE_8__* tscGetMeterMetaInfo (TYPE_5__*,scalar_t__) ; 
 TYPE_4__* tscSqlExprGet (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  tscSqlExprInsert (TYPE_5__*,int /*<<< orphan*/ ,size_t,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t parseIntervalClause(SSqlCmd* pCmd, SQuerySQL* pQuerySql) {
  const char* msg1 = "invalid query expression";
  const char* msg2 = "interval cannot be less than 10 ms";

  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  if (pQuerySql->interval.type == 0) {
    return TSDB_CODE_SUCCESS;
  }

  // interval is not null
  SSQLToken* t = &pQuerySql->interval;
  if (getTimestampInUsFromStr(t->z, t->n, &pCmd->nAggTimeInterval) != TSDB_CODE_SUCCESS) {
    return TSDB_CODE_INVALID_SQL;
  }

  /* revised the time precision according to the flag */
  if (pMeterMetaInfo->pMeterMeta->precision == TSDB_TIME_PRECISION_MILLI) {
    pCmd->nAggTimeInterval = pCmd->nAggTimeInterval / 1000;
  }

  /* parser has filter the illegal type, no need to check here */
  pCmd->intervalTimeUnit = pQuerySql->interval.z[pQuerySql->interval.n - 1];

  // interval cannot be less than 10 milliseconds
  if (pCmd->nAggTimeInterval < tsMinIntervalTime) {
    setErrMsg(pCmd, msg2);
    return TSDB_CODE_INVALID_SQL;
  }

  // for top/bottom + interval query, we do not add additional timestamp column in the front
  if (isTopBottomQuery(pCmd)) {
    return TSDB_CODE_SUCCESS;
  }

  // check the invalid sql expresssion: select count(tbname)/count(tag1)/count(tag2) from super_table interval(1d);
  for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);
    if (pExpr->functionId == TSDB_FUNC_COUNT && TSDB_COL_IS_TAG(pExpr->colInfo.flag)) {
      setErrMsg(pCmd, msg1);
      return TSDB_CODE_INVALID_SQL;
    }
  }

  // need to add timestamp column in result set, if interval is existed
  uint64_t uid = tscSqlExprGet(pCmd, 0)->uid;

  int32_t tableIndex = COLUMN_INDEX_INITIAL_VAL;
  for (int32_t i = 0; i < pCmd->numOfTables; ++i) {
    pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, i);
    if (pMeterMetaInfo->pMeterMeta->uid == uid) {
      tableIndex = i;
      break;
    }
  }

  if (tableIndex == COLUMN_INDEX_INITIAL_VAL) {
    return TSDB_CODE_INVALID_SQL;
  }

  SColumnIndex index = {tableIndex, PRIMARYKEY_TIMESTAMP_COL_INDEX};
  tscSqlExprInsert(pCmd, 0, TSDB_FUNC_TS, &index, TSDB_DATA_TYPE_TIMESTAMP, TSDB_KEYSIZE, TSDB_KEYSIZE);

  SColumnList ids = getColumnList(1, 0, PRIMARYKEY_TIMESTAMP_COL_INDEX);
  int32_t     ret = insertResultField(pCmd, 0, &ids, TSDB_KEYSIZE, TSDB_DATA_TYPE_TIMESTAMP, aAggs[TSDB_FUNC_TS].aName);

  return ret;
}