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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
struct TYPE_14__ {int /*<<< orphan*/  db; } ;
struct TYPE_13__ {char* payload; int payloadLen; int /*<<< orphan*/  msgType; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {int /*<<< orphan*/  qhandle; } ;
struct TYPE_12__ {TYPE_1__ res; TYPE_2__* pTscObj; TYPE_4__ cmd; } ;
struct TYPE_11__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ STscObj ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SSqlCmd ;
typedef  TYPE_5__ SMgmtHead ;
typedef  TYPE_6__ SMeterMetaInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_RETRIEVE ; 
 char htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int tsRpcHeadSize ; 
 TYPE_6__* tscGetMeterMetaInfo (TYPE_4__*,int /*<<< orphan*/ ) ; 

int tscBuildRetrieveFromMgmtMsg(SSqlObj *pSql) {
  char *pMsg, *pStart;
  int   msgLen = 0;

  SSqlCmd *pCmd = &pSql->cmd;
  STscObj *pObj = pSql->pTscObj;
  pMsg = pCmd->payload + tsRpcHeadSize;
  pStart = pMsg;

  SMgmtHead *pMgmt = (SMgmtHead *)pMsg;

  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);
  size_t          nameLen = strlen(pMeterMetaInfo->name);

  if (nameLen > 0) {
    strcpy(pMgmt->db, pMeterMetaInfo->name);
  } else {
    strcpy(pMgmt->db, pObj->db);
  }

  pMsg += sizeof(SMgmtHead);

  *((uint64_t *)pMsg) = pSql->res.qhandle;
  pMsg += sizeof(pSql->res.qhandle);

  *pMsg = htons(pCmd->type);
  pMsg += sizeof(pCmd->type);

  msgLen = pMsg - pStart;
  pCmd->payloadLen = msgLen;
  pCmd->msgType = TSDB_MSG_TYPE_RETRIEVE;

  return msgLen;
}