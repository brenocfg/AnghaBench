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
 size_t TSDB_SQL_ALTER_ACCT ; 
 size_t TSDB_SQL_ALTER_DB ; 
 size_t TSDB_SQL_ALTER_TABLE ; 
 size_t TSDB_SQL_ALTER_USER ; 
 size_t TSDB_SQL_CFG_DNODE ; 
 size_t TSDB_SQL_CONNECT ; 
 size_t TSDB_SQL_CREATE_ACCT ; 
 size_t TSDB_SQL_CREATE_DB ; 
 size_t TSDB_SQL_CREATE_DNODE ; 
 size_t TSDB_SQL_CREATE_TABLE ; 
 size_t TSDB_SQL_CREATE_USER ; 
 size_t TSDB_SQL_DESCRIBE_TABLE ; 
 size_t TSDB_SQL_DROP_ACCT ; 
 size_t TSDB_SQL_DROP_DB ; 
 size_t TSDB_SQL_DROP_DNODE ; 
 size_t TSDB_SQL_DROP_TABLE ; 
 size_t TSDB_SQL_DROP_USER ; 
 size_t TSDB_SQL_FETCH ; 
 size_t TSDB_SQL_HB ; 
 size_t TSDB_SQL_INSERT ; 
 size_t TSDB_SQL_KILL_CONNECTION ; 
 size_t TSDB_SQL_KILL_QUERY ; 
 size_t TSDB_SQL_KILL_STREAM ; 
 size_t TSDB_SQL_META ; 
 size_t TSDB_SQL_METRIC ; 
 size_t TSDB_SQL_MULTI_META ; 
 size_t TSDB_SQL_RETRIEVE ; 
 size_t TSDB_SQL_RETRIEVE_EMPTY_RESULT ; 
 size_t TSDB_SQL_RETRIEVE_METRIC ; 
 size_t TSDB_SQL_RETRIEVE_TAGS ; 
 size_t TSDB_SQL_SELECT ; 
 size_t TSDB_SQL_SHOW ; 
 size_t TSDB_SQL_USE_DB ; 
 int /*<<< orphan*/  tscAlterDbMsg ; 
 int /*<<< orphan*/  tscBuildAlterAcctMsg ; 
 int /*<<< orphan*/  tscBuildAlterTableMsg ; 
 int /*<<< orphan*/  tscBuildAlterUserMsg ; 
 int /*<<< orphan*/  tscBuildCfgDnodeMsg ; 
 int /*<<< orphan*/  tscBuildConnectMsg ; 
 int /*<<< orphan*/  tscBuildCreateAcctMsg ; 
 int /*<<< orphan*/  tscBuildCreateDbMsg ; 
 int /*<<< orphan*/  tscBuildCreateDnodeMsg ; 
 int /*<<< orphan*/  tscBuildCreateTableMsg ; 
 int /*<<< orphan*/  tscBuildCreateUserMsg ; 
 int /*<<< orphan*/  tscBuildDropAcctMsg ; 
 int /*<<< orphan*/  tscBuildDropDbMsg ; 
 int /*<<< orphan*/  tscBuildDropDnodeMsg ; 
 int /*<<< orphan*/  tscBuildDropTableMsg ; 
 int /*<<< orphan*/  tscBuildDropUserMsg ; 
 int /*<<< orphan*/  tscBuildHeartBeatMsg ; 
 int /*<<< orphan*/  tscBuildKillConnectionMsg ; 
 int /*<<< orphan*/  tscBuildKillQueryMsg ; 
 int /*<<< orphan*/  tscBuildKillStreamMsg ; 
 int /*<<< orphan*/  tscBuildMeterMetaMsg ; 
 int /*<<< orphan*/  tscBuildMetricMetaMsg ; 
 int /*<<< orphan*/ * tscBuildMsg ; 
 int /*<<< orphan*/  tscBuildMultiMeterMetaMsg ; 
 int /*<<< orphan*/  tscBuildQueryMsg ; 
 int /*<<< orphan*/  tscBuildRetrieveFromMgmtMsg ; 
 int /*<<< orphan*/  tscBuildRetrieveMsg ; 
 int /*<<< orphan*/  tscBuildShowMsg ; 
 int /*<<< orphan*/  tscBuildSubmitMsg ; 
 int /*<<< orphan*/  tscBuildUseDbMsg ; 
 int* tscKeepConn ; 
 int /*<<< orphan*/  tscProcessAlterDbMsgRsp ; 
 int /*<<< orphan*/  tscProcessAlterTableMsgRsp ; 
 int /*<<< orphan*/  tscProcessConnectRsp ; 
 int /*<<< orphan*/  tscProcessDescribeTableRsp ; 
 int /*<<< orphan*/  tscProcessDropDbRsp ; 
 int /*<<< orphan*/  tscProcessDropTableRsp ; 
 int /*<<< orphan*/  tscProcessEmptyResultRsp ; 
 int /*<<< orphan*/  tscProcessMeterMetaRsp ; 
 int /*<<< orphan*/  tscProcessMetricMetaRsp ; 
 int /*<<< orphan*/ * tscProcessMsgRsp ; 
 int /*<<< orphan*/  tscProcessMultiMeterMetaRsp ; 
 int /*<<< orphan*/  tscProcessQueryRsp ; 
 int /*<<< orphan*/  tscProcessRetrieveMetricRsp ; 
 int /*<<< orphan*/  tscProcessRetrieveRspFromMgmt ; 
 int /*<<< orphan*/  tscProcessRetrieveRspFromVnode ; 
 int /*<<< orphan*/  tscProcessShowRsp ; 
 int /*<<< orphan*/  tscProcessTagRetrieveRsp ; 
 int /*<<< orphan*/  tscProcessUseDbRsp ; 
 int /*<<< orphan*/  tscUpdateVnodeInQueryMsg ; 
 int /*<<< orphan*/  tscUpdateVnodeInSubmitMsg ; 
 int /*<<< orphan*/ * tscUpdateVnodeMsg ; 

