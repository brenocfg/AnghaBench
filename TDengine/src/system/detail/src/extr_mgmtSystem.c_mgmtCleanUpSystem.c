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
 int TSDB_MOD_MGMT ; 
 int /*<<< orphan*/  mTrace (char*) ; 
 int /*<<< orphan*/  mgmtCleanUpAccts () ; 
 int /*<<< orphan*/  mgmtCleanUpDbs () ; 
 int /*<<< orphan*/  mgmtCleanUpDnodeInt () ; 
 int /*<<< orphan*/  mgmtCleanUpDnodes () ; 
 int /*<<< orphan*/  mgmtCleanUpMeters () ; 
 int /*<<< orphan*/  mgmtCleanUpRedirect () ; 
 int /*<<< orphan*/  mgmtCleanUpShell () ; 
 int /*<<< orphan*/  mgmtCleanUpUsers () ; 
 int /*<<< orphan*/  mgmtCleanUpVgroups () ; 
 int /*<<< orphan*/  mgmtCleanupBalance () ; 
 scalar_t__ mgmtDnodeConns ; 
 int /*<<< orphan*/ * mgmtQhandle ; 
 scalar_t__ mgmtShellConns ; 
 int /*<<< orphan*/  mgmtStatisticTimer ; 
 int /*<<< orphan*/ * mgmtTmr ; 
 int /*<<< orphan*/ * mgmtTranQhandle ; 
 int /*<<< orphan*/ * pShellConn ; 
 int /*<<< orphan*/  sdbCleanUpPeers () ; 
 int /*<<< orphan*/  taosCleanUpScheduler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosTmrCleanUp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosTmrStopA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tclearModuleStatus (int) ; 
 int tsModuleStatus ; 

void mgmtCleanUpSystem() {
  if (tsModuleStatus & (1 << TSDB_MOD_MGMT)) {
    mTrace("mgmt is running, clean it up");
    taosTmrStopA(&mgmtStatisticTimer);
    sdbCleanUpPeers();
    mgmtCleanupBalance();
    mgmtCleanUpDnodeInt();
    mgmtCleanUpShell();
    mgmtCleanUpMeters();
    mgmtCleanUpVgroups();
    mgmtCleanUpDbs();
    mgmtCleanUpDnodes();
    mgmtCleanUpUsers();
    mgmtCleanUpAccts();
    taosTmrCleanUp(mgmtTmr);
    taosCleanUpScheduler(mgmtQhandle);
    taosCleanUpScheduler(mgmtTranQhandle);
  } else {
    mgmtCleanUpRedirect();
  }

  mgmtTmr = NULL;
  mgmtQhandle = NULL;
  mgmtShellConns = 0;
  mgmtDnodeConns = 0;
  tclearModuleStatus(TSDB_MOD_MGMT);
  pShellConn = NULL;

  mTrace("mgmt is cleaned up");
}