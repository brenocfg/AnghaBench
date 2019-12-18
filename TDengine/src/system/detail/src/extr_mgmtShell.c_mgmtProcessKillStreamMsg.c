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
struct TYPE_6__ {int /*<<< orphan*/  thandle; int /*<<< orphan*/  writeAuth; } ;
struct TYPE_5__ {int /*<<< orphan*/  queryId; } ;
typedef  TYPE_1__ SKillStream ;
typedef  TYPE_2__ SConnObj ;

/* Variables and functions */
 int TSDB_CODE_NO_RIGHTS ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_KILL_STREAM_RSP ; 
 int mgmtKillStream (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  taosSendSimpleRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mgmtProcessKillStreamMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  int          code = 0;
  SKillStream *pKill = (SKillStream *)pMsg;

  if (!pConn->writeAuth) {
    code = TSDB_CODE_NO_RIGHTS;
  } else {
    code = mgmtKillStream(pKill->queryId, pConn);
  }

  taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_KILL_STREAM_RSP, code);

  return 0;
}