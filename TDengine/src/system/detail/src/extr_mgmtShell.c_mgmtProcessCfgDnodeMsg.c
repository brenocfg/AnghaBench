#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ip; } ;
struct TYPE_9__ {TYPE_1__* pUser; int /*<<< orphan*/  thandle; TYPE_2__* pAcct; } ;
struct TYPE_8__ {int /*<<< orphan*/  user; } ;
struct TYPE_7__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_3__ SConnObj ;
typedef  TYPE_4__ SCfgMsg ;

/* Variables and functions */
 int TSDB_CODE_NO_RIGHTS ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_CFG_MNODE_RSP ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_CFG_PNODE_RSP ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mgmtCheckRedirectMsg (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int mgmtSendCfgDnodeMsg (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taosSendSimpleRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mgmtProcessCfgDnodeMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  int      code = 0;
  SCfgMsg *pCfg = (SCfgMsg *)pMsg;

  if (mgmtCheckRedirectMsg(pConn, TSDB_MSG_TYPE_CFG_MNODE_RSP) != 0) {
    return 0;
  }

  if (strcmp(pConn->pAcct->user, "root") != 0) {
    code = TSDB_CODE_NO_RIGHTS;
  } else {
    code = mgmtSendCfgDnodeMsg(pMsg);
  }

  taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_CFG_PNODE_RSP, code);

  if (code == 0) mTrace("dnode:%s is configured by %s", pCfg->ip, pConn->pUser->user);

  return 0;
}