void tscInitMsgs() {
  tscBuildMsg[TSDB_SQL_SELECT] = tscBuildQueryMsg;
  tscBuildMsg[TSDB_SQL_INSERT] = tscBuildSubmitMsg;
  tscBuildMsg[TSDB_SQL_FETCH] = tscBuildRetrieveMsg;

  tscBuildMsg[TSDB_SQL_CREATE_DB] = tscBuildCreateDbMsg;
  tscBuildMsg[TSDB_SQL_CREATE_USER] = tscBuildCreateUserMsg;

  tscBuildMsg[TSDB_SQL_CREATE_ACCT] = tscBuildCreateAcctMsg;
  tscBuildMsg[TSDB_SQL_ALTER_ACCT] = tscBuildAlterAcctMsg;

  tscBuildMsg[TSDB_SQL_CREATE_TABLE] = tscBuildCreateTableMsg;
  tscBuildMsg[TSDB_SQL_DROP_USER] = tscBuildDropUserMsg;
  tscBuildMsg[TSDB_SQL_DROP_ACCT] = tscBuildDropAcctMsg;
  tscBuildMsg[TSDB_SQL_DROP_DB] = tscBuildDropDbMsg;
  tscBuildMsg[TSDB_SQL_DROP_TABLE] = tscBuildDropTableMsg;
  tscBuildMsg[TSDB_SQL_ALTER_USER] = tscBuildAlterUserMsg;
  tscBuildMsg[TSDB_SQL_CREATE_DNODE] = tscBuildCreateDnodeMsg;
  tscBuildMsg[TSDB_SQL_DROP_DNODE] = tscBuildDropDnodeMsg;
  tscBuildMsg[TSDB_SQL_CFG_DNODE] = tscBuildCfgDnodeMsg;
  tscBuildMsg[TSDB_SQL_ALTER_TABLE] = tscBuildAlterTableMsg;
  tscBuildMsg[TSDB_SQL_ALTER_DB] = tscAlterDbMsg;

  tscBuildMsg[TSDB_SQL_CONNECT] = tscBuildConnectMsg;
  tscBuildMsg[TSDB_SQL_USE_DB] = tscBuildUseDbMsg;
  tscBuildMsg[TSDB_SQL_META] = tscBuildMeterMetaMsg;
  tscBuildMsg[TSDB_SQL_METRIC] = tscBuildMetricMetaMsg;
  tscBuildMsg[TSDB_SQL_MULTI_META] = tscBuildMultiMeterMetaMsg;

  tscBuildMsg[TSDB_SQL_HB] = tscBuildHeartBeatMsg;
  tscBuildMsg[TSDB_SQL_SHOW] = tscBuildShowMsg;
  tscBuildMsg[TSDB_SQL_RETRIEVE] = tscBuildRetrieveFromMgmtMsg;
  tscBuildMsg[TSDB_SQL_KILL_QUERY] = tscBuildKillQueryMsg;
  tscBuildMsg[TSDB_SQL_KILL_STREAM] = tscBuildKillStreamMsg;
  tscBuildMsg[TSDB_SQL_KILL_CONNECTION] = tscBuildKillConnectionMsg;

  tscProcessMsgRsp[TSDB_SQL_SELECT] = tscProcessQueryRsp;
  tscProcessMsgRsp[TSDB_SQL_FETCH] = tscProcessRetrieveRspFromVnode;

  tscProcessMsgRsp[TSDB_SQL_DROP_DB] = tscProcessDropDbRsp;
  tscProcessMsgRsp[TSDB_SQL_DROP_TABLE] = tscProcessDropTableRsp;
  tscProcessMsgRsp[TSDB_SQL_CONNECT] = tscProcessConnectRsp;
  tscProcessMsgRsp[TSDB_SQL_USE_DB] = tscProcessUseDbRsp;
  tscProcessMsgRsp[TSDB_SQL_META] = tscProcessMeterMetaRsp;
  tscProcessMsgRsp[TSDB_SQL_METRIC] = tscProcessMetricMetaRsp;
  tscProcessMsgRsp[TSDB_SQL_MULTI_META] = tscProcessMultiMeterMetaRsp;

  tscProcessMsgRsp[TSDB_SQL_SHOW] = tscProcessShowRsp;
  tscProcessMsgRsp[TSDB_SQL_RETRIEVE] = tscProcessRetrieveRspFromMgmt;
  tscProcessMsgRsp[TSDB_SQL_DESCRIBE_TABLE] = tscProcessDescribeTableRsp;
  tscProcessMsgRsp[TSDB_SQL_RETRIEVE_TAGS] = tscProcessTagRetrieveRsp;
  tscProcessMsgRsp[TSDB_SQL_RETRIEVE_EMPTY_RESULT] = tscProcessEmptyResultRsp;

  tscProcessMsgRsp[TSDB_SQL_RETRIEVE_METRIC] = tscProcessRetrieveMetricRsp;

  tscProcessMsgRsp[TSDB_SQL_ALTER_TABLE] = tscProcessAlterTableMsgRsp;
  tscProcessMsgRsp[TSDB_SQL_ALTER_DB] = tscProcessAlterDbMsgRsp;

  tscKeepConn[TSDB_SQL_SHOW] = 1;
  tscKeepConn[TSDB_SQL_RETRIEVE] = 1;
  tscKeepConn[TSDB_SQL_SELECT] = 1;
  tscKeepConn[TSDB_SQL_FETCH] = 1;
  tscKeepConn[TSDB_SQL_HB] = 1;

  tscUpdateVnodeMsg[TSDB_SQL_SELECT] = tscUpdateVnodeInQueryMsg;
  tscUpdateVnodeMsg[TSDB_SQL_INSERT] = tscUpdateVnodeInSubmitMsg;
}