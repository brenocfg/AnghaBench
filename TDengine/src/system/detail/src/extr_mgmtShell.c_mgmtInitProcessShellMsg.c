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
 size_t TSDB_MSG_TYPE_ALTER_ACCT ; 
 size_t TSDB_MSG_TYPE_ALTER_DB ; 
 size_t TSDB_MSG_TYPE_ALTER_TABLE ; 
 size_t TSDB_MSG_TYPE_ALTER_USER ; 
 size_t TSDB_MSG_TYPE_CFG_MNODE ; 
 size_t TSDB_MSG_TYPE_CFG_PNODE ; 
 size_t TSDB_MSG_TYPE_CONNECT ; 
 size_t TSDB_MSG_TYPE_CREATE_ACCT ; 
 size_t TSDB_MSG_TYPE_CREATE_DB ; 
 size_t TSDB_MSG_TYPE_CREATE_MNODE ; 
 size_t TSDB_MSG_TYPE_CREATE_PNODE ; 
 size_t TSDB_MSG_TYPE_CREATE_TABLE ; 
 size_t TSDB_MSG_TYPE_CREATE_USER ; 
 size_t TSDB_MSG_TYPE_DROP_ACCT ; 
 size_t TSDB_MSG_TYPE_DROP_DB ; 
 size_t TSDB_MSG_TYPE_DROP_MNODE ; 
 size_t TSDB_MSG_TYPE_DROP_PNODE ; 
 size_t TSDB_MSG_TYPE_DROP_TABLE ; 
 size_t TSDB_MSG_TYPE_DROP_USER ; 
 size_t TSDB_MSG_TYPE_HEARTBEAT ; 
 size_t TSDB_MSG_TYPE_KILL_CONNECTION ; 
 size_t TSDB_MSG_TYPE_KILL_QUERY ; 
 size_t TSDB_MSG_TYPE_KILL_STREAM ; 
 size_t TSDB_MSG_TYPE_METERINFO ; 
 size_t TSDB_MSG_TYPE_METRIC_META ; 
 size_t TSDB_MSG_TYPE_MULTI_METERINFO ; 
 size_t TSDB_MSG_TYPE_RETRIEVE ; 
 size_t TSDB_MSG_TYPE_SHOW ; 
 size_t TSDB_MSG_TYPE_USE_DB ; 
 int /*<<< orphan*/  mgmtProcessAlterAcctMsg ; 
 int /*<<< orphan*/  mgmtProcessAlterDbMsg ; 
 int /*<<< orphan*/  mgmtProcessAlterTableMsg ; 
 int /*<<< orphan*/  mgmtProcessAlterUserMsg ; 
 int /*<<< orphan*/  mgmtProcessCfgDnodeMsg ; 
 int /*<<< orphan*/  mgmtProcessCfgMnodeMsg ; 
 int /*<<< orphan*/  mgmtProcessConnectMsg ; 
 int /*<<< orphan*/  mgmtProcessCreateAcctMsg ; 
 int /*<<< orphan*/  mgmtProcessCreateDbMsg ; 
 int /*<<< orphan*/  mgmtProcessCreateDnodeMsg ; 
 int /*<<< orphan*/  mgmtProcessCreateMnodeMsg ; 
 int /*<<< orphan*/  mgmtProcessCreateTableMsg ; 
 int /*<<< orphan*/  mgmtProcessCreateUserMsg ; 
 int /*<<< orphan*/  mgmtProcessDropAcctMsg ; 
 int /*<<< orphan*/  mgmtProcessDropDbMsg ; 
 int /*<<< orphan*/  mgmtProcessDropDnodeMsg ; 
 int /*<<< orphan*/  mgmtProcessDropMnodeMsg ; 
 int /*<<< orphan*/  mgmtProcessDropTableMsg ; 
 int /*<<< orphan*/  mgmtProcessDropUserMsg ; 
 int /*<<< orphan*/  mgmtProcessHeartBeatMsg ; 
 int /*<<< orphan*/  mgmtProcessKillConnectionMsg ; 
 int /*<<< orphan*/  mgmtProcessKillQueryMsg ; 
 int /*<<< orphan*/  mgmtProcessKillStreamMsg ; 
 int /*<<< orphan*/  mgmtProcessMeterMetaMsg ; 
 int /*<<< orphan*/  mgmtProcessMetricMetaMsg ; 
 int /*<<< orphan*/  mgmtProcessMultiMeterMetaMsg ; 
 int /*<<< orphan*/  mgmtProcessRetrieveMsg ; 
 int /*<<< orphan*/ * mgmtProcessShellMsg ; 
 int /*<<< orphan*/  mgmtProcessShowMsg ; 
 int /*<<< orphan*/  mgmtProcessUseDbMsg ; 

void mgmtInitProcessShellMsg() {
  mgmtProcessShellMsg[TSDB_MSG_TYPE_METERINFO] = mgmtProcessMeterMetaMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_METRIC_META] = mgmtProcessMetricMetaMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_MULTI_METERINFO] = mgmtProcessMultiMeterMetaMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_CREATE_DB] = mgmtProcessCreateDbMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_ALTER_DB] = mgmtProcessAlterDbMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_CREATE_USER] = mgmtProcessCreateUserMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_ALTER_USER] = mgmtProcessAlterUserMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_CREATE_ACCT] = mgmtProcessCreateAcctMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_DROP_DB] = mgmtProcessDropDbMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_DROP_USER] = mgmtProcessDropUserMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_DROP_ACCT] = mgmtProcessDropAcctMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_ALTER_ACCT] = mgmtProcessAlterAcctMsg;

  mgmtProcessShellMsg[TSDB_MSG_TYPE_CREATE_TABLE] = mgmtProcessCreateTableMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_DROP_TABLE] = mgmtProcessDropTableMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_ALTER_TABLE] = mgmtProcessAlterTableMsg;

  mgmtProcessShellMsg[TSDB_MSG_TYPE_USE_DB] = mgmtProcessUseDbMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_RETRIEVE] = mgmtProcessRetrieveMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_SHOW] = mgmtProcessShowMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_CONNECT] = mgmtProcessConnectMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_HEARTBEAT] = mgmtProcessHeartBeatMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_CREATE_PNODE] = mgmtProcessCreateDnodeMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_DROP_PNODE] = mgmtProcessDropDnodeMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_CREATE_MNODE] = mgmtProcessCreateMnodeMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_DROP_MNODE] = mgmtProcessDropMnodeMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_CFG_MNODE] = mgmtProcessCfgMnodeMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_CFG_PNODE] = mgmtProcessCfgDnodeMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_KILL_QUERY] = mgmtProcessKillQueryMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_KILL_STREAM] = mgmtProcessKillStreamMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_KILL_CONNECTION] = mgmtProcessKillConnectionMsg;
}