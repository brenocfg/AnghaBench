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
typedef  int int32_t ;
struct TYPE_5__ {scalar_t__ maxSessions; } ;
struct TYPE_6__ {int vnode; TYPE_1__ cfg; int /*<<< orphan*/  accessState; } ;
typedef  TYPE_2__ SVnodeObj ;

/* Variables and functions */
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_VN_ALL_ACCCESS ; 
 int /*<<< orphan*/  dTrace (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int tsMaxVnode ; 
 int /*<<< orphan*/  tsOpenVnodes ; 
 int /*<<< orphan*/  vnodeCalcOpenVnodes () ; 
 TYPE_2__* vnodeList ; 
 int /*<<< orphan*/  vnodeOpenPeerVnode (int) ; 
 int vnodeOpenShellVnode (int) ; 
 int /*<<< orphan*/  vnodeOpenStreams (TYPE_2__*,int /*<<< orphan*/ *) ; 

int vnodeOpenVnode(int vnode) {
  int32_t code = TSDB_CODE_SUCCESS;

  SVnodeObj *pVnode = vnodeList + vnode;

  pVnode->vnode = vnode;
  pVnode->accessState = TSDB_VN_ALL_ACCCESS;

  // vnode is empty
  if (pVnode->cfg.maxSessions == 0) return 0;

  pthread_mutex_lock(&dmutex);
  // vnodeOpenMeterMgmtVnode(vnode);

  // not enough memory, abort
  if ((code = vnodeOpenShellVnode(vnode)) != TSDB_CODE_SUCCESS) {
    pthread_mutex_unlock(&dmutex);
    return code;
  }

  vnodeOpenPeerVnode(vnode);

  if (vnode > tsMaxVnode) tsMaxVnode = vnode;

  vnodeCalcOpenVnodes();

  pthread_mutex_unlock(&dmutex);

#ifndef CLUSTER
  vnodeOpenStreams(pVnode, NULL);
#endif

  dTrace("vid:%d, vnode is opened, openVnodes:%d", vnode, tsOpenVnodes);

  return 0;
}