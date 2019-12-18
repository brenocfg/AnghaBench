#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numOfVnodes; int numOfFreeVnodes; int /*<<< orphan*/  privateIp; TYPE_1__* vload; } ;
struct TYPE_4__ {scalar_t__ vgId; size_t status; size_t dropStatus; size_t syncStatus; } ;
typedef  TYPE_1__ SVnodeLoad ;
typedef  TYPE_2__ SDnodeObj ;

/* Variables and functions */
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,int,int,int,...) ; 
 int /*<<< orphan*/ * sdbDnodeStatusStr ; 
 int /*<<< orphan*/ * sdbVnodeDropStateStr ; 
 int /*<<< orphan*/ * sdbVnodeSyncStatusStr ; 
 int /*<<< orphan*/  taosIpStr (int /*<<< orphan*/ ) ; 

void mgmtCalcNumOfFreeVnodes(SDnodeObj *pDnode) {
  int totalVnodes = 0;

  for (int i = 0; i < pDnode->numOfVnodes; ++i) {
    SVnodeLoad *pVload = pDnode->vload + i;
    if (pVload->vgId != 0) {
      mTrace("dnode:%s, calc free vnodes, exist vnode:%d, vgroup:%d, state:%d %s, dropstate:%d %s, syncstatus:%d %s",
             taosIpStr(pDnode->privateIp), i, pVload->vgId,
             pVload->status, sdbDnodeStatusStr[pVload->status],
             pVload->dropStatus, sdbVnodeDropStateStr[pVload->dropStatus],
             pVload->syncStatus, sdbVnodeSyncStatusStr[pVload->syncStatus]);
      totalVnodes++;
    }
  }

  pDnode->numOfFreeVnodes = pDnode->numOfVnodes - totalVnodes;
  mTrace("dnode:%s, calc free vnodes, numOfVnodes:%d, numOfFreeVnodes:%d, totalVnodes:%d",
          taosIpStr(pDnode->privateIp), pDnode->numOfVnodes, pDnode->numOfFreeVnodes, totalVnodes);
}