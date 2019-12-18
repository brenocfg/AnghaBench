#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  pMetricMeta; scalar_t__ pMeterMeta; } ;
struct TYPE_7__ {int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ SSqlObj ;
typedef  TYPE_2__ SMeterMetaInfo ;
typedef  int /*<<< orphan*/  SMeterMeta ;

/* Variables and functions */
 int UTIL_METER_IS_METRIC (TYPE_2__*) ; 
 int /*<<< orphan*/  taosClearDataCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taosGetDataFromCache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosRemoveDataFromCache (int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  tscCacheHandle ; 
 TYPE_2__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

int tscProcessAlterTableMsgRsp(SSqlObj *pSql) {
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(&pSql->cmd, 0);

  SMeterMeta *pMeterMeta = taosGetDataFromCache(tscCacheHandle, pMeterMetaInfo->name);
  if (pMeterMeta == NULL) { /* not in cache, abort */
    return 0;
  }

  tscTrace("%p force release metermeta in cache after alter-table: %s", pSql, pMeterMetaInfo->name);
  taosRemoveDataFromCache(tscCacheHandle, (void **)&pMeterMeta, true);

  if (pMeterMetaInfo->pMeterMeta) {
    bool isMetric = UTIL_METER_IS_METRIC(pMeterMetaInfo);

    taosRemoveDataFromCache(tscCacheHandle, (void **)&(pMeterMetaInfo->pMeterMeta), true);
    taosRemoveDataFromCache(tscCacheHandle, (void **)&(pMeterMetaInfo->pMetricMeta), true);

    if (isMetric) {  // if it is a metric, reset whole query cache
      tscTrace("%p reset query cache since table:%s is stable", pSql, pMeterMetaInfo->name);
      taosClearDataCache(tscCacheHandle);
    }
  }

  return 0;
}