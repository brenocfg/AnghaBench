#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_9__ {int commitInProcess; } ;
struct TYPE_7__ {int commitTime; } ;
struct TYPE_8__ {scalar_t__ status; int /*<<< orphan*/  commitThread; int /*<<< orphan*/  vnode; int /*<<< orphan*/  commitTimer; TYPE_1__ cfg; scalar_t__ pCachePool; } ;
typedef  TYPE_2__ SVnodeObj ;
typedef  TYPE_3__ SCachePool ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 scalar_t__ TSDB_STATUS_UNSYNCED ; 
 int /*<<< orphan*/  dError (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dTrace (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosTmrStopA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeCommitToFile ; 
 int /*<<< orphan*/  vnodeProcessCommitTimer ; 
 int /*<<< orphan*/  vnodeTmrCtrl ; 

pthread_t vnodeCreateCommitThread(SVnodeObj *pVnode) {
  // this function has to mutex locked before it is called

  pthread_attr_t thattr;
  SCachePool *   pPool = (SCachePool *)pVnode->pCachePool;

  if (pPool->commitInProcess) {
    dTrace("vid:%d, commit is already in process", pVnode->vnode);
    return pVnode->commitThread;
  }

  taosTmrStopA(&pVnode->commitTimer);

  if (pVnode->status == TSDB_STATUS_UNSYNCED) {
    taosTmrReset(vnodeProcessCommitTimer, pVnode->cfg.commitTime * 1000, pVnode, vnodeTmrCtrl, &pVnode->commitTimer);
    dTrace("vid:%d, it is in unsyc state, commit later", pVnode->vnode);
    return pVnode->commitThread;
  }

  pthread_attr_init(&thattr);
  pthread_attr_setdetachstate(&thattr, PTHREAD_CREATE_DETACHED);
  if (pthread_create(&(pVnode->commitThread), &thattr, vnodeCommitToFile, pVnode) != 0) {
    dError("vid:%d, failed to create thread to commit file, reason:%s", pVnode->vnode, strerror(errno));
  } else {
    pPool->commitInProcess = 1;
    dTrace("vid:%d, commit thread: 0x%lx is created", pVnode->vnode, pVnode->commitThread);
  }

  pthread_attr_destroy(&thattr);

  return pVnode->commitThread;
}