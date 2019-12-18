#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  name; TYPE_3__* pHead; } ;
struct TYPE_11__ {scalar_t__ status; int /*<<< orphan*/  privateIp; TYPE_1__* vload; } ;
struct TYPE_10__ {int numOfVnodes; struct TYPE_10__* next; TYPE_2__* vnodeGid; } ;
struct TYPE_9__ {size_t vnode; int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {scalar_t__ dropStatus; } ;
typedef  TYPE_1__ SVnodeLoad ;
typedef  TYPE_2__ SVnodeGid ;
typedef  TYPE_3__ SVgObj ;
typedef  TYPE_4__ SDnodeObj ;
typedef  TYPE_5__ SDbObj ;

/* Variables and functions */
 scalar_t__ TSDB_STATUS_OFFLINE ; 
 scalar_t__ TSDB_VN_STATUS_DROPPING ; 
 int /*<<< orphan*/  mPrint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 TYPE_4__* mgmtGetDnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosIpStr (int /*<<< orphan*/ ) ; 

bool mgmtCheckDropDbFinished(SDbObj *pDb) {
  SVgObj *pVgroup = pDb->pHead;
  while (pVgroup) {
    for (int i = 0; i < pVgroup->numOfVnodes; i++) {
      SVnodeGid *pVnodeGid = pVgroup->vnodeGid + i;
      SDnodeObj *pDnode = mgmtGetDnode(pVnodeGid->ip);

      if (pDnode == NULL) continue;
      if (pDnode->status == TSDB_STATUS_OFFLINE) continue;

      SVnodeLoad *pVload = &pDnode->vload[pVnodeGid->vnode];
      if (pVload->dropStatus == TSDB_VN_STATUS_DROPPING) {
        mTrace("dnode:%s, vnode:%d db:%s wait dropping", taosIpStr(pDnode->privateIp), pVnodeGid->vnode, pDb->name);
        return false;
      }
    }
    pVgroup = pVgroup->next;
  }

  mPrint("db:%s all vnodes drop finished", pDb->name);
  return true;
}