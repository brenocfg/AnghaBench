#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cfgType; int valType; int /*<<< orphan*/  option; } ;
typedef  TYPE_1__ SGlobalConfig ;

/* Variables and functions */
 int TSDB_CFG_CTYPE_B_CONFIG ; 
 int TSDB_CFG_CTYPE_B_LOG ; 
#define  TSDB_CFG_VTYPE_DIRECTORY 129 
#define  TSDB_CFG_VTYPE_INT 128 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* tsGlobalConfig ; 
 int tsGlobalConfigNum ; 
 int /*<<< orphan*/  tsReadFilePathConfig (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  tsReadIntConfig (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  tsSetAllDebugFlag () ; 

void tsReadLogOption(char *option, char *value) {
  for (int i = 0; i < tsGlobalConfigNum; ++i) {
    SGlobalConfig *cfg = tsGlobalConfig + i;
    if (!(cfg->cfgType & TSDB_CFG_CTYPE_B_CONFIG) || !(cfg->cfgType & TSDB_CFG_CTYPE_B_LOG)) continue;
    if (strcasecmp(cfg->option, option) != 0) continue;

    switch (cfg->valType) {
      case TSDB_CFG_VTYPE_INT:
        tsReadIntConfig(cfg, value);
        if (strcasecmp(cfg->option, "debugFlag") == 0) {
          tsSetAllDebugFlag();
        }
        break;
      case TSDB_CFG_VTYPE_DIRECTORY:
        tsReadFilePathConfig(cfg, value);
        break;
      default:
        break;
    }
    break;
  }
}