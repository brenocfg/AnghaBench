#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int replications; } ;
struct TYPE_6__ {TYPE_1__ cfg; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ SVnodeObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_STATUS_MASTER ; 
 int /*<<< orphan*/  TSDB_STATUS_UNSYNCED ; 
 int /*<<< orphan*/  dTrace (char*,int,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* vnodeList ; 
 int /*<<< orphan*/  vnodeUpdateStreamRole (TYPE_2__*) ; 

int vnodeOpenPeerVnode(int vnode) {
  SVnodeObj *pVnode = vnodeList + vnode;
  pVnode->status = (pVnode->cfg.replications > 1) ? TSDB_STATUS_UNSYNCED : TSDB_STATUS_MASTER;
  dTrace("vid:%d, vnode status:%d numOfPeers:%d", vnode, pVnode->status, pVnode->cfg.replications-1);
  vnodeUpdateStreamRole(pVnode);
  return 0;
}