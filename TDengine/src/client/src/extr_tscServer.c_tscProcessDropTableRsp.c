#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pMetricMeta; scalar_t__ pMeterMeta; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ SSqlObj ;
typedef  TYPE_2__ SMeterMetaInfo ;
typedef  int /*<<< orphan*/  SMeterMeta ;

/* Variables and functions */
 int /*<<< orphan*/ * taosGetDataFromCache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosRemoveDataFromCache (int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  tscCacheHandle ; 
 TYPE_2__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

int tscProcessDropTableRsp(SSqlObj *pSql) {
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(&pSql->cmd, 0);

  SMeterMeta *pMeterMeta = taosGetDataFromCache(tscCacheHandle, pMeterMetaInfo->name);
  if (pMeterMeta == NULL) {
    /* not in cache, abort */
    return 0;
  }

  /*
   * 1. if a user drops one table, which is the only table in a vnode, remove operation will incur vnode to be removed.
   * 2. Then, a user creates a new metric followed by a table with identical name of removed table but different schema,
   * here the table will reside in a new vnode.
   * The cached information is expired, however, we may have lost the ref of original meter. So, clear whole cache
   * instead.
   */
  tscTrace("%p force release metermeta after drop table:%s", pSql, pMeterMetaInfo->name);
  taosRemoveDataFromCache(tscCacheHandle, (void **)&pMeterMeta, true);

  if (pMeterMetaInfo->pMeterMeta) {
    taosRemoveDataFromCache(tscCacheHandle, (void **)&(pMeterMetaInfo->pMeterMeta), true);
    taosRemoveDataFromCache(tscCacheHandle, (void **)&(pMeterMetaInfo->pMetricMeta), true);
  }

  return 0;
}