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
struct TYPE_2__ {scalar_t__ cmdIndex; int /*<<< orphan*/  state; int /*<<< orphan*/  sql; int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 scalar_t__ MONITOR_CMD_MAX ; 
 int /*<<< orphan*/  MONITOR_STATE_INITIALIZED ; 
 int /*<<< orphan*/  dnodeBuildMonitorSql (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* monitor ; 
 int /*<<< orphan*/  monitorInitDatabaseCb ; 
 int /*<<< orphan*/  monitorPrint (char*) ; 
 int /*<<< orphan*/  monitorStartTimer () ; 
 int /*<<< orphan*/  taos_query_a (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void monitorInitDatabase() {
  if (monitor->cmdIndex < MONITOR_CMD_MAX) {
    dnodeBuildMonitorSql(monitor->sql, monitor->cmdIndex);
    taos_query_a(monitor->conn, monitor->sql, monitorInitDatabaseCb, NULL);
  } else {
    monitor->state = MONITOR_STATE_INITIALIZED;
    monitorPrint("monitor service init success");

    monitorStartTimer();
  }
}