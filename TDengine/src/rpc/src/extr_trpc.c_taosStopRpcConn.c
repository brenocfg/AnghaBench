#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  qhandle; } ;
struct TYPE_10__ {int chann; int rspReceived; int /*<<< orphan*/  ahandle; scalar_t__ outType; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; TYPE_1__* pServer; } ;
struct TYPE_9__ {TYPE_3__* thandle; int /*<<< orphan*/  ahandle; int /*<<< orphan*/ * msg; int /*<<< orphan*/  fp; } ;
struct TYPE_8__ {int /*<<< orphan*/  label; TYPE_4__* channList; } ;
typedef  TYPE_1__ STaosRpc ;
typedef  TYPE_2__ SSchedMsg ;
typedef  TYPE_3__ SRpcConn ;
typedef  TYPE_4__ SRpcChann ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tTrace (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  taosCloseRpcConn (TYPE_3__*) ; 
 int /*<<< orphan*/  taosProcessSchedMsg ; 
 int /*<<< orphan*/  taosScheduleTask (int /*<<< orphan*/ ,TYPE_2__*) ; 

void taosStopRpcConn(void *thandle) {
  SRpcConn * pConn = (SRpcConn *)thandle;
  STaosRpc * pServer = pConn->pServer;
  SRpcChann *pChann = pServer->channList + pConn->chann;

  tTrace("%s cid:%d sid:%d id:%s, stop the connection pConn:%p", pServer->label, pConn->chann, pConn->sid,
         pConn->meterId, pConn);

  pthread_mutex_lock(&pChann->mutex);

  if (pConn->outType) {
    pConn->rspReceived = 1;
    SSchedMsg schedMsg;
    schedMsg.fp = taosProcessSchedMsg;
    schedMsg.msg = NULL;
    schedMsg.ahandle = pConn->ahandle;
    schedMsg.thandle = pConn;
    pthread_mutex_unlock(&pChann->mutex);

    taosScheduleTask(pChann->qhandle, &schedMsg);
  } else {
    pthread_mutex_unlock(&pChann->mutex);
    taosCloseRpcConn(pConn);
  }
}