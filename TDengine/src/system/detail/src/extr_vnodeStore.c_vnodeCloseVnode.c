#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ maxSessions; } ;
struct TYPE_9__ {int /*<<< orphan*/  meterIndex; int /*<<< orphan*/  vmutex; TYPE_1__ cfg; } ;
typedef  TYPE_2__ SVnodeObj ;

/* Variables and functions */
 int TSDB_CODE_ACTION_IN_PROGRESS ; 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  dmutex ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ ) ; 
 int tsMaxVnode ; 
 int /*<<< orphan*/  vnodeCalcOpenVnodes () ; 
 int /*<<< orphan*/  vnodeCancelCommit (TYPE_2__*) ; 
 int /*<<< orphan*/  vnodeCleanUpCommit (int) ; 
 int /*<<< orphan*/  vnodeCloseCachePool (int) ; 
 int /*<<< orphan*/  vnodeCloseMetersVnode (int) ; 
 int /*<<< orphan*/  vnodeClosePeerVnode (int) ; 
 int /*<<< orphan*/  vnodeCloseShellVnode (int) ; 
 int /*<<< orphan*/  vnodeCloseStream (TYPE_2__*) ; 
 TYPE_2__* vnodeList ; 
 int vnodeMarkAllMetersDropped (TYPE_2__*) ; 

int vnodeCloseVnode(int vnode) {
  if (vnodeList == NULL) return TSDB_CODE_SUCCESS;

  SVnodeObj* pVnode = &vnodeList[vnode];

  pthread_mutex_lock(&dmutex);
  if (pVnode->cfg.maxSessions == 0) {
    pthread_mutex_unlock(&dmutex);
    return TSDB_CODE_SUCCESS;
  }

  // set the meter is dropped flag 
  if (vnodeMarkAllMetersDropped(pVnode) != TSDB_CODE_SUCCESS) {
    pthread_mutex_unlock(&dmutex);
    return TSDB_CODE_ACTION_IN_PROGRESS;
  }

  vnodeCloseStream(vnodeList + vnode);
  vnodeCancelCommit(vnodeList + vnode);
  vnodeClosePeerVnode(vnode);
  vnodeCloseMetersVnode(vnode);
  vnodeCloseShellVnode(vnode);
  vnodeCloseCachePool(vnode);
  vnodeCleanUpCommit(vnode);

  pthread_mutex_destroy(&(vnodeList[vnode].vmutex));

  if (tsMaxVnode == vnode) tsMaxVnode = vnode - 1;

  tfree(vnodeList[vnode].meterIndex);
  memset(vnodeList + vnode, 0, sizeof(SVnodeObj));

  vnodeCalcOpenVnodes();

  pthread_mutex_unlock(&dmutex);
  return TSDB_CODE_SUCCESS;
}