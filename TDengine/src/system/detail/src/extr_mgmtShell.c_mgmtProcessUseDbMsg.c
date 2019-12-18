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
struct TYPE_8__ {int /*<<< orphan*/  thandle; TYPE_1__* pUser; } ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;
struct TYPE_6__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_2__ SUseDbMsg ;
typedef  TYPE_3__ SConnObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_USE_DB_RSP ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mgmtUseDb (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSendSimpleRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mgmtProcessUseDbMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  SUseDbMsg *pUse = (SUseDbMsg *)pMsg;
  int        code;

  code = mgmtUseDb(pConn, pUse->db);
  if (code == 0) mTrace("DB is change to:%s by %s", pUse->db, pConn->pUser->user);

  taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_USE_DB_RSP, code);

  return 0;
}