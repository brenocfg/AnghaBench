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
struct TYPE_4__ {scalar_t__ maxSessions; int /*<<< orphan*/  precision; } ;
struct TYPE_5__ {int vnode; int /*<<< orphan*/  numOfFiles; int /*<<< orphan*/  fileId; int /*<<< orphan*/  version; int /*<<< orphan*/  vmutex; int /*<<< orphan*/ * pCachePool; TYPE_1__ cfg; int /*<<< orphan*/  firstKey; } ;
typedef  TYPE_2__ SVnodeObj ;

/* Variables and functions */
 int /*<<< orphan*/  dError (char*,int) ; 
 int /*<<< orphan*/  dTrace (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosGetTimestamp (int /*<<< orphan*/ ) ; 
 scalar_t__ vnodeInitCommit (int) ; 
 scalar_t__ vnodeInitFile (int) ; 
 TYPE_2__* vnodeList ; 
 int /*<<< orphan*/ * vnodeOpenCachePool (int) ; 
 int /*<<< orphan*/  vnodeOpenMetersVnode (int) ; 

int vnodeInitStoreVnode(int vnode) {
  SVnodeObj *pVnode = vnodeList + vnode;

  pVnode->vnode = vnode;
  vnodeOpenMetersVnode(vnode);
  if (pVnode->cfg.maxSessions == 0) return 0;

  pVnode->firstKey = taosGetTimestamp(pVnode->cfg.precision);

  pVnode->pCachePool = vnodeOpenCachePool(vnode);
  if (pVnode->pCachePool == NULL) {
    dError("vid:%d, cache pool init failed.", pVnode->vnode);
    return -1;
  }

  if (vnodeInitFile(vnode) < 0) return -1;

  // vnodeOpenMeterMgmtStoreVnode(vnode);

  if (vnodeInitCommit(vnode) < 0) {
    dError("vid:%d, commit init failed.", pVnode->vnode);
    return -1;
  }

  pthread_mutex_init(&(pVnode->vmutex), NULL);
  dTrace("vid:%d, storage initialized, version:%ld fileId:%d numOfFiles:%d", vnode, pVnode->version, pVnode->fileId,
         pVnode->numOfFiles);

  return 0;
}