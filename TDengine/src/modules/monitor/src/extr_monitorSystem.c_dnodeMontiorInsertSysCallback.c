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
struct TYPE_2__ {int /*<<< orphan*/  sql; int /*<<< orphan*/  conn; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;

/* Variables and functions */
 TYPE_1__* monitor ; 
 int /*<<< orphan*/  monitorError (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitorTrace (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void dnodeMontiorInsertSysCallback(void *param, TAOS_RES *result, int code) {
  if (code < 0) {
    monitorError("monitor:%p, save system info failed, code:%d %s", monitor->conn, code, monitor->sql);
  } else if (code == 0) {
    monitorError("monitor:%p, save system info failed, affect rows:%d %s", monitor->conn, code, monitor->sql);
  } else {
    monitorTrace("monitor:%p, save system info success, code:%d %s", monitor->conn, code, monitor->sql);
  }
}