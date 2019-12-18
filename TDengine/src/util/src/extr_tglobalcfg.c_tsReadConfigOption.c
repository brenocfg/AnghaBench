#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int cfgType; int valType; int /*<<< orphan*/  option; } ;
typedef  TYPE_1__ SGlobalConfig ;

/* Variables and functions */
 int TSDB_CFG_CTYPE_B_CONFIG ; 
#define  TSDB_CFG_VTYPE_DIRECTORY 134 
#define  TSDB_CFG_VTYPE_FLOAT 133 
#define  TSDB_CFG_VTYPE_INT 132 
#define  TSDB_CFG_VTYPE_IPSTR 131 
#define  TSDB_CFG_VTYPE_SHORT 130 
#define  TSDB_CFG_VTYPE_STRING 129 
#define  TSDB_CFG_VTYPE_UINT 128 
 int /*<<< orphan*/  pError (char*,char const*,char*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* tsGlobalConfig ; 
 int tsGlobalConfigNum ; 
 int /*<<< orphan*/  tsReadFilePathConfig (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  tsReadFloatConfig (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  tsReadIntConfig (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  tsReadIpConfig (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  tsReadShortConfig (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  tsReadStrConfig (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  tsReadUIntConfig (TYPE_1__*,char*) ; 

void tsReadConfigOption(const char *option, char *value) {
  for (int i = 0; i < tsGlobalConfigNum; ++i) {
    SGlobalConfig *cfg = tsGlobalConfig + i;
    if (!(cfg->cfgType & TSDB_CFG_CTYPE_B_CONFIG)) continue;
    if (strcasecmp(cfg->option, option) != 0) continue;

    switch (cfg->valType) {
      case TSDB_CFG_VTYPE_SHORT:
        tsReadShortConfig(cfg, value);
        break;
      case TSDB_CFG_VTYPE_INT:
        tsReadIntConfig(cfg, value);
        break;
      case TSDB_CFG_VTYPE_UINT:
        tsReadUIntConfig(cfg, value);
        break;
      case TSDB_CFG_VTYPE_FLOAT:
        tsReadFloatConfig(cfg, value);
        break;
      case TSDB_CFG_VTYPE_STRING:
        tsReadStrConfig(cfg, value);
        break;
      case TSDB_CFG_VTYPE_IPSTR:
        tsReadIpConfig(cfg, value);
        break;
      case TSDB_CFG_VTYPE_DIRECTORY:
        tsReadFilePathConfig(cfg, value);
        break;
      default:
        pError("config option:%s, input value:%s, can't be recognized", option, value);
        break;
    }
    break;
  }
}