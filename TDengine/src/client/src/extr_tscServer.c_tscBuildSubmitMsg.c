#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  order; } ;
struct TYPE_17__ {char* payload; int /*<<< orphan*/  msgType; int /*<<< orphan*/  count; TYPE_1__ order; } ;
struct TYPE_16__ {size_t index; TYPE_2__* vpeerDesc; } ;
struct TYPE_15__ {TYPE_6__* pMeterMeta; } ;
struct TYPE_14__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  numOfSid; int /*<<< orphan*/  import; } ;
struct TYPE_13__ {TYPE_9__ cmd; } ;
struct TYPE_12__ {int /*<<< orphan*/  vnode; } ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SShellSubmitMsg ;
typedef  TYPE_5__ SMeterMetaInfo ;
typedef  TYPE_6__ SMeterMeta ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_SUBMIT ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int tsRpcHeadSize ; 
 TYPE_5__* tscGetMeterMetaInfo (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_3__*,int /*<<< orphan*/ ) ; 

int tscBuildSubmitMsg(SSqlObj *pSql) {
  SShellSubmitMsg *pShellMsg;
  char *           pMsg, *pStart;
  int              msgLen = 0;

  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(&pSql->cmd, 0);
  SMeterMeta *    pMeterMeta = pMeterMetaInfo->pMeterMeta;

  pStart = pSql->cmd.payload + tsRpcHeadSize;
  pMsg = pStart;

  pShellMsg = (SShellSubmitMsg *)pMsg;
  pShellMsg->import = pSql->cmd.order.order;
  pShellMsg->vnode = htons(pMeterMeta->vpeerDesc[pMeterMeta->index].vnode);
  pShellMsg->numOfSid = htonl(pSql->cmd.count);  // number of meters to be inserted

  // pSql->cmd.payloadLen is set during parse sql routine, so we do not use it here
  pSql->cmd.msgType = TSDB_MSG_TYPE_SUBMIT;
  tscTrace("%p update submit msg vnode:%d", pSql, htons(pShellMsg->vnode));

  return msgLen;
}