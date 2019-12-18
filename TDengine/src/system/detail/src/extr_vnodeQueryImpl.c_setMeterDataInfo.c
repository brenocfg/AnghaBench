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
typedef  void* int32_t ;
struct TYPE_3__ {void* meterOrderIdx; void* groupIdx; int /*<<< orphan*/ * pMeterObj; } ;
typedef  int /*<<< orphan*/  SMeterObj ;
typedef  TYPE_1__ SMeterDataInfo ;

/* Variables and functions */

void setMeterDataInfo(SMeterDataInfo *pMeterDataInfo, SMeterObj *pMeterObj, int32_t meterIdx, int32_t groupId) {
  pMeterDataInfo->pMeterObj = pMeterObj;
  pMeterDataInfo->groupIdx = groupId;
  pMeterDataInfo->meterOrderIdx = meterIdx;
}