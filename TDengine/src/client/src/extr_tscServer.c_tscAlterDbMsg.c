#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  db; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  db; } ;
struct TYPE_12__ {char* payload; int payloadLen; int /*<<< orphan*/  msgType; } ;
struct TYPE_11__ {TYPE_1__* pTscObj; TYPE_3__ cmd; } ;
struct TYPE_10__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;
typedef  TYPE_4__ SMgmtHead ;
typedef  TYPE_5__ SMeterMetaInfo ;
typedef  TYPE_6__ SAlterDbMsg ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_ALTER_DB ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tsRpcHeadSize ; 
 TYPE_5__* tscGetMeterMetaInfo (TYPE_3__*,int /*<<< orphan*/ ) ; 

int tscAlterDbMsg(SSqlObj *pSql) {
  SAlterDbMsg *pAlterDbMsg;
  char *       pMsg, *pStart;
  int          msgLen = 0;

  SSqlCmd *       pCmd = &pSql->cmd;
  STscObj *       pObj = pSql->pTscObj;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  pStart = pCmd->payload + tsRpcHeadSize;
  pMsg = pStart;

  SMgmtHead *pMgmt = (SMgmtHead *)pMsg;
  strcpy(pMgmt->db, pObj->db);
  pMsg += sizeof(SMgmtHead);

  pAlterDbMsg = (SAlterDbMsg *)pMsg;
  strcpy(pAlterDbMsg->db, pMeterMetaInfo->name);

  pMsg += sizeof(SAlterDbMsg);

  msgLen = pMsg - pStart;
  pCmd->payloadLen = msgLen;
  pCmd->msgType = TSDB_MSG_TYPE_ALTER_DB;

  return msgLen;
}