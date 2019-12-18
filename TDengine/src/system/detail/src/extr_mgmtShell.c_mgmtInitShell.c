#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rpcInit ;
struct TYPE_6__ {char* localIp; char* label; int numOfThreads; int bits; int numOfChanns; int sessionsPerChann; int idleTime; int /*<<< orphan*/  afp; int /*<<< orphan*/  qhandle; int /*<<< orphan*/  connType; int /*<<< orphan*/  idMgmt; int /*<<< orphan*/  fp; int /*<<< orphan*/  localPort; } ;
typedef  TYPE_1__ SRpcInit ;
typedef  TYPE_1__ SConnObj ;

/* Variables and functions */
 int /*<<< orphan*/  TAOS_CONN_SOCKET_TYPE_S () ; 
 int /*<<< orphan*/  TAOS_ID_FREE ; 
 TYPE_1__* connList ; 
 int /*<<< orphan*/  mError (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmtInitProcessShellMsg () ; 
 int /*<<< orphan*/  mgmtProcessMsgFromShell ; 
 int /*<<< orphan*/  mgmtQhandle ; 
 int /*<<< orphan*/  mgmtRetriveUserAuthInfo ; 
 int /*<<< orphan*/ * pShellConn ; 
 int /*<<< orphan*/ * taosOpenRpc (TYPE_1__*) ; 
 char* tsInternalIp ; 
 int tsMaxShellConns ; 
 int /*<<< orphan*/  tsMgmtShellPort ; 
 double tsNumOfCores ; 
 double tsNumOfThreadsPerCore ; 
 int tsShellActivityTimer ; 

int mgmtInitShell() {
  SRpcInit rpcInit;

  mgmtInitProcessShellMsg();

  int size = sizeof(SConnObj) * tsMaxShellConns;
  connList = (SConnObj *)malloc(size);
  if (connList == NULL) {
    mError("failed to malloc for connList to shell");
    return -1;
  }
  memset(connList, 0, size);

  int numOfThreads = tsNumOfCores * tsNumOfThreadsPerCore / 4.0;
  if (numOfThreads < 1) numOfThreads = 1;

  memset(&rpcInit, 0, sizeof(rpcInit));
#ifdef CLUSTER
  rpcInit.localIp = tsInternalIp;
#else
  rpcInit.localIp = "0.0.0.0";
#endif
  rpcInit.localPort = tsMgmtShellPort;
  rpcInit.label = "MND-shell";
  rpcInit.numOfThreads = numOfThreads;
  rpcInit.fp = mgmtProcessMsgFromShell;
  rpcInit.bits = 20;
  rpcInit.numOfChanns = 1;
  rpcInit.sessionsPerChann = tsMaxShellConns;
  rpcInit.idMgmt = TAOS_ID_FREE;
  rpcInit.connType = TAOS_CONN_SOCKET_TYPE_S();
  rpcInit.idleTime = tsShellActivityTimer * 2000;
  rpcInit.qhandle = mgmtQhandle;
  rpcInit.afp = mgmtRetriveUserAuthInfo;

  pShellConn = taosOpenRpc(&rpcInit);
  if (pShellConn == NULL) {
    mError("failed to init tcp connection to shell");
    return -1;
  }

  return 0;
}