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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {size_t cfgStatus; int /*<<< orphan*/  option; scalar_t__ maxValue; scalar_t__ minValue; scalar_t__ ptr; } ;
typedef  TYPE_1__ SGlobalConfig ;

/* Variables and functions */
 size_t TSDB_CFG_CSTATUS_FILE ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  pError (char*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pWarn (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * tsCfgStatusStr ; 

void tsReadUIntConfig(SGlobalConfig *cfg, char *input_value) {
  uint32_t  value = (uint32_t)atoi(input_value);
  uint32_t *option = (uint32_t *)cfg->ptr;
  if (value < (uint32_t)cfg->minValue || value > (uint32_t)cfg->maxValue) {
    pError("config option:%s, input value:%s, out of range[%f, %f], use default value:%u",
           cfg->option, input_value, cfg->minValue, cfg->maxValue, *option);
  } else {
    if (cfg->cfgStatus <= TSDB_CFG_CSTATUS_FILE) {
      *option = value;
      cfg->cfgStatus = TSDB_CFG_CSTATUS_FILE;
    } else {
      pWarn("config option:%s, input value:%s, is configured by %s, use %u", cfg->option, input_value,
            tsCfgStatusStr[cfg->cfgStatus], *option);
    }
  }
}