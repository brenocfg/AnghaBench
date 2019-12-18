#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_14__ {int numOfIps; int /*<<< orphan*/ * ip; int /*<<< orphan*/ * ipstr; } ;
struct TYPE_13__ {char* acctId; char* version; int /*<<< orphan*/  superAuth; int /*<<< orphan*/  writeAuth; } ;
struct TYPE_12__ {int numOfIps; int /*<<< orphan*/ * ip; } ;
struct TYPE_10__ {char* pRsp; } ;
struct TYPE_11__ {TYPE_2__ res; TYPE_1__* pTscObj; } ;
struct TYPE_9__ {char* acctId; char* db; char* sversion; int /*<<< orphan*/  pTimer; int /*<<< orphan*/  superAuth; int /*<<< orphan*/  writeAuth; } ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlRes ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SIpList ;
typedef  TYPE_5__ SConnectRsp ;

/* Variables and functions */
 int TSDB_METER_ID_LEN ; 
 char* TS_PATH_DELIMITER ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tinet_ntoa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tsShellActivityTimer ; 
 TYPE_7__ tscMgmtIpList ; 
 int /*<<< orphan*/  tscPrintMgmtIp () ; 
 int /*<<< orphan*/  tscProcessActivityTimer ; 
 int /*<<< orphan*/  tscTmr ; 

int tscProcessConnectRsp(SSqlObj *pSql) {
  char         temp[TSDB_METER_ID_LEN];
  SConnectRsp *pConnect;

  STscObj *pObj = pSql->pTscObj;
  SSqlRes *pRes = &pSql->res;

  pConnect = (SConnectRsp *)pRes->pRsp;
  strcpy(pObj->acctId, pConnect->acctId);  // copy acctId from response
  sprintf(temp, "%s%s%s", pObj->acctId, TS_PATH_DELIMITER, pObj->db);
  strcpy(pObj->db, temp);
#ifdef CLUSTER
  SIpList *    pIpList;
  char *rsp = pRes->pRsp + sizeof(SConnectRsp);
  pIpList = (SIpList *)rsp;
  tscMgmtIpList.numOfIps = pIpList->numOfIps;
  for (int i = 0; i < pIpList->numOfIps; ++i) {
    tinet_ntoa(tscMgmtIpList.ipstr[i], pIpList->ip[i]);
    tscMgmtIpList.ip[i] = pIpList->ip[i];
  }

  rsp += sizeof(SIpList) + sizeof(int32_t) * pIpList->numOfIps;

  tscPrintMgmtIp();
#endif
  strcpy(pObj->sversion, pConnect->version);
  pObj->writeAuth = pConnect->writeAuth;
  pObj->superAuth = pConnect->superAuth;
  taosTmrReset(tscProcessActivityTimer, tsShellActivityTimer * 500, pObj, tscTmr, &pObj->pTimer);

  return 0;
}