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
struct TYPE_11__ {int msgType; } ;
struct TYPE_10__ {scalar_t__ signature; void* ahandle; TYPE_1__* pServer; } ;
struct TYPE_9__ {scalar_t__ thandle; int /*<<< orphan*/ * msg; int /*<<< orphan*/  ahandle; } ;
struct TYPE_8__ {void* (* fp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ;} ;
typedef  TYPE_1__ STaosRpc ;
typedef  int /*<<< orphan*/  STaosHeader ;
typedef  TYPE_2__ SSchedMsg ;
typedef  TYPE_3__ SRpcConn ;
typedef  TYPE_4__ SIntMsg ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  taosCloseRpcConn (TYPE_3__*) ; 
 int /*<<< orphan*/  taosProcessResponse (TYPE_3__*) ; 

void taosProcessSchedMsg(SSchedMsg *pMsg) {
  SIntMsg * pHeader = (SIntMsg *)pMsg->msg;
  SRpcConn *pConn = (SRpcConn *)pMsg->thandle;
  if (pConn == NULL || pConn->signature != pMsg->thandle || pConn->pServer == NULL) return;
  STaosRpc *pRpc = pConn->pServer;

  void *ahandle = (*(pRpc->fp))(pMsg->msg, pMsg->ahandle, pMsg->thandle);

  if (ahandle == NULL || pMsg->msg == NULL) {
    taosCloseRpcConn(pConn);
  } else {
    pConn->ahandle = ahandle;
    if (pHeader && ((pHeader->msgType & 1) == 0)) taosProcessResponse(pConn);
  }

  if (pMsg->msg) free(pMsg->msg - sizeof(STaosHeader) + sizeof(SIntMsg));
}