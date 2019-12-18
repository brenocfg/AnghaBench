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
typedef  size_t int32_t ;
struct TYPE_4__ {size_t numOfTables; int /*<<< orphan*/ * pMeterInfo; } ;
typedef  TYPE_1__ SSqlCmd ;
typedef  int /*<<< orphan*/  SMeterMetaInfo ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  tscClearMeterMetaInfo (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tscGetMeterMetaInfo (TYPE_1__*,size_t) ; 

void tscRemoveMeterMetaInfo(SSqlCmd* pCmd, int32_t index, bool removeFromCache) {
  if (index < 0 || index >= pCmd->numOfTables) {
    return;
  }

  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, index);

  tscClearMeterMetaInfo(pMeterMetaInfo, removeFromCache);
  free(pMeterMetaInfo);

  int32_t after = pCmd->numOfTables - index - 1;
  if (after > 0) {
    memmove(&pCmd->pMeterInfo[index], &pCmd->pMeterInfo[index + 1], after * sizeof(void*));
  }

  pCmd->numOfTables -= 1;
}