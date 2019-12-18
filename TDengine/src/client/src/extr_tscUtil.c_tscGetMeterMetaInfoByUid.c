#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  size_t int32_t ;
struct TYPE_8__ {size_t numOfTables; TYPE_2__** pMeterInfo; } ;
struct TYPE_7__ {TYPE_1__* pMeterMeta; } ;
struct TYPE_6__ {scalar_t__ uid; } ;
typedef  TYPE_3__ SSqlCmd ;
typedef  int /*<<< orphan*/  SMeterMetaInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * tscGetMeterMetaInfo (TYPE_3__*,size_t) ; 

SMeterMetaInfo* tscGetMeterMetaInfoByUid(SSqlCmd* pCmd, uint64_t uid, int32_t* index) {
  int32_t k = -1;
  for (int32_t i = 0; i < pCmd->numOfTables; ++i) {
    if (pCmd->pMeterInfo[i]->pMeterMeta->uid == uid) {
      k = i;
      break;
    }
  }

  if (index != NULL) {
    *index = k;
  }

  return tscGetMeterMetaInfo(pCmd, k);
}