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
struct TYPE_4__ {scalar_t__ commitLog; } ;
struct TYPE_5__ {char* logFn; char* logOFn; int logFd; int /*<<< orphan*/  logMutex; int /*<<< orphan*/  version; TYPE_1__ cfg; int /*<<< orphan*/  mappingSize; int /*<<< orphan*/  pMem; } ;
typedef  TYPE_2__ SVnodeObj ;

/* Variables and functions */
 scalar_t__ VALIDFD (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 TYPE_2__* vnodeList ; 
 int /*<<< orphan*/  vnodeOpenCommitLog (int,int /*<<< orphan*/ ) ; 

int vnodeRenewCommitLog(int vnode) {
  SVnodeObj *pVnode = vnodeList + vnode;
  char *     fileName = pVnode->logFn;
  char *     oldName = pVnode->logOFn;

  pthread_mutex_lock(&(pVnode->logMutex));

  if (VALIDFD(pVnode->logFd)) {
    munmap(pVnode->pMem, pVnode->mappingSize);
    close(pVnode->logFd);
    rename(fileName, oldName);
  }

  if (pVnode->cfg.commitLog) vnodeOpenCommitLog(vnode, vnodeList[vnode].version);

  pthread_mutex_unlock(&(pVnode->logMutex));

  return pVnode->logFd;
}