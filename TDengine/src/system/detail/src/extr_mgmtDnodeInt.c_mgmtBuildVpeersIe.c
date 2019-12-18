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
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int totalBlocks; } ;
struct TYPE_12__ {int maxSessions; int cacheBlockSize; int daysPerFile; int daysToKeep1; int daysToKeep2; int daysToKeep; int commitTime; char replications; int rowsInFileBlock; int /*<<< orphan*/  blocksPerMeter; TYPE_1__ cacheNumOfBlocks; void* vgId; } ;
struct TYPE_16__ {TYPE_3__ cfg; } ;
struct TYPE_15__ {void* vnode; void* ip; } ;
struct TYPE_14__ {TYPE_6__* vpeerDesc; TYPE_3__ cfg; void* vnode; } ;
struct TYPE_13__ {int vgId; int numOfVnodes; TYPE_2__* vnodeGid; int /*<<< orphan*/  dbName; } ;
struct TYPE_11__ {int ip; int vnode; } ;
typedef  TYPE_3__ SVnodeCfg ;
typedef  TYPE_4__ SVgObj ;
typedef  TYPE_5__ SVPeersMsg ;
typedef  TYPE_6__ SVPeerDesc ;
typedef  TYPE_7__ SDbObj ;

/* Variables and functions */
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 TYPE_7__* mgmtGetDb (int /*<<< orphan*/ ) ; 

char *mgmtBuildVpeersIe(char *pMsg, SVgObj *pVgroup, int vnode) {
  SVPeersMsg *pVPeers = (SVPeersMsg *)pMsg;
  SDbObj *    pDb;

  pDb = mgmtGetDb(pVgroup->dbName);
  pVPeers->vnode = htonl(vnode);

  pVPeers->cfg = pDb->cfg;
  SVnodeCfg *pCfg = &pVPeers->cfg;
  pCfg->vgId = htonl(pVgroup->vgId);
  pCfg->maxSessions = htonl(pCfg->maxSessions);
  pCfg->cacheBlockSize = htonl(pCfg->cacheBlockSize);
  pCfg->cacheNumOfBlocks.totalBlocks = htonl(pCfg->cacheNumOfBlocks.totalBlocks);
  pCfg->daysPerFile = htonl(pCfg->daysPerFile);
  pCfg->daysToKeep1 = htonl(pCfg->daysToKeep1);
  pCfg->daysToKeep2 = htonl(pCfg->daysToKeep2);
  pCfg->daysToKeep = htonl(pCfg->daysToKeep);
  pCfg->commitTime = htonl(pCfg->commitTime);
  pCfg->blocksPerMeter = htons(pCfg->blocksPerMeter);
  pCfg->replications = (char)pVgroup->numOfVnodes;
  pCfg->rowsInFileBlock = htonl(pCfg->rowsInFileBlock);

#ifdef CLUSTER
  SVPeerDesc *vpeerDesc = pVPeers->vpeerDesc;

  pMsg = (char *)(pVPeers->vpeerDesc);

  for (int j = 0; j < pVgroup->numOfVnodes; ++j) {
    vpeerDesc[j].ip = htonl(pVgroup->vnodeGid[j].ip);
    vpeerDesc[j].vnode = htonl(pVgroup->vnodeGid[j].vnode);
    pMsg += sizeof(SVPeerDesc);
  }
#endif

  return pMsg;
}