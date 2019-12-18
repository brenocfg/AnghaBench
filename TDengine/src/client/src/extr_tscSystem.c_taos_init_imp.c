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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  rpcInit ;
typedef  int int64_t ;
struct TYPE_6__ {int numOfIps; void** ipstr; void** ip; } ;
struct TYPE_5__ {char* label; int numOfThreads; int bits; int numOfChanns; int sessionsPerChann; int /*<<< orphan*/ * qhandle; void* connType; scalar_t__ noFree; void* idMgmt; void* fp; scalar_t__ localPort; void* localIp; } ;
typedef  int /*<<< orphan*/  SShellSubmitMsg ;
typedef  TYPE_1__ SRpcInit ;

/* Variables and functions */
 void* TAOS_CONN_SOCKET_TYPE_C () ; 
 void* TAOS_ID_FREE ; 
 void* inet_addr (char*) ; 
 int initialized ; 
 char* logDir ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/ * pTscMgmtConn ; 
 int /*<<< orphan*/ * pVnodeConn ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  slaveIndex ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (void*,char*) ; 
 int /*<<< orphan*/  tError (char*) ; 
 int /*<<< orphan*/  taosCloseRpc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosCloseRpcConn ; 
 int /*<<< orphan*/  taosGetTimestampSec () ; 
 int /*<<< orphan*/ * taosInitDataCache (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ taosInitLog (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * taosInitScheduler (int,int,char*) ; 
 int /*<<< orphan*/  taosOpenConnCache (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* taosOpenRpc (TYPE_1__*) ; 
 int taosOpenRpcChann (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  taosTmrInit (int,int,int,char*) ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tsInsertHeadSize ; 
 void* tsLocalIp ; 
 char* tsMasterIp ; 
 int tsMaxMeterConnections ; 
 int tsMaxMgmtConnections ; 
 int tsMaxVnodeConnections ; 
 scalar_t__ tsMeterMetaKeepTimer ; 
 scalar_t__ tsMetricMetaKeepTimer ; 
 double tsNumOfCores ; 
 int /*<<< orphan*/  tsNumOfLogLines ; 
 double tsNumOfThreadsPerCore ; 
 int /*<<< orphan*/  tsPrintGlobalConfig () ; 
 int /*<<< orphan*/  tsReadGlobalConfig () ; 
 int /*<<< orphan*/  tsReadGlobalLogConfig () ; 
 scalar_t__ tsRpcHeadSize ; 
 char* tsSecondIp ; 
 int tsShellActivityTimer ; 
 int /*<<< orphan*/ * tscCacheHandle ; 
 int /*<<< orphan*/  tscCheckDiskUsage ; 
 int /*<<< orphan*/  tscCheckDiskUsageTmr ; 
 int /*<<< orphan*/  tscConnCache ; 
 scalar_t__ tscEmbedded ; 
 int /*<<< orphan*/  tscError (char*) ; 
 int /*<<< orphan*/  tscInitMsgs () ; 
 TYPE_2__ tscMgmtIpList ; 
 int tscNumOfThreads ; 
 void* tscProcessMsgFromServer ; 
 int /*<<< orphan*/ * tscQhandle ; 
 int /*<<< orphan*/  tscTmr ; 
 int /*<<< orphan*/  tscTrace (char*,...) ; 

void taos_init_imp() {
  char        temp[128];
  struct stat dirstat;
  SRpcInit    rpcInit;

  srand(taosGetTimestampSec());

  if (tscEmbedded == 0) {
    /*
     * set localIp = 0
     * means unset tsLocalIp in client
     * except read from config file
     */
    strcpy(tsLocalIp, "0.0.0.0");

    // Read global configuration.
    tsReadGlobalLogConfig();

    // For log directory
    if (stat(logDir, &dirstat) < 0) mkdir(logDir, 0755);

    sprintf(temp, "%s/taoslog", logDir);
    if (taosInitLog(temp, tsNumOfLogLines, 10) < 0) {
      printf("failed to open log file in directory:%s\n", logDir);
    }

    tsReadGlobalConfig();
    tsPrintGlobalConfig();

    tscTrace("starting to initialize TAOS client ...");
    tscTrace("Local IP address is:%s", tsLocalIp);
  }

#ifdef CLUSTER
  tscMgmtIpList.numOfIps = 2;
  strcpy(tscMgmtIpList.ipstr[0], tsMasterIp);
  tscMgmtIpList.ip[0] = inet_addr(tsMasterIp);

  strcpy(tscMgmtIpList.ipstr[1], tsMasterIp);
  tscMgmtIpList.ip[1] = inet_addr(tsMasterIp);

  if (tsSecondIp[0]) {
    tscMgmtIpList.numOfIps = 3;
    strcpy(tscMgmtIpList.ipstr[2], tsSecondIp);
    tscMgmtIpList.ip[2] = inet_addr(tsSecondIp);
  }
#endif

  tscInitMsgs();
  slaveIndex = rand();
  int queueSize = tsMaxVnodeConnections + tsMaxMeterConnections + tsMaxMgmtConnections + tsMaxMgmtConnections;

  if (tscEmbedded == 0) {
    tscNumOfThreads = tsNumOfCores * tsNumOfThreadsPerCore / 2.0;
  } else {
    tscNumOfThreads = tsNumOfCores * tsNumOfThreadsPerCore / 4.0;
  }

  if (tscNumOfThreads < 2) tscNumOfThreads = 2;

  tscQhandle = taosInitScheduler(queueSize, tscNumOfThreads, "tsc");
  if (NULL == tscQhandle) {
    tscError("failed to init scheduler");
    return;
  }

  memset(&rpcInit, 0, sizeof(rpcInit));
  rpcInit.localIp = tsLocalIp;
  rpcInit.localPort = 0;
  rpcInit.label = "TSC-vnode";
  rpcInit.numOfThreads = tscNumOfThreads;
  rpcInit.fp = tscProcessMsgFromServer;
  rpcInit.bits = 20;
  rpcInit.numOfChanns = tscNumOfThreads;
  rpcInit.sessionsPerChann = tsMaxVnodeConnections / tscNumOfThreads;
  rpcInit.idMgmt = TAOS_ID_FREE;
  rpcInit.noFree = 0;
  rpcInit.connType = TAOS_CONN_SOCKET_TYPE_C();
  rpcInit.qhandle = tscQhandle;
  pVnodeConn = taosOpenRpc(&rpcInit);
  if (pVnodeConn == NULL) {
    tscError("failed to init connection to vnode");
    return;
  }

  for (int i = 0; i < tscNumOfThreads; ++i) {
    int retVal = taosOpenRpcChann(pVnodeConn, i, rpcInit.sessionsPerChann);
    if (0 != retVal) {
      tError("TSC-vnode, failed to open rpc chann");
      taosCloseRpc(pVnodeConn);
      return;
    }
  }

  memset(&rpcInit, 0, sizeof(rpcInit));
  rpcInit.localIp = tsLocalIp;
  rpcInit.localPort = 0;
  rpcInit.label = "TSC-mgmt";
  rpcInit.numOfThreads = 1;
  rpcInit.fp = tscProcessMsgFromServer;
  rpcInit.bits = 20;
  rpcInit.numOfChanns = 1;
  rpcInit.sessionsPerChann = tsMaxMgmtConnections;
  rpcInit.idMgmt = TAOS_ID_FREE;
  rpcInit.noFree = 0;
  rpcInit.connType = TAOS_CONN_SOCKET_TYPE_C();
  rpcInit.qhandle = tscQhandle;
  pTscMgmtConn = taosOpenRpc(&rpcInit);
  if (pTscMgmtConn == NULL) {
    tscError("failed to init connection to mgmt");
    return;
  }

  tscTmr = taosTmrInit(tsMaxMgmtConnections * 2, 200, 60000, "TSC");
  if(0 == tscEmbedded){
    taosTmrReset(tscCheckDiskUsage, 10, NULL, tscTmr, &tscCheckDiskUsageTmr);      
  }
  int64_t refreshTime = tsMetricMetaKeepTimer < tsMeterMetaKeepTimer ? tsMetricMetaKeepTimer : tsMeterMetaKeepTimer;
  refreshTime = refreshTime > 2 ? 2 : refreshTime;
  refreshTime = refreshTime < 1 ? 1 : refreshTime;

  if (tscCacheHandle == NULL) tscCacheHandle = taosInitDataCache(tsMaxMeterConnections / 2, tscTmr, refreshTime);

  tscConnCache = taosOpenConnCache(tsMaxMeterConnections * 2, taosCloseRpcConn, tscTmr, tsShellActivityTimer * 1000);

  initialized = 1;
  tscTrace("client is initialized successfully");
  tsInsertHeadSize = tsRpcHeadSize + sizeof(SShellSubmitMsg);
}