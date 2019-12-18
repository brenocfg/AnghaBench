#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* vload; } ;
struct TYPE_9__ {int vnode; int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {int vnode; int vgId; } ;
typedef  TYPE_1__ SVnodeLoad ;
typedef  TYPE_2__ SVnodeGid ;
typedef  TYPE_3__ SDnodeObj ;

/* Variables and functions */
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmtCalcNumOfFreeVnodes (TYPE_3__*) ; 
 TYPE_3__* mgmtGetDnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosIpStr (int /*<<< orphan*/ ) ; 

void mgmtSetDnodeVgid(SVnodeGid vnodeGid[], int numOfVnodes, int vgId) {
  SDnodeObj *pDnode;

  for (int i = 0; i < numOfVnodes; ++i) {
    pDnode = mgmtGetDnode(vnodeGid[i].ip);
    if (pDnode) {
      SVnodeLoad *pVload = pDnode->vload + vnodeGid[i].vnode;
      memset(pVload, 0, sizeof(SVnodeLoad));
      pVload->vnode = vnodeGid[i].vnode;
      pVload->vgId = vgId;
      mTrace("dnode:%s, vnode:%d add to vgroup:%d", taosIpStr(vnodeGid[i].ip), vnodeGid[i].vnode, pVload->vgId);
      mgmtCalcNumOfFreeVnodes(pDnode);
    } else {
      mError("dnode:%s, not in dnode DB!!!", taosIpStr(vnodeGid[i].ip));
    }
  }
}