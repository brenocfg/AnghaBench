#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ command; } ;
struct TYPE_5__ {scalar_t__ qhandle; int code; } ;
struct TYPE_6__ {void (* fp ) () ;int /*<<< orphan*/  fetchFp; TYPE_1__ res; TYPE_3__ cmd; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_SQL_FETCH ; 
 scalar_t__ TSDB_SQL_LOCAL ; 
 scalar_t__ TSDB_SQL_MGMT ; 
 scalar_t__ TSDB_SQL_RETRIEVE ; 
 scalar_t__ TSDB_SQL_RETRIEVE_METRIC ; 
 int /*<<< orphan*/  tscError (char*) ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_2__*) ; 
 int /*<<< orphan*/  tscQueueAsyncError (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void tscProcessAsyncRetrieveImpl(void *param, TAOS_RES *tres, int numOfRows, void (*fp)()) {
  SSqlObj *pSql = (SSqlObj *)tres;
  if (pSql == NULL) {  // error
    tscError("sql object is NULL");
    tscQueueAsyncError(pSql->fetchFp, param);
    return;
  }

  SSqlCmd *pCmd = &pSql->cmd;
  SSqlRes *pRes = &pSql->res;

  if (pRes->qhandle == 0 || numOfRows != 0) {
    if (pRes->qhandle == 0) {
      tscError("qhandle is NULL");
    } else {
      pRes->code = numOfRows;
    }

    tscQueueAsyncError(pSql->fetchFp, param);
    return;
  }

  pSql->fp = fp;
  if (pCmd->command != TSDB_SQL_RETRIEVE_METRIC && pCmd->command < TSDB_SQL_LOCAL) {
    pCmd->command = (pCmd->command > TSDB_SQL_MGMT) ? TSDB_SQL_RETRIEVE : TSDB_SQL_FETCH;
  }
  tscProcessSql(pSql);
}