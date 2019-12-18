#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  thandle; TYPE_1__* pUser; int /*<<< orphan*/  pAcct; scalar_t__ superAuth; } ;
struct TYPE_7__ {char* user; } ;
struct TYPE_6__ {char* user; } ;
typedef  TYPE_2__ SDropUserMsg ;
typedef  TYPE_3__ SConnObj ;

/* Variables and functions */
 int TSDB_CODE_NO_RIGHTS ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_DROP_USER_RSP ; 
 int /*<<< orphan*/  mLPrint (char*,char*,char*) ; 
 scalar_t__ mgmtCheckRedirectMsg (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int mgmtDropUser (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  taosSendSimpleRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mgmtProcessDropUserMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  SDropUserMsg *pDrop = (SDropUserMsg *)pMsg;
  int           code = 0;

  if (mgmtCheckRedirectMsg(pConn, TSDB_MSG_TYPE_DROP_USER_RSP) != 0) {
    return 0;
  }

  if (strcmp(pConn->pUser->user, pDrop->user) == 0) {
    code = TSDB_CODE_NO_RIGHTS;
  } else if (strcmp(pDrop->user, "monitor") == 0 || strcmp(pDrop->user, "stream") == 0) {
    code = TSDB_CODE_NO_RIGHTS;
  } else {
    if (pConn->superAuth) {
      code = mgmtDropUser(pConn->pAcct, pDrop->user);
      if (code == 0) {
        mLPrint("user:%s is dropped by %s", pDrop->user, pConn->pUser->user);
      }
    } else {
      code = TSDB_CODE_NO_RIGHTS;
    }
  }

  taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_DROP_USER_RSP, code);

  return 0;
}