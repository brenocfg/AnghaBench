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
typedef  int /*<<< orphan*/  SMgmtObj ;

/* Variables and functions */
 int TSDB_MSG_TYPE_ALTER_STREAM ; 
 int TSDB_MSG_TYPE_CFG_PNODE ; 
 int TSDB_MSG_TYPE_CREATE ; 
 int TSDB_MSG_TYPE_FREE_VNODE ; 
 int TSDB_MSG_TYPE_GRANT_RSP ; 
 int TSDB_MSG_TYPE_METER_CFG_RSP ; 
 int TSDB_MSG_TYPE_REMOVE ; 
 int TSDB_MSG_TYPE_VPEERS ; 
 int TSDB_MSG_TYPE_VPEER_CFG_RSP ; 
 int /*<<< orphan*/  dError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taosMsg ; 
 int /*<<< orphan*/  vnodeProcessAlterStreamRequest (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeProcessCfgDnodeRequest (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeProcessCreateMeterRequest (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeProcessFreeVnodeRequest (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeProcessMeterCfgRsp (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeProcessRemoveMeterRequest (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeProcessVPeerCfgRsp (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeProcessVPeersMsg (char*,int,int /*<<< orphan*/ *) ; 

void vnodeProcessMsgFromMgmt(char *content, int msgLen, int msgType, SMgmtObj *pObj) {
  if (msgType == TSDB_MSG_TYPE_CREATE) {
    vnodeProcessCreateMeterRequest(content, msgLen, pObj);
  } else if (msgType == TSDB_MSG_TYPE_VPEERS) {
    vnodeProcessVPeersMsg(content, msgLen, pObj);
  } else if (msgType == TSDB_MSG_TYPE_VPEER_CFG_RSP) {
    vnodeProcessVPeerCfgRsp(content, msgLen, pObj);
  } else if (msgType == TSDB_MSG_TYPE_METER_CFG_RSP) {
    vnodeProcessMeterCfgRsp(content, msgLen, pObj);
  } else if (msgType == TSDB_MSG_TYPE_REMOVE) {
    vnodeProcessRemoveMeterRequest(content, msgLen, pObj);
  } else if (msgType == TSDB_MSG_TYPE_FREE_VNODE) {
    vnodeProcessFreeVnodeRequest(content, msgLen, pObj);
  } else if (msgType == TSDB_MSG_TYPE_CFG_PNODE) {
    vnodeProcessCfgDnodeRequest(content, msgLen, pObj);
  } else if (msgType == TSDB_MSG_TYPE_ALTER_STREAM) {
    vnodeProcessAlterStreamRequest(content, msgLen, pObj);
  } else if (msgType == TSDB_MSG_TYPE_GRANT_RSP) {
    // do nothing
  } else {
    dError("%s is not processed", taosMsg[msgType]);
  }
}