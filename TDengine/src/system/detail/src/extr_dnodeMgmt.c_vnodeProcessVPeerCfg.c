#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* maxSessions; int /*<<< orphan*/  replications; } ;
struct TYPE_16__ {scalar_t__ status; TYPE_2__ cfg; } ;
struct TYPE_15__ {void* vnode; void* ip; } ;
struct TYPE_11__ {void* totalBlocks; } ;
struct TYPE_13__ {int replications; void* maxSessions; void* rowsInFileBlock; int /*<<< orphan*/  blocksPerMeter; void* commitTime; void* daysToKeep; void* daysToKeep2; void* daysToKeep1; void* daysPerFile; TYPE_1__ cacheNumOfBlocks; void* cacheBlockSize; void* vgId; } ;
struct TYPE_14__ {TYPE_6__* vpeerDesc; TYPE_3__ cfg; void* vnode; } ;
typedef  TYPE_3__ SVnodeCfg ;
typedef  TYPE_4__ SVPeersMsg ;
typedef  int /*<<< orphan*/  SMgmtObj ;

/* Variables and functions */
 int TSDB_MAX_VNODES ; 
 scalar_t__ TSDB_STATUS_CREATING ; 
 int /*<<< orphan*/  dError (char*,int) ; 
 int /*<<< orphan*/  dTrace (char*,int,...) ; 
 void* htonl (void*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeCleanUpOneVnode (int) ; 
 int /*<<< orphan*/  vnodeConfigVPeers (int,int,TYPE_6__*) ; 
 int vnodeCreateVnode (int,TYPE_3__*,TYPE_6__*) ; 
 TYPE_7__* vnodeList ; 
 int /*<<< orphan*/  vnodeOpenVnode (int) ; 
 int /*<<< orphan*/  vnodeRemoveVnode (int) ; 
 int /*<<< orphan*/  vnodeSaveVnodeCfg (int,TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  vnodeUpdateHeadFile (int,void*,void*) ; 

int vnodeProcessVPeerCfg(char *msg, int msgLen, SMgmtObj *pMgmtObj) {
  SVPeersMsg *pMsg = (SVPeersMsg *)msg;
  int         i, vnode;

  vnode = htonl(pMsg->vnode);
  if (vnode >= TSDB_MAX_VNODES) {
    dError("vid:%d, vnode is out of range", vnode);
    return -1;
  }

  if (vnodeList[vnode].status == TSDB_STATUS_CREATING) {
    dTrace("vid:%d, vnode is still under creating", vnode);
    return 0;
  }

  SVnodeCfg *pCfg = &pMsg->cfg;
  pCfg->vgId = htonl(pCfg->vgId);
  pCfg->maxSessions = htonl(pCfg->maxSessions);
  pCfg->cacheBlockSize = htonl(pCfg->cacheBlockSize);
  pCfg->cacheNumOfBlocks.totalBlocks = htonl(pCfg->cacheNumOfBlocks.totalBlocks);
  pCfg->daysPerFile = htonl(pCfg->daysPerFile);
  pCfg->daysToKeep1 = htonl(pCfg->daysToKeep1);
  pCfg->daysToKeep2 = htonl(pCfg->daysToKeep2);
  pCfg->daysToKeep = htonl(pCfg->daysToKeep);
  pCfg->commitTime = htonl(pCfg->commitTime);
  pCfg->blocksPerMeter = htons(pCfg->blocksPerMeter);
  pCfg->rowsInFileBlock = htonl(pCfg->rowsInFileBlock);

  if (pCfg->replications > 0) {
    dTrace("vid:%d, vpeer cfg received, replica:%d session:%d, vnodeList replica:%d session:%d",
        vnode, pCfg->replications, pCfg->maxSessions, vnodeList[vnode].cfg.replications, vnodeList[vnode].cfg.maxSessions);
    for (i = 0; i < pCfg->replications; ++i) {
      pMsg->vpeerDesc[i].vnode = htonl(pMsg->vpeerDesc[i].vnode);
      pMsg->vpeerDesc[i].ip = htonl(pMsg->vpeerDesc[i].ip);
      dTrace("vid:%d, vpeer:%d ip:0x%x vid:%d ", vnode, i, pMsg->vpeerDesc[i].ip, pMsg->vpeerDesc[i].vnode);
    }
  }

  if (vnodeList[vnode].cfg.maxSessions == 0) {
    if (pCfg->maxSessions > 0) {
      return vnodeCreateVnode(vnode, pCfg, pMsg->vpeerDesc);
    }
  } else {
    if (pCfg->maxSessions > 0) {
      if (pCfg->maxSessions != vnodeList[vnode].cfg.maxSessions) {
          vnodeCleanUpOneVnode(vnode);
      }

      vnodeConfigVPeers(vnode, pCfg->replications, pMsg->vpeerDesc);
      vnodeSaveVnodeCfg(vnode, pCfg, pMsg->vpeerDesc);

      if (pCfg->maxSessions != vnodeList[vnode].cfg.maxSessions) {
        vnodeUpdateHeadFile(vnode, vnodeList[vnode].cfg.maxSessions, pCfg->maxSessions);
        vnodeList[vnode].cfg.maxSessions = pCfg->maxSessions;
        vnodeOpenVnode(vnode);
      }
    } else {
      vnodeRemoveVnode(vnode);
    }
  }

  return 0;
}