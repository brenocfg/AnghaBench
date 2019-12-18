#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_2__ {scalar_t__ num; scalar_t__ (* initFp ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int TSDB_MOD_MAX ; 
 int /*<<< orphan*/  dError (char*) ; 
 int /*<<< orphan*/  dPrint (char*,...) ; 
 int /*<<< orphan*/  dmutex ; 
 int /*<<< orphan*/  dnodeCountRequest ; 
 int /*<<< orphan*/  dnodeInitModules () ; 
 scalar_t__ dnodeInitSystemSpec () ; 
 int /*<<< orphan*/  dnodeStartModuleSpec () ; 
 char* logDir ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  monitorCountReqFp ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ stub1 () ; 
 scalar_t__ taosCreateTierDirectory () ; 
 int /*<<< orphan*/  taosGetTimestampSec () ; 
 scalar_t__ taosInitLog (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taosResolveCRC () ; 
 int /*<<< orphan*/  tsInternalIp ; 
 TYPE_1__* tsModule ; 
 int /*<<< orphan*/  tsNumOfLogLines ; 
 int /*<<< orphan*/  tsPrintGlobalConfig () ; 
 int /*<<< orphan*/  tsReadGlobalConfig () ; 
 int /*<<< orphan*/  tsReadGlobalLogConfig () ; 
 int /*<<< orphan*/  tsRebootTime ; 
 int tscEmbedded ; 
 int /*<<< orphan*/  vnodeInitQHandle () ; 
 scalar_t__ vnodeInitSystem () ; 

int dnodeInitSystem() {
  char        temp[128];
  struct stat dirstat;

  taosResolveCRC();

  tsRebootTime = taosGetTimestampSec();
  tscEmbedded = 1;

  // Read global configuration.
  tsReadGlobalLogConfig();

  if (stat(logDir, &dirstat) < 0) mkdir(logDir, 0755);

  sprintf(temp, "%s/taosdlog", logDir);
  if (taosInitLog(temp, tsNumOfLogLines, 1) < 0) printf("failed to init log file\n");

  if (!tsReadGlobalConfig()) {  // TODO : Change this function
    tsPrintGlobalConfig();
    dError("TDengine read global config failed");
    return -1;
  }

  if (taosCreateTierDirectory() != 0) {
    dError("TDengine init tier directory failed");
    return -1;
  }

  tsPrintGlobalConfig();
  dPrint("Server IP address is:%s", tsInternalIp);

  signal(SIGPIPE, SIG_IGN);

  dnodeInitModules();
  pthread_mutex_init(&dmutex, NULL);

  dPrint("starting to initialize TDengine ...");

  vnodeInitQHandle();
  if (dnodeInitSystemSpec() < 0) {
    return -1;
  }
  
  for (int mod = 0; mod < TSDB_MOD_MAX; ++mod) {
    if (tsModule[mod].num != 0 && tsModule[mod].initFp) {
      if ((*tsModule[mod].initFp)() != 0) {
        dError("TDengine initialization failed");
        return -1;
      }
    }
  }

  if (vnodeInitSystem() != 0) {
    dError("TDengine vnodes initialization failed");
    return -1;
  }

  monitorCountReqFp = dnodeCountRequest;

  dnodeStartModuleSpec();

  dPrint("TDengine is initialized successfully");

  return 0;
}