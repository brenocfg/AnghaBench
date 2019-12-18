#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ command; } ;
struct TYPE_5__ {int /*<<< orphan*/  code; } ;
struct TYPE_6__ {int /*<<< orphan*/ * thandle; TYPE_4__ cmd; TYPE_1__ res; struct TYPE_6__* signature; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_2__ SSqlObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_QUERY_CANCELLED ; 
 scalar_t__ TSDB_SQL_LOCAL ; 
 int /*<<< orphan*/  taosStopRpcConn (int /*<<< orphan*/ *) ; 
 scalar_t__ tscIsTwoStageMergeMetricQuery (TYPE_4__*) ; 
 int /*<<< orphan*/  tscKillMetricQuery (TYPE_2__*) ; 
 int /*<<< orphan*/  tscTrace (char*,int /*<<< orphan*/ *) ; 

void taos_stop_query(TAOS_RES *res) {
  if (res == NULL) return;

  SSqlObj *pSql = (SSqlObj *)res;
  if (pSql->signature != pSql) return;
  tscTrace("%p start to cancel query", res);

  pSql->res.code = TSDB_CODE_QUERY_CANCELLED;

  if (tscIsTwoStageMergeMetricQuery(&pSql->cmd)) {
    tscKillMetricQuery(pSql);
    return;
  }

  if (pSql->cmd.command >= TSDB_SQL_LOCAL) {
    return;
  }

  if (pSql->thandle == NULL) {
    tscTrace("%p no connection, abort cancel", res);
    return;
  }

  taosStopRpcConn(pSql->thandle);
  tscTrace("%p query is cancelled", res);
}