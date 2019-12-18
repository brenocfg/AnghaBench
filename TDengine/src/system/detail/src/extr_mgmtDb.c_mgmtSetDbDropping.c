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
struct TYPE_15__ {scalar_t__ dropStatus; int /*<<< orphan*/  name; TYPE_3__* pHead; } ;
struct TYPE_14__ {int /*<<< orphan*/  privateIp; TYPE_1__* vload; } ;
struct TYPE_13__ {int numOfVnodes; struct TYPE_13__* next; TYPE_2__* vnodeGid; } ;
struct TYPE_12__ {size_t vnode; int /*<<< orphan*/  ip; } ;
struct TYPE_11__ {scalar_t__ dropStatus; } ;
typedef  TYPE_1__ SVnodeLoad ;
typedef  TYPE_2__ SVnodeGid ;
typedef  TYPE_3__ SVgObj ;
typedef  TYPE_4__ SDnodeObj ;
typedef  TYPE_5__ SDbObj ;

/* Variables and functions */
 int TSDB_CODE_SDB_ERROR ; 
 scalar_t__ TSDB_DB_STATUS_DROPPING ; 
 scalar_t__ TSDB_DB_STATUS_DROP_FROM_SDB ; 
 scalar_t__ TSDB_VN_STATUS_DROPPING ; 
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mPrint (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_4__* mgmtGetDnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmtSendFreeVnodeMsg (TYPE_3__*) ; 
 scalar_t__ mgmtUpdateDb (TYPE_5__*) ; 
 scalar_t__ mgmtUpdateDnode (TYPE_4__*) ; 
 int /*<<< orphan*/  taosIpStr (int /*<<< orphan*/ ) ; 

int mgmtSetDbDropping(SDbObj *pDb) {
  if (pDb->dropStatus == TSDB_DB_STATUS_DROP_FROM_SDB) return 0;

  SVgObj *pVgroup = pDb->pHead;
  while (pVgroup != NULL) {
    for (int i = 0; i < pVgroup->numOfVnodes; i++) {
      SVnodeGid *pVnodeGid = pVgroup->vnodeGid + i;
      SDnodeObj *pDnode = mgmtGetDnode(pVnodeGid->ip);
      if (pDnode == NULL) continue;

      SVnodeLoad *pVload = &pDnode->vload[pVnodeGid->vnode];
      if (pVload->dropStatus != TSDB_VN_STATUS_DROPPING) {
        pVload->dropStatus = TSDB_VN_STATUS_DROPPING;

        mPrint("dnode:%s vnode:%d db:%s set to dropping status", taosIpStr(pDnode->privateIp), pVnodeGid->vnode, pDb->name);
        if (mgmtUpdateDnode(pDnode) < 0) {
          mError("db:%s drop failed, dnode sdb update error", pDb->name);
          return TSDB_CODE_SDB_ERROR;
        }
      }
    }
    mgmtSendFreeVnodeMsg(pVgroup);
    pVgroup = pVgroup->next;
  }

  if (pDb->dropStatus == TSDB_DB_STATUS_DROPPING) return 0;

  pDb->dropStatus = TSDB_DB_STATUS_DROPPING;
  if (mgmtUpdateDb(pDb) < 0) {
    mError("db:%s drop failed, db sdb update error", pDb->name);
    return TSDB_CODE_SDB_ERROR;
  }

  mPrint("db:%s set to dropping status", pDb->name);
  return 0;
}