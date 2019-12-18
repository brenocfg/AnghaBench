#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  command; } ;
struct TYPE_12__ {void* pTimer; struct TYPE_12__* pHb; struct TYPE_12__* thandle; struct TYPE_12__* signature; struct TYPE_12__* pTscObj; struct TYPE_12__* param; TYPE_9__ cmd; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_1__ SSqlObj ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_DEFAULT_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  TSDB_SQL_HB ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  taosCloseRpcConn (TYPE_1__*) ; 
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 
 scalar_t__ tscAllocPayload (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscCloseTscObj (TYPE_1__*) ; 
 int /*<<< orphan*/  tscFreeSqlObj (TYPE_1__*) ; 
 int /*<<< orphan*/  tscProcessHeartBeatRsp ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_1__*) ; 
 scalar_t__ tscShouldFreeHeatBeat (TYPE_1__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_1__*,TYPE_1__*) ; 

void tscProcessActivityTimer(void *handle, void *tmrId) {
  STscObj *pObj = (STscObj *)handle;

  if (pObj == NULL) return;
  if (pObj->signature != pObj) return;
  if (pObj->pTimer != tmrId) return;

  if (pObj->pHb == NULL) {
    SSqlObj *pSql = (SSqlObj *)calloc(1, sizeof(SSqlObj));
    if (NULL == pSql) return;

    pSql->fp = tscProcessHeartBeatRsp;
    pSql->cmd.command = TSDB_SQL_HB;
    if (TSDB_CODE_SUCCESS != tscAllocPayload(&(pSql->cmd), TSDB_DEFAULT_PAYLOAD_SIZE)) {
      tfree(pSql);
      return;
    }

    pSql->param = pObj;
    pSql->pTscObj = pObj;
    pSql->signature = pSql;
    pObj->pHb = pSql;
    tscTrace("%p pHb is allocated, pObj:%p", pObj->pHb, pObj);
  }

  if (tscShouldFreeHeatBeat(pObj->pHb)) {
    tscTrace("%p free HB object and release connection, pConn:%p", pObj, pObj->pHb->thandle);
    taosCloseRpcConn(pObj->pHb->thandle);

    tscFreeSqlObj(pObj->pHb);
    tscCloseTscObj(pObj);
    return;
  }

  tscProcessSql(pObj->pHb);
}