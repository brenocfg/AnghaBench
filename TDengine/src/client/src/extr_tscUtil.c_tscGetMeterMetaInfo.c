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
typedef  size_t int32_t ;
struct TYPE_3__ {size_t numOfTables; int /*<<< orphan*/ ** pMeterInfo; } ;
typedef  TYPE_1__ SSqlCmd ;
typedef  int /*<<< orphan*/  SMeterMetaInfo ;

/* Variables and functions */

SMeterMetaInfo* tscGetMeterMetaInfo(SSqlCmd* pCmd, int32_t index) {
  if (pCmd == NULL || index >= pCmd->numOfTables || index < 0) {
    return NULL;
  }

  return pCmd->pMeterInfo[index];
}