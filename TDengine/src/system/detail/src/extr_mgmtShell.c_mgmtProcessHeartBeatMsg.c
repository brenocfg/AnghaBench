#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int numOfIps; int /*<<< orphan*/  ip; } ;
struct TYPE_11__ {int /*<<< orphan*/  thandle; int /*<<< orphan*/  killConnection; scalar_t__ streamId; scalar_t__ queryId; } ;
struct TYPE_8__ {int numOfIps; int /*<<< orphan*/  ip; } ;
struct TYPE_10__ {TYPE_1__ ipList; int /*<<< orphan*/  killConnection; scalar_t__ streamId; scalar_t__ queryId; } ;
struct TYPE_9__ {scalar_t__ more; scalar_t__ code; } ;
typedef  TYPE_2__ STaosRsp ;
typedef  TYPE_3__ SHeartBeatRsp ;
typedef  TYPE_4__ SConnObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_HEARTBEAT_RSP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmtSaveQueryStreamList (char*,int,TYPE_4__*) ; 
 TYPE_5__* pSdbPublicIpList ; 
 char* taosBuildRspMsgWithSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taosSendMsgToPeer (int /*<<< orphan*/ ,char*,int) ; 

int mgmtProcessHeartBeatMsg(char *cont, int contLen, SConnObj *pConn) {
  char *    pStart, *pMsg;
  int       msgLen;
  STaosRsp *pRsp;

  mgmtSaveQueryStreamList(cont, contLen, pConn);

  pStart = taosBuildRspMsgWithSize(pConn->thandle, TSDB_MSG_TYPE_HEARTBEAT_RSP, 128);
  if (pStart == NULL) return 0;
  pMsg = pStart;
  pRsp = (STaosRsp *)pMsg;
  pRsp->code = 0;
  pMsg = (char *)pRsp->more;

  SHeartBeatRsp *pHBRsp = (SHeartBeatRsp *)pRsp->more;
  pHBRsp->queryId = pConn->queryId;
  pConn->queryId = 0;
  pHBRsp->streamId = pConn->streamId;
  pHBRsp->streamId = pConn->streamId;
  pConn->streamId = 0;
  pHBRsp->killConnection = pConn->killConnection;

#ifdef CLUSTER
  int size = pSdbPublicIpList->numOfIps * 4;
  pHBRsp->ipList.numOfIps = pSdbPublicIpList->numOfIps;
  memcpy(pHBRsp->ipList.ip, pSdbPublicIpList->ip, size);
  pMsg += sizeof(SHeartBeatRsp) + size;
#else
  pMsg += sizeof(SHeartBeatRsp);
#endif
  msgLen = pMsg - pStart;

  taosSendMsgToPeer(pConn->thandle, pStart, msgLen);

  return 0;
}