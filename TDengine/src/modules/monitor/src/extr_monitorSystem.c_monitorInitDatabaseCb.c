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
typedef  int /*<<< orphan*/  TAOS_RES ;

/* Variables and functions */
 scalar_t__ MONITOR_CMD_CREATE_TB_LOG ; 
 int /*<<< orphan*/  MONITOR_STATE_UN_INIT ; 
 int TSDB_CODE_DB_ALREADY_EXIST ; 
 int TSDB_CODE_TABLE_ALREADY_EXIST ; 
 TYPE_1__* monitor ; 
 int /*<<< orphan*/  monitorError (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitorExecuteSQL ; 
 int /*<<< orphan*/  monitorInitDatabase () ; 
 int /*<<< orphan*/  monitorLPrint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitorSaveAcctLog ; 
 int /*<<< orphan*/  monitorSaveLog ; 
 int /*<<< orphan*/  monitorStartSystemRetry () ; 
 int /*<<< orphan*/  monitorTrace (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosLogAcctFp ; 
 int /*<<< orphan*/  taosLogFp ; 
 int /*<<< orphan*/  taosLogSqlFp ; 
 int /*<<< orphan*/  tsInternalIp ; 
 int /*<<< orphan*/  tsPrivateIp ; 

void monitorInitDatabaseCb(void *param, TAOS_RES *result, int code) {
  if (-code == TSDB_CODE_TABLE_ALREADY_EXIST || -code == TSDB_CODE_DB_ALREADY_EXIST || code >= 0) {
    monitorTrace("monitor:%p, sql success, code:%d, %s", monitor->conn, code, monitor->sql);
    if (monitor->cmdIndex == MONITOR_CMD_CREATE_TB_LOG) {
      taosLogFp = monitorSaveLog;
      taosLogSqlFp = monitorExecuteSQL;
#ifdef CLUSTER
      taosLogAcctFp = monitorSaveAcctLog;
      monitorLPrint("dnode:%s is started", tsPrivateIp);
#else
      monitorLPrint("dnode:%s is started", tsInternalIp);
#endif
    }
    monitor->cmdIndex++;
    monitorInitDatabase();
  } else {
    monitorError("monitor:%p, sql failed, code:%d, %s", monitor->conn, code, monitor->sql);
    monitor->state = MONITOR_STATE_UN_INIT;
    monitorStartSystemRetry();
  }
}