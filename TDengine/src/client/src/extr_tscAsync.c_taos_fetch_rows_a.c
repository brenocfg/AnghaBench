#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ command; } ;
struct TYPE_6__ {scalar_t__ qhandle; } ;
struct TYPE_7__ {void (* fetchFp ) (void*,int /*<<< orphan*/ *,int) ;void* param; int /*<<< orphan*/  fp; TYPE_3__ cmd; TYPE_1__ res; struct TYPE_7__* signature; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_DISCONNECTED ; 
 scalar_t__ TSDB_SQL_FETCH ; 
 scalar_t__ TSDB_SQL_LOCAL ; 
 scalar_t__ TSDB_SQL_MGMT ; 
 scalar_t__ TSDB_SQL_RETRIEVE ; 
 scalar_t__ TSDB_SQL_RETRIEVE_METRIC ; 
 int /*<<< orphan*/  globalCode ; 
 int /*<<< orphan*/  tscError (char*) ; 
 int /*<<< orphan*/  tscProcessAsyncFetchRowsProxy ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_2__*) ; 
 int /*<<< orphan*/  tscQueueAsyncError (void (*) (void*,int /*<<< orphan*/ *,int),void*) ; 
 int /*<<< orphan*/  tscResetForNextRetrieve (TYPE_1__*) ; 

void taos_fetch_rows_a(TAOS_RES *taosa, void (*fp)(void *, TAOS_RES *, int), void *param) {
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

  // user-defined callback function is stored in fetchFp
  pSql->fetchFp = fp;
  pSql->fp = tscProcessAsyncFetchRowsProxy;

  pSql->param = param;
  tscResetForNextRetrieve(pRes);

  if (pCmd->command != TSDB_SQL_RETRIEVE_METRIC && pCmd->command < TSDB_SQL_LOCAL) {
    pCmd->command = (pCmd->command > TSDB_SQL_MGMT) ? TSDB_SQL_RETRIEVE : TSDB_SQL_FETCH;
  }

  tscProcessSql(pSql);
}