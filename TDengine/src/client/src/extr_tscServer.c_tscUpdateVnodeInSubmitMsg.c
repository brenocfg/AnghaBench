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
struct TYPE_13__ {TYPE_1__* vpeerDesc; } ;
struct TYPE_12__ {TYPE_5__* pMeterMeta; } ;
struct TYPE_11__ {int /*<<< orphan*/  vnode; } ;
struct TYPE_10__ {size_t index; int /*<<< orphan*/  cmd; } ;
struct TYPE_9__ {int /*<<< orphan*/  vnode; } ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SShellSubmitMsg ;
typedef  TYPE_4__ SMeterMetaInfo ;
typedef  TYPE_5__ SMeterMeta ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int tsRpcHeadSize ; 
 TYPE_4__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 

void tscUpdateVnodeInSubmitMsg(SSqlObj *pSql, char *buf) {
  SShellSubmitMsg *pShellMsg;
  char *           pMsg;
  SMeterMetaInfo * pMeterMetaInfo = tscGetMeterMetaInfo(&pSql->cmd, 0);

  SMeterMeta *pMeterMeta = pMeterMetaInfo->pMeterMeta;

  pMsg = buf + tsRpcHeadSize;

  pShellMsg = (SShellSubmitMsg *)pMsg;
  pShellMsg->vnode = htons(pMeterMeta->vpeerDesc[pSql->index].vnode);
  tscTrace("%p update submit msg vnode:%d", pSql, htons(pShellMsg->vnode));
}