#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_20__ {int numOfIps; } ;
struct TYPE_19__ {int acctId; } ;
struct TYPE_18__ {int /*<<< orphan*/  user; int /*<<< orphan*/  ip; int /*<<< orphan*/  thandle; TYPE_1__* pUser; TYPE_6__* pAcct; int /*<<< orphan*/  superAuth; int /*<<< orphan*/  writeAuth; int /*<<< orphan*/ * pDb; } ;
struct TYPE_17__ {scalar_t__* db; } ;
struct TYPE_16__ {int /*<<< orphan*/  superAuth; int /*<<< orphan*/  writeAuth; int /*<<< orphan*/  version; int /*<<< orphan*/  acctId; } ;
struct TYPE_15__ {int code; scalar_t__ more; } ;
struct TYPE_14__ {int /*<<< orphan*/  acct; } ;
typedef  TYPE_1__ SUserObj ;
typedef  TYPE_2__ STaosRsp ;
typedef  int /*<<< orphan*/  SIpList ;
typedef  int /*<<< orphan*/  SDbObj ;
typedef  TYPE_3__ SConnectRsp ;
typedef  TYPE_4__ SConnectMsg ;
typedef  TYPE_5__ SConnObj ;
typedef  TYPE_6__ SAcctObj ;

/* Variables and functions */
 int TSDB_CODE_GRANT_EXPIRED ; 
 int TSDB_CODE_INVALID_DB ; 
 int TSDB_CODE_INVALID_USER ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_CONNECT_RSP ; 
 char* TS_PATH_DELIMITER ; 
 int /*<<< orphan*/  atomic_fetch_sub_32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ grantCheckExpired () ; 
 int /*<<< orphan*/  mLPrint (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  mgmtEstablishConn (TYPE_5__*) ; 
 TYPE_6__* mgmtGetAcct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mgmtGetDb (char*) ; 
 TYPE_1__* mgmtGetUser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmtRemoveConnFromAcct (TYPE_5__*) ; 
 int /*<<< orphan*/  mgmtShellConns ; 
 TYPE_7__* pSdbPublicIpList ; 
 int /*<<< orphan*/  sdbExtConns ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* taosBuildRspMsgWithSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taosSendMsgToPeer (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tinet_ntoa (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsTimePrecision ; 
 int /*<<< orphan*/  version ; 

int mgmtProcessConnectMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  STaosRsp *   pRsp;
  SConnectRsp *pConnectRsp;
  SConnectMsg *pConnectMsg;
  char *       pStart;
  int          code = TSDB_CODE_INVALID_USER;
  SAcctObj *   pAcct = NULL;
  SUserObj *   pUser = NULL;
  SDbObj *     pDb = NULL;
  char         dbName[256] = {0};

  pConnectMsg = (SConnectMsg *)pMsg;

  pUser = mgmtGetUser(pConn->user);
  if (pUser == NULL) {
    code = TSDB_CODE_INVALID_USER;
    goto _rsp;
  }

  if (grantCheckExpired()) {
    code = TSDB_CODE_GRANT_EXPIRED;
    goto _rsp;
  }

  pAcct = mgmtGetAcct(pUser->acct);

  if (pConnectMsg->db[0]) {
    sprintf(dbName, "%x%s%s", pAcct->acctId, TS_PATH_DELIMITER, pConnectMsg->db);
    pDb = mgmtGetDb(dbName);
    if (pDb == NULL) {
      code = TSDB_CODE_INVALID_DB;
      goto _rsp;
    }
  }

  if (pConn->pAcct) {
    mgmtRemoveConnFromAcct(pConn);
    atomic_fetch_sub_32(&mgmtShellConns, 1);
    atomic_fetch_sub_32(&sdbExtConns, 1);
  }

  code = 0;
  pConn->pAcct = pAcct;
  pConn->pDb = pDb;
  pConn->pUser = pUser;
  mgmtEstablishConn(pConn);

_rsp:
  pStart = taosBuildRspMsgWithSize(pConn->thandle, TSDB_MSG_TYPE_CONNECT_RSP, 128);
  if (pStart == NULL) return 0;

  pMsg = pStart;
  pRsp = (STaosRsp *)pMsg;
  pRsp->code = code;
  pMsg += sizeof(STaosRsp);

  if (code == 0) {
    pConnectRsp = (SConnectRsp *)pRsp->more;
    sprintf(pConnectRsp->acctId, "%x", pConn->pAcct->acctId);
    strcpy(pConnectRsp->version, version);
    pConnectRsp->writeAuth = pConn->writeAuth;
    pConnectRsp->superAuth = pConn->superAuth;
    pMsg += sizeof(SConnectRsp);

#ifdef CLUSTER
    int size = pSdbPublicIpList->numOfIps * 4 + sizeof(SIpList);
    memcpy(pMsg, pSdbPublicIpList, size);
    pMsg += size;
#endif

    // set the time resolution: millisecond or microsecond
    *((uint32_t *)pMsg) = tsTimePrecision;
    pMsg += sizeof(uint32_t);

  } else {
    pConn->pAcct = NULL;
    pConn->pUser = NULL;
  }

  msgLen = pMsg - pStart;
  taosSendMsgToPeer(pConn->thandle, pStart, msgLen);

  char ipstr[24];
  tinet_ntoa(ipstr, pConn->ip);
  mLPrint("user:%s login from %s, code:%d", pConn->user, ipstr, code);

  return code;
}