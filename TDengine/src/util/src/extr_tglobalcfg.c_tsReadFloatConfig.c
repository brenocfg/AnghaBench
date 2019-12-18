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
struct TYPE_3__ {float minValue; float maxValue; size_t cfgStatus; int /*<<< orphan*/  option; scalar_t__ ptr; } ;
typedef  TYPE_1__ SGlobalConfig ;

/* Variables and functions */
 size_t TSDB_CFG_CSTATUS_FILE ; 
 scalar_t__ atof (char*) ; 
 int /*<<< orphan*/  pError (char*,int /*<<< orphan*/ ,char*,float,float,float) ; 
 int /*<<< orphan*/  pWarn (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/ * tsCfgStatusStr ; 

void tsReadFloatConfig(SGlobalConfig *cfg, char *input_value) {
  float  value = (float)atof(input_value);
  float *option = (float *)cfg->ptr;
  if (value < cfg->minValue || value > cfg->maxValue) {
    pError("config option:%s, input value:%s, out of range[%f, %f], use default value:%f",
           cfg->option, input_value, cfg->minValue, cfg->maxValue, *option);
  } else {
    if (cfg->cfgStatus <= TSDB_CFG_CSTATUS_FILE) {
      *option = value;
      cfg->cfgStatus = TSDB_CFG_CSTATUS_FILE;
    } else {
      pWarn("config option:%s, input value:%s, is configured by %s, use %f", cfg->option, input_value,
            tsCfgStatusStr[cfg->cfgStatus], *option);
    }
  }
}