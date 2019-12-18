#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_13__ {char* tags; int /*<<< orphan*/  createFlag; int /*<<< orphan*/  meterId; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  db; } ;
struct TYPE_10__ {int allocSize; char* payload; scalar_t__* defaultVal; int payloadLen; int /*<<< orphan*/  msgType; } ;
struct TYPE_9__ {TYPE_2__ cmd; } ;
typedef  int /*<<< orphan*/  STagData ;
typedef  TYPE_1__ SSqlObj ;
typedef  TYPE_2__ SSqlCmd ;
typedef  TYPE_3__ SMgmtHead ;
typedef  TYPE_4__ SMeterMetaInfo ;
typedef  TYPE_5__ SMeterInfoMsg ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_METERINFO ; 
 int /*<<< orphan*/  assert (int) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ minMsgSize () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (char*) ; 
 int tsRpcHeadSize ; 
 int /*<<< orphan*/  tscGetDBInfoFromMeterId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* tscGetMeterMetaInfo (TYPE_2__*,int /*<<< orphan*/ ) ; 

int tscBuildMeterMetaMsg(SSqlObj *pSql) {
  SMeterInfoMsg *pInfoMsg;
  char *         pMsg, *pStart;
  int            msgLen = 0;

  char *tmpData = 0;
  if (pSql->cmd.allocSize > 0) {
    tmpData = calloc(1, pSql->cmd.allocSize);
    if (NULL == tmpData) return -1;
    // STagData is in binary format, strncpy is not available
    memcpy(tmpData, pSql->cmd.payload, pSql->cmd.allocSize);
  }

  SSqlCmd *       pCmd = &pSql->cmd;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  pMsg = pCmd->payload + tsRpcHeadSize;
  pStart = pMsg;

  SMgmtHead *pMgmt = (SMgmtHead *)pMsg;
  tscGetDBInfoFromMeterId(pMeterMetaInfo->name, pMgmt->db);

  pMsg += sizeof(SMgmtHead);

  pInfoMsg = (SMeterInfoMsg *)pMsg;
  strcpy(pInfoMsg->meterId, pMeterMetaInfo->name);
  pInfoMsg->createFlag = htons((uint16_t)pCmd->defaultVal[0]);
  pMsg += sizeof(SMeterInfoMsg);

  if (pCmd->defaultVal[0] != 0) {
    memcpy(pInfoMsg->tags, tmpData, sizeof(STagData));
    pMsg += sizeof(STagData);
  }

  msgLen = pMsg - pStart;
  pCmd->payloadLen = msgLen;
  pCmd->msgType = TSDB_MSG_TYPE_METERINFO;

  tfree(tmpData);

  assert(msgLen + minMsgSize() <= pCmd->allocSize);
  return msgLen;
}