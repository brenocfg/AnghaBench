#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  connInit ;
struct TYPE_25__ {TYPE_2__* vpeerDesc; } ;
struct TYPE_24__ {TYPE_8__* pMeterMeta; int /*<<< orphan*/  pMetricMeta; } ;
struct TYPE_23__ {int cid; char* peerIp; void* peerPort; TYPE_4__* ahandle; void* shandle; void* peerId; int /*<<< orphan*/  meterId; scalar_t__ encrypt; scalar_t__ spi; scalar_t__ sid; } ;
struct TYPE_22__ {int /*<<< orphan*/  vnodeIdx; } ;
struct TYPE_21__ {scalar_t__ retry; scalar_t__ maxRetry; size_t index; scalar_t__ ip; int vnode; int /*<<< orphan*/ * thandle; TYPE_3__* pTscObj; TYPE_5__ cmd; } ;
struct TYPE_20__ {int /*<<< orphan*/  user; } ;
struct TYPE_19__ {scalar_t__ ip; int vnode; } ;
struct TYPE_18__ {TYPE_2__* vpeerDesc; } ;
typedef  TYPE_1__ SVnodeSidList ;
typedef  TYPE_2__ SVPeerDesc ;
typedef  TYPE_3__ STscObj ;
typedef  TYPE_4__ SSqlObj ;
typedef  TYPE_5__ SSqlCmd ;
typedef  TYPE_6__ SRpcConnInit ;
typedef  TYPE_7__ SMeterMetaInfo ;
typedef  TYPE_8__ SMeterMeta ;

/* Variables and functions */
 int TSDB_SHELL_VNODE_BITS ; 
 int TSDB_VNODES_SUPPORT ; 
 scalar_t__ UTIL_METER_IS_METRIC (TYPE_7__*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 void* pVnodeConn ; 
 void* taosGetConnFromCache (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 void* taosOpenRpcConn (TYPE_6__*,scalar_t__*) ; 
 int /*<<< orphan*/  tinet_ntoa (char*,scalar_t__) ; 
 scalar_t__ tsServerIp ; 
 char* tsServerIpStr ; 
 void* tsVnodeShellPort ; 
 int /*<<< orphan*/  tscConnCache ; 
 int /*<<< orphan*/  tscError (char*,TYPE_4__*) ; 
 TYPE_7__* tscGetMeterMetaInfo (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* tscGetVnodeSidList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tscNumOfThreads ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_4__*,int,scalar_t__,size_t,int /*<<< orphan*/ *) ; 

void tscGetConnToVnode(SSqlObj *pSql, uint8_t *pCode) {
  char        ipstr[40] = {0};
  SVPeerDesc *pVPeersDesc = NULL;
  static int  vidIndex = 0;
  STscObj *   pTscObj = pSql->pTscObj;

  pSql->thandle = NULL;

  SSqlCmd *       pCmd = &pSql->cmd;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  if (UTIL_METER_IS_METRIC(pMeterMetaInfo)) {  // multiple vnode query
    SVnodeSidList *vnodeList = tscGetVnodeSidList(pMeterMetaInfo->pMetricMeta, pCmd->vnodeIdx);
    if (vnodeList != NULL) {
      pVPeersDesc = vnodeList->vpeerDesc;
    }
  } else {
    SMeterMeta *pMeta = pMeterMetaInfo->pMeterMeta;
    if (pMeta == NULL) {
      tscError("%p pMeterMeta is NULL", pSql);
      pSql->retry = pSql->maxRetry;
      return;
    }
    pVPeersDesc = pMeta->vpeerDesc;
  }

  if (pVPeersDesc == NULL) {
    pSql->retry = pSql->maxRetry;
    tscError("%p pVPeerDesc is NULL", pSql);
  }

  while (pSql->retry < pSql->maxRetry) {
    (pSql->retry)++;
#ifdef CLUSTER
    if (pVPeersDesc[pSql->index].ip == 0) {
      (pSql->index) = (pSql->index + 1) % TSDB_VNODES_SUPPORT;
      continue;
    }
    *pCode = 0;

    void *thandle =
        taosGetConnFromCache(tscConnCache, pVPeersDesc[pSql->index].ip, pVPeersDesc[pSql->index].vnode, pTscObj->user);

    if (thandle == NULL) {
      SRpcConnInit connInit;
      tinet_ntoa(ipstr, pVPeersDesc[pSql->index].ip);
      memset(&connInit, 0, sizeof(connInit));
      connInit.cid = vidIndex;
      connInit.sid = 0;
      connInit.spi = 0;
      connInit.encrypt = 0;
      connInit.meterId = pSql->pTscObj->user;
      connInit.peerId = htonl((pVPeersDesc[pSql->index].vnode << TSDB_SHELL_VNODE_BITS));
      connInit.shandle = pVnodeConn;
      connInit.ahandle = pSql;
      connInit.peerIp = ipstr;
      connInit.peerPort = tsVnodeShellPort;
      thandle = taosOpenRpcConn(&connInit, pCode);
      vidIndex = (vidIndex + 1) % tscNumOfThreads;
    }

    pSql->thandle = thandle;
    pSql->ip = pVPeersDesc[pSql->index].ip;
    pSql->vnode = pVPeersDesc[pSql->index].vnode;
    tscTrace("%p vnode:%d ip:0x%x index:%d is picked up, pConn:%p", pSql, pVPeersDesc[pSql->index].vnode,
             pVPeersDesc[pSql->index].ip, pSql->index, pSql->thandle);
#else
    *pCode = 0;
    void *thandle = taosGetConnFromCache(tscConnCache, tsServerIp, pVPeersDesc[0].vnode, pTscObj->user);

    if (thandle == NULL) {
      SRpcConnInit connInit;
      memset(&connInit, 0, sizeof(connInit));
      connInit.cid = vidIndex;
      connInit.sid = 0;
      connInit.spi = 0;
      connInit.encrypt = 0;
      connInit.meterId = pSql->pTscObj->user;
      connInit.peerId = htonl((pVPeersDesc[0].vnode << TSDB_SHELL_VNODE_BITS));
      connInit.shandle = pVnodeConn;
      connInit.ahandle = pSql;
      connInit.peerIp = tsServerIpStr;
      connInit.peerPort = tsVnodeShellPort;
      thandle = taosOpenRpcConn(&connInit, pCode);
      vidIndex = (vidIndex + 1) % tscNumOfThreads;
    }

    pSql->thandle = thandle;
    pSql->ip = tsServerIp;
    pSql->vnode = pVPeersDesc[0].vnode;
#endif

    break;
  }
}