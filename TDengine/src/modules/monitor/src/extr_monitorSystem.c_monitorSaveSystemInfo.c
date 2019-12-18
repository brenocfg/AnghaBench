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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_2__ {scalar_t__ state; char* sql; char* privateIpStr; int /*<<< orphan*/ * timer; int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 scalar_t__ MONITOR_STATE_INITIALIZED ; 
 scalar_t__ MONITOR_STATE_STOPPED ; 
 int /*<<< orphan*/  SQL_LENGTH ; 
 int /*<<< orphan*/  dnodeMontiorInsertSysCallback ; 
 TYPE_1__* monitor ; 
 scalar_t__ monitorBuildBandSql (char*) ; 
 scalar_t__ monitorBuildCpuSql (char*) ; 
 scalar_t__ monitorBuildDiskSql (char*) ; 
 scalar_t__ monitorBuildIoSql (char*) ; 
 scalar_t__ monitorBuildMemorySql (char*) ; 
 scalar_t__ monitorBuildReqSql (char*) ; 
 int /*<<< orphan*/ * monitorCountReqFp ; 
 int /*<<< orphan*/  monitorStartTimer () ; 
 int /*<<< orphan*/  monitorTrace (char*,int /*<<< orphan*/ ,char*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosGetTimestampUs () ; 
 int /*<<< orphan*/  taos_query_a (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 char* tsMonitorDbName ; 

void monitorSaveSystemInfo() {
  if (monitor->state != MONITOR_STATE_INITIALIZED) {
    return;
  }

  if (monitorCountReqFp == NULL) {
    return;
  }

  int64_t ts = taosGetTimestampUs();
  char *  sql = monitor->sql;
  int pos = snprintf(sql, SQL_LENGTH, "insert into %s.dn_%s values(%ld", tsMonitorDbName, monitor->privateIpStr, ts);

  pos += monitorBuildCpuSql(sql + pos);
  pos += monitorBuildMemorySql(sql + pos);
  pos += monitorBuildDiskSql(sql + pos);
  pos += monitorBuildBandSql(sql + pos);
  pos += monitorBuildIoSql(sql + pos);
  pos += monitorBuildReqSql(sql + pos);

  monitorTrace("monitor:%p, save system info, sql:%s", monitor->conn, sql);
  taos_query_a(monitor->conn, sql, dnodeMontiorInsertSysCallback, "log");

  if (monitor->timer != NULL && monitor->state != MONITOR_STATE_STOPPED) {
    monitorStartTimer();
  }
}