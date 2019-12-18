#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ commitThread; scalar_t__ pCachePool; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_STATUS_OFFLINE ; 
 int /*<<< orphan*/  dmutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosMsleep (int) ; 
 int /*<<< orphan*/  vnodeCleanUpCommit (int) ; 
 int /*<<< orphan*/  vnodeClosePeerVnode (int) ; 
 TYPE_1__* vnodeList ; 
 int /*<<< orphan*/  vnodeProcessCommitTimer (TYPE_1__*,int /*<<< orphan*/ *) ; 

void vnodeCleanUpOneVnode(int vnode) {
  static int again = 0;
  if (vnodeList == NULL) return;

  pthread_mutex_lock(&dmutex);

  if (again) {
    pthread_mutex_unlock(&dmutex);
    return;
  }
  again = 1;

  if (vnodeList[vnode].pCachePool) {
    vnodeList[vnode].status = TSDB_STATUS_OFFLINE;
    vnodeClosePeerVnode(vnode);
  }

  pthread_mutex_unlock(&dmutex);

  if (vnodeList[vnode].pCachePool) {
    vnodeProcessCommitTimer(vnodeList + vnode, NULL);
    while (vnodeList[vnode].commitThread != 0) {
      taosMsleep(10);
    }
    vnodeCleanUpCommit(vnode);
  }
}