#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SSqlCmd ;

/* Variables and functions */

void tscClearSqlMetaInfoForce(SSqlCmd* pCmd) {
  /* remove the metermeta/metricmeta in cache */
  //    taosRemoveDataFromCache(tscCacheHandle, (void**)&(pCmd->pMeterMeta),
  //    true);
  //    taosRemoveDataFromCache(tscCacheHandle, (void**)&(pCmd->pMetricMeta),
  //    true);
}