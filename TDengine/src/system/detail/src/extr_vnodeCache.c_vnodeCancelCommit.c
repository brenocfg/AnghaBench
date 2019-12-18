#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int commitTime; } ;
struct TYPE_7__ {int /*<<< orphan*/  commitTimer; TYPE_1__ cfg; scalar_t__ pCachePool; } ;
typedef  TYPE_2__ SVnodeObj ;
typedef  int /*<<< orphan*/  SCachePool ;

/* Variables and functions */
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeProcessCommitTimer ; 
 int /*<<< orphan*/  vnodeTmrCtrl ; 
 int /*<<< orphan*/  vnodeWaitForCommitComplete (TYPE_2__*) ; 

void vnodeCancelCommit(SVnodeObj *pVnode) {
  SCachePool *pPool = (SCachePool *)(pVnode->pCachePool);
  if (pPool == NULL) return;

  vnodeWaitForCommitComplete(pVnode);
  taosTmrReset(vnodeProcessCommitTimer, pVnode->cfg.commitTime * 1000, pVnode, vnodeTmrCtrl, &pVnode->commitTimer);
}