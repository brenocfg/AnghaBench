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
struct TYPE_7__ {int /*<<< orphan*/  user; int /*<<< orphan*/  pass; } ;
struct TYPE_6__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_2__ SCreateUserMsg ;
typedef  TYPE_3__ SConnObj ;

/* Variables and functions */
 int TSDB_CODE_NO_RIGHTS ; 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_CREATE_USER_RSP ; 
 int /*<<< orphan*/  mLPrint (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mgmtCheckRedirectMsg (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int mgmtCreateUser (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSendSimpleRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mgmtProcessCreateUserMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  SCreateUserMsg *pCreate = (SCreateUserMsg *)pMsg;
  int             code = 0;

  if (mgmtCheckRedirectMsg(pConn, TSDB_MSG_TYPE_CREATE_USER_RSP) != 0) {
    return 0;
  }

  if (pConn->superAuth) {
    code = mgmtCreateUser(pConn->pAcct, pCreate->user, pCreate->pass);
    if (code == TSDB_CODE_SUCCESS) {
      mLPrint("user:%s is created by %s", pCreate->user, pConn->pUser->user);
    }
  } else {
    code = TSDB_CODE_NO_RIGHTS;
  }

  taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_CREATE_USER_RSP, code);

  return 0;
}