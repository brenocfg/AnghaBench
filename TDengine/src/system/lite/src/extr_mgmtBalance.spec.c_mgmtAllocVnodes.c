#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int numOfVnodes; int lastAllocVnode; int /*<<< orphan*/  numOfFreeVnodes; TYPE_1__* vload; } ;
struct TYPE_9__ {TYPE_2__* vnodeGid; int /*<<< orphan*/  vgId; } ;
struct TYPE_8__ {int vnode; } ;
struct TYPE_7__ {scalar_t__ vgId; scalar_t__ status; } ;
typedef  TYPE_3__ SVgObj ;
typedef  TYPE_4__ SDnodeObj ;

/* Variables and functions */
 scalar_t__ TSDB_VN_STATUS_READY ; 
 TYPE_4__ dnodeObj ; 
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,int,int) ; 

int mgmtAllocVnodes(SVgObj *pVgroup) {
  int        selectedVnode = -1;
  SDnodeObj *pDnode = &dnodeObj;

  for (int i = 0; i < pDnode->numOfVnodes; i++) {
    int vnode = (i + pDnode->lastAllocVnode) % pDnode->numOfVnodes;
    if (pDnode->vload[vnode].vgId == 0 && pDnode->vload[vnode].status == TSDB_VN_STATUS_READY) {
      selectedVnode = vnode;
      break;
    }
  }

  if (selectedVnode == -1) {
    mError("vgroup:%d alloc vnode failed, free vnodes:%d", pVgroup->vgId, pDnode->numOfFreeVnodes);
    return -1;
  } else {
    mTrace("vgroup:%d allocate vnode:%d, last allocated vnode:%d", pVgroup->vgId, selectedVnode,
           pDnode->lastAllocVnode);
    pVgroup->vnodeGid[0].vnode = selectedVnode;
    pDnode->lastAllocVnode = selectedVnode + 1;
    if (pDnode->lastAllocVnode >= pDnode->numOfVnodes) pDnode->lastAllocVnode = 0;
    return 0;
  }
}