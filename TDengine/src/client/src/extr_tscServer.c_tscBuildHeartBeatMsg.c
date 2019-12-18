#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  db; } ;
struct TYPE_12__ {char* payload; int payloadLen; int /*<<< orphan*/  msgType; } ;
struct TYPE_11__ {TYPE_1__* pTscObj; TYPE_3__ cmd; } ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;
typedef  TYPE_4__ SMgmtHead ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_HEARTBEAT ; 
 int /*<<< orphan*/  assert (int) ; 
 int minMsgSize () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tsRpcHeadSize ; 
 scalar_t__ tscAllocPayload (TYPE_3__*,int) ; 
 char* tscBuildQueryStreamDesc (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  tscError (char*,TYPE_2__*) ; 
 int tscEstimateHeartBeatMsgLength (TYPE_2__*) ; 

int tscBuildHeartBeatMsg(SSqlObj *pSql) {
  char *pMsg, *pStart;
  int   msgLen = 0;
  int   size = 0;

  SSqlCmd *pCmd = &pSql->cmd;
  STscObj *pObj = pSql->pTscObj;

  pthread_mutex_lock(&pObj->mutex);

  size = tscEstimateHeartBeatMsgLength(pSql);
  if (TSDB_CODE_SUCCESS != tscAllocPayload(pCmd, size)) {
    tscError("%p failed to malloc for heartbeat msg", pSql);
    return -1;
  }

  pMsg = pCmd->payload + tsRpcHeadSize;
  pStart = pMsg;

  SMgmtHead *pMgmt = (SMgmtHead *)pMsg;
  strcpy(pMgmt->db, pObj->db);
  pMsg += sizeof(SMgmtHead);

  pMsg = tscBuildQueryStreamDesc(pMsg, pObj);
  pthread_mutex_unlock(&pObj->mutex);

  msgLen = pMsg - pStart;
  pCmd->payloadLen = msgLen;
  pCmd->msgType = TSDB_MSG_TYPE_HEARTBEAT;

  assert(msgLen + minMsgSize() <= size);
  return msgLen;
}