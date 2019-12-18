#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_32__ {scalar_t__ numOfMeters; } ;
struct TYPE_25__ {scalar_t__ offset; int limit; } ;
struct TYPE_24__ {scalar_t__ offset; scalar_t__ limit; } ;
struct TYPE_31__ {TYPE_2__ slimit; TYPE_1__ limit; } ;
struct TYPE_26__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_30__ {scalar_t__ globalLimit; TYPE_3__ fieldsInfo; TYPE_2__ slimit; TYPE_1__ limit; void* command; } ;
struct TYPE_27__ {scalar_t__ colIdx; } ;
struct TYPE_29__ {TYPE_4__ colInfo; } ;
struct TYPE_28__ {TYPE_7__ cmd; } ;
struct TYPE_23__ {int /*<<< orphan*/ * pMeterMeta; TYPE_9__* pMetricMeta; } ;
typedef  TYPE_5__ SSqlObj ;
typedef  TYPE_6__ SSqlExpr ;
typedef  TYPE_7__ SSqlCmd ;
typedef  TYPE_8__ SQuerySQL ;
typedef  TYPE_9__ SMetricMeta ;
typedef  TYPE_10__ SMeterMetaInfo ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 void* TSDB_SQL_RETRIEVE_EMPTY_RESULT ; 
 void* TSDB_SQL_RETRIEVE_TAGS ; 
 scalar_t__ TSDB_TBNAME_COLUMN_INDEX ; 
 scalar_t__ UTIL_METER_IS_METRIC (TYPE_10__*) ; 
 int /*<<< orphan*/  setErrMsg (TYPE_7__*,char const*) ; 
 TYPE_10__* tscGetMeterMetaInfo (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tscGetMetricMeta (TYPE_5__*) ; 
 scalar_t__ tscProjectionQueryOnMetric (TYPE_7__*) ; 
 scalar_t__ tscQueryOnlyMetricTags (TYPE_7__*,int*) ; 
 TYPE_6__* tscSqlExprGet (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_5__*) ; 

int32_t parseLimitClause(SSqlObj* pSql, SQuerySQL* pQuerySql) {
  SSqlCmd*        pCmd = &pSql->cmd;
  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  const char* msg0 = "soffset/offset can not be less than 0";
  const char* msg1 = "slimit/soffset only available for STable query";
  const char* msg2 = "function not supported on table";
  const char* msg3 = "slimit/soffset can not apply to projection query";

  // handle the limit offset value, validate the limit
  pCmd->limit = pQuerySql->limit;
  pCmd->slimit = pQuerySql->slimit;

  if (pCmd->slimit.offset < 0 || pCmd->limit.offset < 0) {
    setErrMsg(pCmd, msg0);
    return TSDB_CODE_INVALID_SQL;
  }

  if (pCmd->limit.limit == 0) {
    tscTrace("%p limit 0, no output result", pSql);
    pCmd->command = TSDB_SQL_RETRIEVE_EMPTY_RESULT;
  }

  if (UTIL_METER_IS_METRIC(pMeterMetaInfo)) {
    bool    queryOnTags = false;
    if (tscQueryOnlyMetricTags(pCmd, &queryOnTags) != TSDB_CODE_SUCCESS) {
      return TSDB_CODE_INVALID_SQL;
    }

    if (queryOnTags == true) {  // local handle the metric tag query
      pCmd->command = TSDB_SQL_RETRIEVE_TAGS;
    } else {
      if (tscProjectionQueryOnMetric(pCmd) && (pCmd->slimit.limit > 0 || pCmd->slimit.offset > 0)) {
        setErrMsg(pCmd, msg3);
        return TSDB_CODE_INVALID_SQL;
      }
    }

    if (pCmd->slimit.limit == 0) {
      tscTrace("%p limit 0, no output result", pSql);
      pCmd->command = TSDB_SQL_RETRIEVE_EMPTY_RESULT;
      return TSDB_CODE_SUCCESS;
    }

    /*
     * get the distribution of all tables among available virtual nodes that satisfy query condition and
     * created according to this super table from management node.
     * And then launching multiple async-queries on required virtual nodes, which is the first-stage query operation.
     */
    int32_t code = tscGetMetricMeta(pSql);
    if (code != TSDB_CODE_SUCCESS) {
      return code;
    }

    // No tables included. No results generated. Query results are empty.
    SMetricMeta* pMetricMeta = pMeterMetaInfo->pMetricMeta;
    if (pMeterMetaInfo->pMeterMeta == NULL || pMetricMeta == NULL || pMetricMeta->numOfMeters == 0) {
      tscTrace("%p no table in metricmeta, no output result", pSql);
      pCmd->command = TSDB_SQL_RETRIEVE_EMPTY_RESULT;
    }

    // keep original limitation value in globalLimit
    pCmd->globalLimit = pCmd->limit.limit;
  } else {
    if (pCmd->slimit.limit != -1 || pCmd->slimit.offset != 0) {
      setErrMsg(pCmd, msg1);
      return TSDB_CODE_INVALID_SQL;
    }

    // filter the query functions operating on "tbname" column that are not supported by normal columns.
    for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
      SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);
      if (pExpr->colInfo.colIdx == TSDB_TBNAME_COLUMN_INDEX) {
        setErrMsg(pCmd, msg2);
        return TSDB_CODE_INVALID_SQL;
      }
    }
  }

  return TSDB_CODE_SUCCESS;
}