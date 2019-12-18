#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; int num; scalar_t__ equalVnodeNum; scalar_t__ curNum; int /*<<< orphan*/  stopFp; int /*<<< orphan*/  startFp; int /*<<< orphan*/  cleanUpFp; int /*<<< orphan*/  initFp; } ;

/* Variables and functions */
 size_t TSDB_MOD_HTTP ; 
 size_t TSDB_MOD_MGMT ; 
 size_t TSDB_MOD_MONITOR ; 
 int /*<<< orphan*/  httpCleanUpSystem ; 
 int /*<<< orphan*/  httpInitSystem ; 
 int /*<<< orphan*/  httpStartSystem ; 
 int /*<<< orphan*/  httpStopSystem ; 
 int /*<<< orphan*/  mgmtCleanUpSystem ; 
 int /*<<< orphan*/  mgmtInitSystem ; 
 int /*<<< orphan*/  mgmtStartSystem ; 
 int /*<<< orphan*/  mgmtStopSystem ; 
 int /*<<< orphan*/  monitorCleanUpSystem ; 
 int /*<<< orphan*/  monitorInitSystem ; 
 int /*<<< orphan*/  monitorStartSystem ; 
 int /*<<< orphan*/  monitorStopSystem ; 
 int tsEnableHttpModule ; 
 int tsEnableMonitorModule ; 
 scalar_t__ tsMgmtEqualVnodeNum ; 
 TYPE_1__* tsModule ; 
 int tsNumOfMPeers ; 

void dnodeInitModules() {
  tsModule[TSDB_MOD_MGMT].name = "mgmt";
  tsModule[TSDB_MOD_MGMT].initFp = mgmtInitSystem;
  tsModule[TSDB_MOD_MGMT].cleanUpFp = mgmtCleanUpSystem;
  tsModule[TSDB_MOD_MGMT].startFp = mgmtStartSystem;
  tsModule[TSDB_MOD_MGMT].stopFp = mgmtStopSystem;
  tsModule[TSDB_MOD_MGMT].num = tsNumOfMPeers;
  tsModule[TSDB_MOD_MGMT].curNum = 0;
  tsModule[TSDB_MOD_MGMT].equalVnodeNum = tsMgmtEqualVnodeNum;

  tsModule[TSDB_MOD_HTTP].name = "http";
  tsModule[TSDB_MOD_HTTP].initFp = httpInitSystem;
  tsModule[TSDB_MOD_HTTP].cleanUpFp = httpCleanUpSystem;
  tsModule[TSDB_MOD_HTTP].startFp = httpStartSystem;
  tsModule[TSDB_MOD_HTTP].stopFp = httpStopSystem;
  tsModule[TSDB_MOD_HTTP].num = (tsEnableHttpModule == 1) ? -1 : 0;
  tsModule[TSDB_MOD_HTTP].curNum = 0;
  tsModule[TSDB_MOD_HTTP].equalVnodeNum = 0;

  tsModule[TSDB_MOD_MONITOR].name = "monitor";
  tsModule[TSDB_MOD_MONITOR].initFp = monitorInitSystem;
  tsModule[TSDB_MOD_MONITOR].cleanUpFp = monitorCleanUpSystem;
  tsModule[TSDB_MOD_MONITOR].startFp = monitorStartSystem;
  tsModule[TSDB_MOD_MONITOR].stopFp = monitorStopSystem;
  tsModule[TSDB_MOD_MONITOR].num = (tsEnableMonitorModule == 1) ? -1 : 0;
  tsModule[TSDB_MOD_MONITOR].curNum = 0;
  tsModule[TSDB_MOD_MONITOR].equalVnodeNum = 0;
}