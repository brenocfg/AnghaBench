#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ const int64_t ;
struct TYPE_8__ {scalar_t__ command; } ;
struct TYPE_6__ {int /*<<< orphan*/  code; } ;
struct TYPE_7__ {int numOfSubs; TYPE_5__ cmd; int /*<<< orphan*/ * thandle; struct TYPE_7__** pSubs; TYPE_1__ res; } ;
typedef  TYPE_2__ SSqlObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_QUERY_CANCELLED ; 
 scalar_t__ TSDB_SQL_RETRIEVE_EMPTY_RESULT ; 
 scalar_t__ TSDB_SQL_RETRIEVE_METRIC ; 
 scalar_t__ const taosGetTimestampMs () ; 
 int /*<<< orphan*/  taosMsleep (int) ; 
 int /*<<< orphan*/  taosStopRpcConn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscIsTwoStageMergeMetricQuery (TYPE_5__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_2__*) ; 

void tscKillMetricQuery(SSqlObj *pSql) {
  if (!tscIsTwoStageMergeMetricQuery(&pSql->cmd)) {
    return;
  }

  for (int i = 0; i < pSql->numOfSubs; ++i) {
    SSqlObj *pSub = pSql->pSubs[i];

    if (pSub == NULL || pSub->thandle == NULL) {
      continue;
    }

    /*
     * here, we cannot set the command = TSDB_SQL_KILL_QUERY. Otherwise, it may cause
     * sub-queries not correctly released and master sql object of metric query reaches an abnormal state.
     */
    pSql->pSubs[i]->res.code = TSDB_CODE_QUERY_CANCELLED;
    taosStopRpcConn(pSql->pSubs[i]->thandle);
  }

  pSql->numOfSubs = 0;

  /*
   * 1. if the subqueries are not launched or partially launched, we need to waiting the launched
   * query return to successfully free allocated resources.
   * 2. if no any subqueries are launched yet, which means the metric query only in parse sql stage,
   * set the res.code, and return.
   */
  const int64_t MAX_WAITING_TIME = 10000;  // 10 Sec.
  int64_t       stime = taosGetTimestampMs();

  while (pSql->cmd.command != TSDB_SQL_RETRIEVE_METRIC && pSql->cmd.command != TSDB_SQL_RETRIEVE_EMPTY_RESULT) {
    taosMsleep(100);
    if (taosGetTimestampMs() - stime > MAX_WAITING_TIME) {
      break;
    }
  }

  tscTrace("%p metric query is cancelled", pSql);
}