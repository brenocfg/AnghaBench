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
struct TYPE_4__ {scalar_t__ maxSessions; } ;
struct TYPE_5__ {TYPE_1__ cfg; } ;
typedef  TYPE_2__ SVnodeObj ;

/* Variables and functions */
 void* vnodeCommitMultiToFile (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

void *vnodeCommitToFile(void *param) {
  SVnodeObj *pVnode = (SVnodeObj *)param;

  return vnodeCommitMultiToFile(pVnode, 0, pVnode->cfg.maxSessions - 1);
}