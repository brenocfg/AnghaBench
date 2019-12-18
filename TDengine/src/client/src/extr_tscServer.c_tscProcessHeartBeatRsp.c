#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int numOfIps; int /*<<< orphan*/ * ip; int /*<<< orphan*/ * ipstr; } ;
struct TYPE_16__ {int numOfIps; int /*<<< orphan*/ * ip; } ;
struct TYPE_17__ {scalar_t__ streamId; scalar_t__ queryId; scalar_t__ killConnection; TYPE_4__ ipList; } ;
struct TYPE_14__ {scalar_t__ pRsp; } ;
struct TYPE_15__ {TYPE_2__ res; } ;
struct TYPE_13__ {int /*<<< orphan*/  pTimer; TYPE_3__* pHb; struct TYPE_13__* signature; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlRes ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SIpList ;
typedef  TYPE_5__ SHeartBeatRsp ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tinet_ntoa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tsShellActivityTimer ; 
 int /*<<< orphan*/  tscError (char*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  tscKillConnection (TYPE_1__*) ; 
 int /*<<< orphan*/  tscKillQuery (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  tscKillStream (TYPE_1__*,scalar_t__) ; 
 TYPE_6__ tscMgmtIpList ; 
 int /*<<< orphan*/  tscPrintMgmtIp () ; 
 int /*<<< orphan*/  tscProcessActivityTimer ; 
 int /*<<< orphan*/  tscTmr ; 
 int /*<<< orphan*/  tscTrace (char*,...) ; 

void tscProcessHeartBeatRsp(void *param, TAOS_RES *tres, int code) {
  STscObj *pObj = (STscObj *)param;
  if (pObj == NULL) return;
  if (pObj != pObj->signature) {
    tscError("heart beat msg, pObj:%p, signature:%p invalid", pObj, pObj->signature);
    return;
  }

  SSqlObj *pSql = pObj->pHb;
  SSqlRes *pRes = &pSql->res;

  if (code == 0) {
    SHeartBeatRsp *pRsp = (SHeartBeatRsp *)pRes->pRsp;
#ifdef CLUSTER
    SIpList *      pIpList = &pRsp->ipList;
    tscMgmtIpList.numOfIps = pIpList->numOfIps;
    if (memcmp(tscMgmtIpList.ip, pIpList->ip, pIpList->numOfIps * 4) != 0) {
      for (int i = 0; i < pIpList->numOfIps; ++i) {
        tinet_ntoa(tscMgmtIpList.ipstr[i], pIpList->ip[i]);
        tscMgmtIpList.ip[i] = pIpList->ip[i];
      }
      tscTrace("new mgmt IP list:");
      tscPrintMgmtIp();
    }
#endif
    if (pRsp->killConnection) {
      tscKillConnection(pObj);
    } else {
      if (pRsp->queryId) tscKillQuery(pObj, pRsp->queryId);
      if (pRsp->streamId) tscKillStream(pObj, pRsp->streamId);
    }
  } else {
    tscTrace("heart beat failed, code:%d", code);
  }

  taosTmrReset(tscProcessActivityTimer, tsShellActivityTimer * 500, pObj, tscTmr, &pObj->pTimer);
}