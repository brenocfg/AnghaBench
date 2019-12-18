#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cfgStatus; } ;
typedef  TYPE_1__ SGlobalConfig ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ TSDB_CFG_CSTATUS_FILE ; 
 char* configDir ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pError (char*) ; 
 int /*<<< orphan*/  paGetToken (char*,char**,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,scalar_t__*) ; 
 scalar_t__ strlen (scalar_t__*) ; 
 int /*<<< orphan*/  taosGetPrivateIp (scalar_t__*) ; 
 int /*<<< orphan*/  taosGetSystemInfo () ; 
 int /*<<< orphan*/  tfree (char*) ; 
 TYPE_1__* tsGetConfigOption (char*) ; 
 int /*<<< orphan*/  tsInitGlobalConfig () ; 
 scalar_t__* tsInternalIp ; 
 scalar_t__* tsLocalIp ; 
 scalar_t__* tsMasterIp ; 
 int tsNumOfCores ; 
 scalar_t__* tsPrivateIp ; 
 scalar_t__* tsPublicIp ; 
 int /*<<< orphan*/  tsReadConfigOption (char*,char*) ; 
 int /*<<< orphan*/  tsReadGlobalConfigSpec () ; 
 scalar_t__* tsSecondIp ; 
 int /*<<< orphan*/  tsSetLocale () ; 
 int /*<<< orphan*/  tsSetTimeZone () ; 
 int tsVersion ; 
 scalar_t__ tscEmbedded ; 
 char* version ; 

bool tsReadGlobalConfig() {
  tsInitGlobalConfig();

  FILE * fp;
  char * line, *option, *value, *value1;
  size_t len;
  int    olen, vlen, vlen1;
  char   fileName[128];

  sprintf(fileName, "%s/taos.cfg", configDir);
  fp = fopen(fileName, "r");
  if (fp == NULL) {
  } else {
    line = NULL;
    while (!feof(fp)) {
      tfree(line);
      line = option = value = NULL;
      len = olen = vlen = 0;

      getline(&line, &len, fp);
      if (line == NULL) break;

      paGetToken(line, &option, &olen);
      if (olen == 0) continue;
      option[olen] = 0;

      paGetToken(option + olen + 1, &value, &vlen);
      if (vlen == 0) continue;
      value[vlen] = 0;

      // For dataDir, the format is:
      // dataDir    /mnt/disk1    0
      paGetToken(value + vlen + 1, &value1, &vlen1);

      tsReadConfigOption(option, value);
    }

    tfree(line);
    fclose(fp);
  }

  tsReadGlobalConfigSpec();

  if (tsPrivateIp[0] == 0) {
    taosGetPrivateIp(tsPrivateIp);
  }

  if (tsPublicIp[0] == 0) {
    strcpy(tsPublicIp, tsPrivateIp);
  }

  if (tsInternalIp[0] == 0) {
    strcpy(tsInternalIp, tsPrivateIp);
  }

  if (tsLocalIp[0] == 0) {
    strcpy(tsLocalIp, tsPrivateIp);
  }

  if (tsMasterIp[0] == 0) {
    strcpy(tsMasterIp, tsPrivateIp);
  }

  if (tsSecondIp[0] == 0) {
    strcpy(tsSecondIp, tsMasterIp);
  }

  taosGetSystemInfo();

  tsSetLocale();

  SGlobalConfig *cfg_timezone = tsGetConfigOption("timezone");
  if (cfg_timezone && cfg_timezone->cfgStatus == TSDB_CFG_CSTATUS_FILE) {
    tsSetTimeZone();
  }

  if (tsNumOfCores <= 0) {
    tsNumOfCores = 1;
  }

  if (strlen(tsPrivateIp) == 0) {
    pError("privateIp is null");
    return false;
  }

  if (tscEmbedded) {
    strcpy(tsLocalIp, tsPrivateIp);
  }

  tsVersion = 0;
  for (int i = 0; i < 10; i++) {
    if (version[i] >= '0' && version[i] <= '9') {
      tsVersion = tsVersion * 10 + (version[i] - '0');
    } else if (version[i] == 0) {
      break;
    }
  }
  tsVersion = 10 * tsVersion;

  return true;
}