#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  db; void* maxSessions; void* daysToKeep; void* daysPerFile; } ;
struct TYPE_8__ {int /*<<< orphan*/  thandle; TYPE_1__* pUser; int /*<<< orphan*/  pAcct; int /*<<< orphan*/  writeAuth; } ;
struct TYPE_7__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_2__ SConnObj ;
typedef  TYPE_3__ SAlterDbMsg ;

/* Variables and functions */
 int TSDB_CODE_NO_RIGHTS ; 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_ALTER_DB_RSP ; 
 void* htonl (void*) ; 
 int /*<<< orphan*/  mLPrint (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mgmtAlterDb (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ mgmtCheckRedirectMsg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSendSimpleRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mgmtProcessAlterDbMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  SAlterDbMsg *pAlter = (SAlterDbMsg *)pMsg;
  int          code = 0;

  if (mgmtCheckRedirectMsg(pConn, TSDB_MSG_TYPE_ALTER_DB_RSP) != 0) {
    return 0;
  }

  pAlter->daysPerFile = htonl(pAlter->daysPerFile);
  pAlter->daysToKeep = htonl(pAlter->daysToKeep);
  pAlter->maxSessions = htonl(pAlter->maxSessions) + 1;

  if (!pConn->writeAuth) {
    code = TSDB_CODE_NO_RIGHTS;
  } else {
    code = mgmtAlterDb(pConn->pAcct, pAlter);
    if (code == TSDB_CODE_SUCCESS) {
      mLPrint("DB:%s is altered by %s", pAlter->db, pConn->pUser->user);
    }
  }

  taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_ALTER_DB_RSP, code);

  return 0;
}