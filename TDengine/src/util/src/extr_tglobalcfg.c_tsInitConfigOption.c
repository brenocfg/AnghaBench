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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* int8_t ;
struct TYPE_3__ {char* option; float minValue; float maxValue; int /*<<< orphan*/  cfgStatus; void* unitType; int /*<<< orphan*/  ptrLength; void* cfgType; void* valType; void* ptr; } ;
typedef  TYPE_1__ SGlobalConfig ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CFG_CSTATUS_NONE ; 

void tsInitConfigOption(SGlobalConfig *cfg, char *name, void *ptr, int8_t valType, int8_t cfgType, float minVal,
                        float maxVal, uint8_t ptrLength, int8_t unitType) {
  cfg->option = name;
  cfg->ptr = ptr;
  cfg->valType = valType;
  cfg->cfgType = cfgType;
  cfg->minValue = minVal;
  cfg->maxValue = maxVal;
  cfg->ptrLength = ptrLength;
  cfg->unitType = unitType;
  cfg->cfgStatus = TSDB_CFG_CSTATUS_NONE;
}