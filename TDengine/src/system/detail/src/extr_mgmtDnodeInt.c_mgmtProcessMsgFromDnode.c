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
typedef  int /*<<< orphan*/  SIntMsg ;
typedef  int /*<<< orphan*/  SDnodeObj ;

/* Variables and functions */
 int TSDB_MSG_TYPE_ALTER_STREAM_RSP ; 
 int TSDB_MSG_TYPE_CFG_PNODE_RSP ; 
 int TSDB_MSG_TYPE_CREATE_RSP ; 
 int TSDB_MSG_TYPE_FREE_VNODE_RSP ; 
 int TSDB_MSG_TYPE_METER_CFG ; 
 int TSDB_MSG_TYPE_REMOVE_RSP ; 
 int TSDB_MSG_TYPE_VPEERS_RSP ; 
 int TSDB_MSG_TYPE_VPEER_CFG ; 
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmtProcessCreateRsp (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmtProcessFreeVnodeRsp (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmtProcessMeterCfgMsg (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmtProcessVPeersRsp (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmtProcessVpeerCfgMsg (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taosMsg ; 

void mgmtProcessMsgFromDnode(char *content, int msgLen, int msgType, SDnodeObj *pObj) {
  if (msgType == TSDB_MSG_TYPE_METER_CFG) {
    mgmtProcessMeterCfgMsg(content, msgLen - sizeof(SIntMsg), pObj);
  } else if (msgType == TSDB_MSG_TYPE_VPEER_CFG) {
    mgmtProcessVpeerCfgMsg(content, msgLen - sizeof(SIntMsg), pObj);
  } else if (msgType == TSDB_MSG_TYPE_CREATE_RSP) {
    mgmtProcessCreateRsp(content, msgLen - sizeof(SIntMsg), pObj);
  } else if (msgType == TSDB_MSG_TYPE_REMOVE_RSP) {
    // do nothing
  } else if (msgType == TSDB_MSG_TYPE_VPEERS_RSP) {
    mgmtProcessVPeersRsp(content, msgLen - sizeof(SIntMsg), pObj);
  } else if (msgType == TSDB_MSG_TYPE_FREE_VNODE_RSP) {
    mgmtProcessFreeVnodeRsp(content, msgLen - sizeof(SIntMsg), pObj);
  } else if (msgType == TSDB_MSG_TYPE_CFG_PNODE_RSP) {
    // do nothing;
  } else if (msgType == TSDB_MSG_TYPE_ALTER_STREAM_RSP) {
    // do nothing;
  } else {
    mError("%s from dnode is not processed", taosMsg[msgType]);
  }
}