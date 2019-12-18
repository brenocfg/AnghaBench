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
typedef  int int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  pMeterInfo; int /*<<< orphan*/  numOfTables; } ;
typedef  TYPE_1__ SSqlCmd ;

/* Variables and functions */
 int /*<<< orphan*/  SSqlObj ; 
 int /*<<< orphan*/  cmd ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscRemoveMeterMetaInfo (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tscTrace (char*,char*,int /*<<< orphan*/ ) ; 

void tscRemoveAllMeterMetaInfo(SSqlCmd* pCmd, bool removeFromCache) {
  int64_t addr = offsetof(SSqlObj, cmd);

  tscTrace("%p deref the metric/meter meta in cache, numOfTables:%d", ((char*)pCmd - addr), pCmd->numOfTables);

  while (pCmd->numOfTables > 0) {
    tscRemoveMeterMetaInfo(pCmd, pCmd->numOfTables - 1, removeFromCache);
  }

  tfree(pCmd->pMeterInfo);
}