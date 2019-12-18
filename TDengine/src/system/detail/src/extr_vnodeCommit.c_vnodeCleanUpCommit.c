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
struct TYPE_5__ {scalar_t__ logFd; int /*<<< orphan*/  logMutex; int /*<<< orphan*/  logFn; TYPE_1__ cfg; } ;
typedef  TYPE_2__ SVnodeObj ;

/* Variables and functions */
 scalar_t__ VALIDFD (scalar_t__) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  dError (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosLogError (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* vnodeList ; 

void vnodeCleanUpCommit(int vnode) {
  SVnodeObj *pVnode = vnodeList + vnode;

  if (VALIDFD(pVnode->logFd)) close(pVnode->logFd);

  if (pVnode->cfg.commitLog && (pVnode->logFd > 0 && remove(pVnode->logFn) < 0)) {
    dError("vid:%d, failed to remove:%s", vnode, pVnode->logFn);
    taosLogError("vid:%d, failed to remove:%s", vnode, pVnode->logFn);
  }

  pthread_mutex_destroy(&(pVnode->logMutex));
}