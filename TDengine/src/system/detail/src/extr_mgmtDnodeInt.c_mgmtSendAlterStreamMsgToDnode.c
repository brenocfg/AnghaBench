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
struct TYPE_12__ {int /*<<< orphan*/  status; int /*<<< orphan*/  uid; int /*<<< orphan*/  sid; int /*<<< orphan*/  vnode; } ;
struct TYPE_9__ {int /*<<< orphan*/  sid; } ;
struct TYPE_11__ {int /*<<< orphan*/  status; int /*<<< orphan*/  uid; TYPE_2__ gid; } ;
struct TYPE_10__ {int numOfVnodes; TYPE_1__* vnodeGid; } ;
struct TYPE_8__ {scalar_t__ ip; int /*<<< orphan*/  vnode; } ;
typedef  TYPE_3__ SVgObj ;
typedef  TYPE_4__ STabObj ;
typedef  int /*<<< orphan*/  SDnodeObj ;
typedef  TYPE_5__ SAlterStreamMsg ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_ALTER_STREAM ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mgmtGetDnode (scalar_t__) ; 
 char* taosBuildReqMsgToDnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSendMsgToDnode (int /*<<< orphan*/ *,char*,int) ; 

int mgmtSendAlterStreamMsgToDnode(STabObj *pMeter, SVgObj *pVgroup) {
  SAlterStreamMsg *pAlter;
  char *           pMsg, *pStart;
  int              i, msgLen = 0;
  SDnodeObj *      pObj;

  for (i = 0; i < pVgroup->numOfVnodes; ++i) {
    if (pVgroup->vnodeGid[i].ip == 0) continue;

    pObj = mgmtGetDnode(pVgroup->vnodeGid[i].ip);
    if (pObj == NULL) continue;

    pStart = taosBuildReqMsgToDnode(pObj, TSDB_MSG_TYPE_ALTER_STREAM);
    if (pStart == NULL) continue;
    pMsg = pStart;

    pAlter = (SAlterStreamMsg *)pMsg;
    pAlter->vnode = htons(pVgroup->vnodeGid[i].vnode);
    pAlter->sid = htonl(pMeter->gid.sid);
    pAlter->uid = pMeter->uid;
    pAlter->status = pMeter->status;

    pMsg += sizeof(SAlterStreamMsg);
    msgLen = pMsg - pStart;

    taosSendMsgToDnode(pObj, pStart, msgLen);
  }

  return 0;
}