#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ ** we_wordv; } ;
typedef  TYPE_1__ wordexp_t ;
struct stat {int dummy; } ;
struct TYPE_7__ {int ptrLength; size_t cfgStatus; int /*<<< orphan*/  option; scalar_t__ ptr; } ;
typedef  TYPE_2__ SGlobalConfig ;

/* Variables and functions */
 size_t TSDB_CFG_CSTATUS_FILE ; 
 int mkdir (char*,int) ; 
 int /*<<< orphan*/  pError (char*,int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  pPrint (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pWarn (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * tsCfgStatusStr ; 
 int /*<<< orphan*/  wordexp (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wordfree (TYPE_1__*) ; 

void tsReadFilePathConfig(SGlobalConfig *cfg, char *input_value) {
  int   length = strlen(input_value);
  char *option = (char *)cfg->ptr;
  if (length <= 0 || length > cfg->ptrLength) {
    pError("config option:%s, input value:%s, length out of range[0, %d], use default value:%s",
           cfg->option, input_value, cfg->ptrLength, option);
  } else {
    if (cfg->cfgStatus <= TSDB_CFG_CSTATUS_FILE) {
      wordexp_t full_path;
      wordexp(input_value, &full_path, 0);
      if (full_path.we_wordv != NULL && full_path.we_wordv[0] != NULL) {
        strcpy(option, full_path.we_wordv[0]);
      }
      wordfree(&full_path);

      struct stat dirstat;
      if (stat(option, &dirstat) < 0) {
        int code = mkdir(option, 0755);
        pPrint("config option:%s, input value:%s, directory not exist, create with return code:%d",
               cfg->option, input_value, code);
      }
      cfg->cfgStatus = TSDB_CFG_CSTATUS_FILE;
    } else {
      pWarn("config option:%s, input value:%s, is configured by %s, use %s", cfg->option, input_value,
            tsCfgStatusStr[cfg->cfgStatus], option);
    }
  }
}