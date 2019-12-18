#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * cacheBlocks; } ;
struct TYPE_14__ {int /*<<< orphan*/  vnode; scalar_t__ pCache; } ;
struct TYPE_13__ {scalar_t__ numOfBlocks; } ;
struct TYPE_12__ {TYPE_2__* pQuery; } ;
typedef  TYPE_1__ SQueryRuntimeEnv ;
typedef  TYPE_2__ SQuery ;
typedef  TYPE_3__ SMeterObj ;
typedef  TYPE_4__ SCacheInfo ;

/* Variables and functions */
 int cacheBoundaryCheck (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  getBasicCacheInfoSnapshot (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeFreeFieldsEx (TYPE_1__*) ; 

bool hasDataInCache(SQueryRuntimeEnv *pRuntimeEnv, SMeterObj *pMeterObj) {
  SQuery *    pQuery = pRuntimeEnv->pQuery;
  SCacheInfo *pCacheInfo = (SCacheInfo *)pMeterObj->pCache;

  /* no data in cache, return */
  if ((pCacheInfo == NULL) || (pCacheInfo->cacheBlocks == NULL)) {
    return false;
  }

  /* numOfBlocks value has been overwrite, release pFields data if exists */
  vnodeFreeFieldsEx(pRuntimeEnv);
  getBasicCacheInfoSnapshot(pQuery, pCacheInfo, pMeterObj->vnode);
  if (pQuery->numOfBlocks <= 0) {
    return false;
  }

  return cacheBoundaryCheck(pQuery, pMeterObj);
}