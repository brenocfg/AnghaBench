#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_23__ {int /*<<< orphan*/  name; } ;
struct TYPE_22__ {scalar_t__ ahandle; } ;
struct TYPE_19__ {int code; } ;
struct TYPE_21__ {int /*<<< orphan*/  cmd; TYPE_1__ res; TYPE_2__* param; int /*<<< orphan*/  fp; } ;
struct TYPE_20__ {TYPE_3__* pSql; int /*<<< orphan*/  precision; int /*<<< orphan*/  slidingTime; } ;
typedef  TYPE_2__ SSqlStream ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SSchedMsg ;
typedef  TYPE_5__ SMeterMetaInfo ;

/* Variables and functions */
 int TSDB_CODE_ACTION_IN_PROGRESS ; 
 int TSDB_CODE_SUCCESS ; 
 scalar_t__ UTIL_METER_IS_METRIC (TYPE_5__*) ; 
 int /*<<< orphan*/  tscError (char*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int tscGetMeterMeta (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tscGetMetricMeta (TYPE_3__*) ; 
 int /*<<< orphan*/  tscGetRetryDelayTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscIncStreamExecutionCount (TYPE_2__*) ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_3__*) ; 
 int /*<<< orphan*/  tscProcessStreamQueryCallback ; 
 int /*<<< orphan*/  tscSetRetryTimer (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscTansformSQLFunctionForMetricQuery (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tscProcessStreamLaunchQuery(SSchedMsg *pMsg) {
  SSqlStream *pStream = (SSqlStream *)pMsg->ahandle;
  SSqlObj *   pSql = pStream->pSql;

  pSql->fp = tscProcessStreamQueryCallback;
  pSql->param = pStream;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(&pSql->cmd, 0);

  int code = tscGetMeterMeta(pSql, pMeterMetaInfo->name, 0);
  pSql->res.code = code;

  if (code == TSDB_CODE_ACTION_IN_PROGRESS) return;

  if (code == 0 && UTIL_METER_IS_METRIC(pMeterMetaInfo)) {
    code = tscGetMetricMeta(pSql);
    pSql->res.code = code;

    if (code == TSDB_CODE_ACTION_IN_PROGRESS) return;
  }

  tscTansformSQLFunctionForMetricQuery(&pSql->cmd);

  // failed to get meter/metric meta, retry in 10sec.
  if (code != TSDB_CODE_SUCCESS) {
    int64_t retryDelayTime = tscGetRetryDelayTime(pStream->slidingTime, pStream->precision);
    tscError("%p stream:%p,get metermeta failed, retry in %lldms", pStream->pSql, pStream, retryDelayTime);

    tscSetRetryTimer(pStream, pSql, retryDelayTime);
    return;
  }

  tscTrace("%p stream:%p start stream query on:%s", pSql, pStream, pMeterMetaInfo->name);
  tscProcessSql(pStream->pSql);

  tscIncStreamExecutionCount(pStream);
}