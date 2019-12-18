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
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 TYPE_1__* monitor ; 
 int /*<<< orphan*/  monitorTrace (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taos_query_a (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void monitorExecuteSQL(char *sql) {
  monitorTrace("monitor:%p, execute sql: %s", monitor->conn, sql);
  taos_query_a(monitor->conn, sql, NULL, NULL);
}