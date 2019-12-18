#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {char privilege; int /*<<< orphan*/  flag; int /*<<< orphan*/  pass; int /*<<< orphan*/  user; } ;
struct TYPE_17__ {char* name; } ;
struct TYPE_16__ {int /*<<< orphan*/  db; } ;
struct TYPE_12__ {int /*<<< orphan*/  order; } ;
struct TYPE_15__ {char* payload; int payloadLen; int /*<<< orphan*/  msgType; scalar_t__ count; TYPE_1__ order; } ;
struct TYPE_14__ {TYPE_2__* pTscObj; TYPE_4__ cmd; } ;
struct TYPE_13__ {char* db; } ;
typedef  TYPE_2__ STscObj ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SSqlCmd ;
typedef  TYPE_5__ SMgmtHead ;
typedef  TYPE_6__ SMeterMetaInfo ;
typedef  TYPE_7__ SCreateUserMsg ;
typedef  TYPE_7__ SAlterUserMsg ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_ALTER_USER ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int tsRpcHeadSize ; 
 TYPE_6__* tscGetMeterMetaInfo (TYPE_4__*,int /*<<< orphan*/ ) ; 

int tscBuildAlterUserMsg(SSqlObj *pSql) {
  SAlterUserMsg *pAlterMsg;
  char *         pMsg, *pStart;
  int            msgLen = 0;

  SSqlCmd *       pCmd = &pSql->cmd;
  STscObj *       pObj = pSql->pTscObj;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  pMsg = pCmd->payload + tsRpcHeadSize;
  pStart = pMsg;

  SMgmtHead *pMgmt = (SMgmtHead *)pMsg;
  strcpy(pMgmt->db, pObj->db);
  pMsg += sizeof(SMgmtHead);

  pAlterMsg = (SCreateUserMsg *)pMsg;
  strcpy(pAlterMsg->user, pMeterMetaInfo->name);
  strcpy(pAlterMsg->pass, pCmd->payload);
  pAlterMsg->flag = pCmd->order.order;
  pAlterMsg->privilege = (char)pCmd->count;

  pMsg += sizeof(SAlterUserMsg);

  msgLen = pMsg - pStart;
  pCmd->payloadLen = msgLen;
  pCmd->msgType = TSDB_MSG_TYPE_ALTER_USER;

  return msgLen;
}