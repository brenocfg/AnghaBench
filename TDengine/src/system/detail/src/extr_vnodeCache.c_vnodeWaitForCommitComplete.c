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
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {scalar_t__ commitInProcess; int /*<<< orphan*/  vmutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  vnode; scalar_t__ pCachePool; } ;
typedef  TYPE_1__ SVnodeObj ;
typedef  TYPE_2__ SCachePool ;

/* Variables and functions */
 int /*<<< orphan*/  dWarn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosMsleep (int) ; 

__attribute__((used)) static void vnodeWaitForCommitComplete(SVnodeObj *pVnode) {
  SCachePool *pPool = (SCachePool *)(pVnode->pCachePool);

  // wait for 100s at most
  const int32_t totalCount = 1000;
  int32_t count = 0;

  // all meter is marked as dropped, so the commit will abort very quickly
  while(count++ < totalCount) {
    int32_t commitInProcess = 0;

    pthread_mutex_lock(&pPool->vmutex);
    commitInProcess = pPool->commitInProcess;
    pthread_mutex_unlock(&pPool->vmutex);

    if (commitInProcess) {
      dWarn("vid:%d still in commit, wait for completed", pVnode->vnode);
      taosMsleep(10);
    }
  }
}