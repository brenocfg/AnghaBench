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
 int /*<<< orphan*/  dError (char*) ; 
 int /*<<< orphan*/ * taosTmrInit (scalar_t__,int,int,char*) ; 
 scalar_t__ tsSessionsPerVnode ; 
 int tsVnodePeers ; 
 int /*<<< orphan*/ * vnodeTmrCtrl ; 

bool vnodeInitTmrCtl() {
  vnodeTmrCtrl = taosTmrInit(TSDB_MAX_VNODES * (tsVnodePeers + 10) + tsSessionsPerVnode + 1000, 200, 60000, "DND-vnode");
  if (vnodeTmrCtrl == NULL) {
    dError("failed to init timer, exit");
    return false;
  }
  return true;
}