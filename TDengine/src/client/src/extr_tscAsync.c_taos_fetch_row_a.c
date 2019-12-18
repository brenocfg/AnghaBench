#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * msg; int /*<<< orphan*/  thandle; TYPE_2__* ahandle; int /*<<< orphan*/  fp; } ;
struct TYPE_10__ {scalar_t__ command; } ;
struct TYPE_8__ {scalar_t__ qhandle; scalar_t__ row; scalar_t__ numOfRows; int /*<<< orphan*/  tsrow; } ;
struct TYPE_9__ {void (* fetchFp ) (void*,int /*<<< orphan*/ *,TAOS_ROW) ;int /*<<< orphan*/  fp; void* param; TYPE_3__ cmd; TYPE_1__ res; struct TYPE_9__* signature; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;
typedef  TYPE_4__ SSchedMsg ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_DISCONNECTED ; 
 scalar_t__ TSDB_SQL_FETCH ; 
 scalar_t__ TSDB_SQL_MGMT ; 
 scalar_t__ TSDB_SQL_RETRIEVE ; 
 int /*<<< orphan*/  globalCode ; 
 int /*<<< orphan*/  taosScheduleTask (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  tscError (char*) ; 
 int /*<<< orphan*/  tscProcessAsyncRetrieve ; 
 int /*<<< orphan*/  tscProcessFetchRow ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_2__*) ; 
 int /*<<< orphan*/  tscQhandle ; 
 int /*<<< orphan*/  tscQueueAsyncError (void (*) (void*,int /*<<< orphan*/ *,TAOS_ROW),void*) ; 
 int /*<<< orphan*/  tscResetForNextRetrieve (TYPE_1__*) ; 

void taos_fetch_row_a(TAOS_RES *taosa, void (*fp)(void *, TAOS_RES *, TAOS_ROW), void *param) {
  SSqlObj *pSql = (SSqlObj *)taosa;
  if (pSql == NULL || pSql->signature != pSql) {
    tscError("sql object is NULL");
    globalCode = TSDB_CODE_DISCONNECTED;
    tscQueueAsyncError(fp, param);
    return;
  }

  SSqlRes *pRes = &pSql->res;
  SSqlCmd *pCmd = &pSql->cmd;

  if (pRes->qhandle == 0) {
    tscError("qhandle is NULL");
    tscQueueAsyncError(fp, param);
    return;
  }

  pSql->fetchFp = fp;
  pSql->param = param;

  if (pRes->row >= pRes->numOfRows) {
    tscResetForNextRetrieve(pRes);
    pSql->fp = tscProcessAsyncRetrieve;
    pCmd->command = (pCmd->command > TSDB_SQL_MGMT) ? TSDB_SQL_RETRIEVE : TSDB_SQL_FETCH;
    tscProcessSql(pSql);
  } else {
    SSchedMsg schedMsg;
    schedMsg.fp = tscProcessFetchRow;
    schedMsg.ahandle = pSql;
    schedMsg.thandle = pRes->tsrow;
    schedMsg.msg = NULL;
    taosScheduleTask(tscQhandle, &schedMsg);
  }
}