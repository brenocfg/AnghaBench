#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  thandle; int /*<<< orphan*/  superAuth; } ;
struct TYPE_5__ {int /*<<< orphan*/  queryId; } ;
typedef  TYPE_1__ SKillConnection ;
typedef  TYPE_2__ SConnObj ;

/* Variables and functions */
 int TSDB_CODE_NO_RIGHTS ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_KILL_CONNECTION_RSP ; 
 int mgmtKillConnection (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  taosSendSimpleRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mgmtProcessKillConnectionMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  int              code = 0;
  SKillConnection *pKill = (SKillConnection *)pMsg;

  if (!pConn->superAuth) {
    code = TSDB_CODE_NO_RIGHTS;
  } else {
    code = mgmtKillConnection(pKill->queryId, pConn);
  }

  taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_KILL_CONNECTION_RSP, code);

  return 0;
}