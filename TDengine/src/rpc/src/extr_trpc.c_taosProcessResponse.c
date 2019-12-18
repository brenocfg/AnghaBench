#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int msgLen; scalar_t__ ahandle; struct TYPE_15__* next; } ;
struct TYPE_14__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  tmrCtrl; } ;
struct TYPE_13__ {int chann; int /*<<< orphan*/  pTimer; int /*<<< orphan*/ * pTail; TYPE_5__* pHead; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; int /*<<< orphan*/  outTranId; int /*<<< orphan*/  outType; scalar_t__ ahandle; TYPE_5__* pMsgNode; scalar_t__ rspReceived; struct TYPE_13__* signature; TYPE_1__* pServer; } ;
struct TYPE_12__ {int /*<<< orphan*/  tranId; int /*<<< orphan*/  msgType; } ;
struct TYPE_11__ {scalar_t__ noFree; int /*<<< orphan*/  label; TYPE_4__* channList; } ;
typedef  TYPE_1__ STaosRpc ;
typedef  TYPE_2__ STaosHeader ;
typedef  TYPE_3__ SRpcConn ;
typedef  TYPE_4__ SRpcChann ;
typedef  TYPE_5__ SMsgNode ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tError (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  taosProcessTaosTimer ; 
 int /*<<< orphan*/  taosSendDataToPeer (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (TYPE_5__*) ; 
 int /*<<< orphan*/  tsRpcTimer ; 

void taosProcessResponse(SRpcConn *pConn) {
  STaosHeader *pHeader;
  char *       msg = NULL;
  int          msgLen = 0;

  if (pConn == NULL) return;
  STaosRpc *pServer = pConn->pServer;
  if (pConn->signature != pConn || pServer == NULL) return;
  SRpcChann *pChann = pServer->channList + pConn->chann;

  pthread_mutex_lock(&pChann->mutex);

  pConn->outType = 0;
  pConn->rspReceived = 0;
  if (pServer->noFree == 0) tfree(pConn->pMsgNode);
  pConn->pMsgNode = NULL;

  if (pConn->pHead) {
    SMsgNode *pMsgNode = pConn->pHead;
    //      assert ( pMsgNode->msgLen >= sizeof(STaosHeader) && pMsgNode->msgLen < RPC_MAX_UDP_SIZE);
    if (pMsgNode->msgLen >= sizeof(STaosHeader)) {
      pConn->pMsgNode = pMsgNode;
      pConn->pHead = pMsgNode->next;
      if (pMsgNode->ahandle) pConn->ahandle = pMsgNode->ahandle;

      pHeader = (STaosHeader *)((char *)pMsgNode + sizeof(SMsgNode));
      pConn->outType = pHeader->msgType;
      pConn->outTranId = pHeader->tranId;

      msg = (char *)pHeader;
      msgLen = pMsgNode->msgLen;

    } else {
      tError("%s cid:%d sid:%d id:%s, invalid msgLen:%d pConn:%p", pServer->label, pConn->chann, pConn->sid,
             pConn->meterId, pMsgNode->msgLen, pConn);
      pConn->pHead = NULL;
    }

    if (pConn->pHead == NULL) pConn->pTail = NULL;
  }

  if (msg) {
    taosSendDataToPeer(pConn, msg, msgLen);
    taosTmrReset(taosProcessTaosTimer, tsRpcTimer, pConn, pChann->tmrCtrl, &pConn->pTimer);
  }

  pthread_mutex_unlock(&pChann->mutex);

}