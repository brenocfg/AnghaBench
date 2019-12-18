#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int TSDB_MAX_VNODES ; 
 int /*<<< orphan*/  dPrint (char*) ; 
 int /*<<< orphan*/  mgmtStopSystem () ; 
 int /*<<< orphan*/  vnodeRemoveVnode (int) ; 

void dnodeResetSystem() {
  dPrint("reset the system ...");
  for (int vnode = 0; vnode < TSDB_MAX_VNODES; ++vnode) vnodeRemoveVnode(vnode);
  mgmtStopSystem();
}