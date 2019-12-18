#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char** we_wordv; } ;
typedef  TYPE_1__ wordexp_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* configDir ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 char* logDir ; 
 int mdebugFlag ; 
 int /*<<< orphan*/  paGetToken (char*,char**,int*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int sdbDebugFlag ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  tfree (char*) ; 
 int /*<<< orphan*/  tsInitGlobalConfig () ; 
 int /*<<< orphan*/  tsReadLogOption (char*,char*) ; 
 int /*<<< orphan*/  wordexp (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wordfree (TYPE_1__*) ; 

void tsReadGlobalLogConfig() {
  tsInitGlobalConfig();

  FILE * fp;
  char * line, *option, *value;
  size_t len;
  int    olen, vlen;
  char   fileName[128];

  mdebugFlag = 135;
  sdbDebugFlag = 135;

  wordexp_t full_path;
  wordexp(configDir, &full_path, 0);
  if (full_path.we_wordv != NULL && full_path.we_wordv[0] != NULL) {
    strcpy(configDir, full_path.we_wordv[0]);
  } else {
    printf("configDir:%s not there, use default value: /etc/taos", configDir);
    strcpy(configDir, "/etc/taos");
  }
  wordfree(&full_path);

  tsReadLogOption("logDir", logDir);
  sprintf(fileName, "%s/taos.cfg", configDir);
  fp = fopen(fileName, "r");
  if (fp == NULL) {
    printf("\noption file:%s not found, all options are set to system default\n", fileName);
    return;
  }

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

    tsReadLogOption(option, value);
  }

  tfree(line);
  fclose(fp);
}