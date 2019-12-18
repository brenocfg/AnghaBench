#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * pMeterObj; TYPE_2__* pQuery; } ;
struct TYPE_10__ {TYPE_1__ runtimeEnv; } ;
struct TYPE_9__ {int ekey; int /*<<< orphan*/  skey; } ;
typedef  int TSKEY ;
typedef  TYPE_1__ SQueryRuntimeEnv ;
typedef  TYPE_2__ SQuery ;
typedef  int /*<<< orphan*/  SPointInterpoSupporter ;
typedef  TYPE_3__ SMeterQuerySupportObj ;
typedef  int /*<<< orphan*/  SMeterObj ;

/* Variables and functions */
 int /*<<< orphan*/  getAlignedIntervalQueryRange (TYPE_2__*,int,int /*<<< orphan*/ ,int) ; 
 int getNeighborPoints (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isPointInterpoQuery (TYPE_2__*) ; 

__attribute__((used)) static bool doGetQueryPos(TSKEY key, SMeterQuerySupportObj *pSupporter, SPointInterpoSupporter *pPointInterpSupporter) {
  SQueryRuntimeEnv *pRuntimeEnv = &pSupporter->runtimeEnv;
  SQuery *          pQuery = pRuntimeEnv->pQuery;
  SMeterObj *       pMeterObj = pRuntimeEnv->pMeterObj;

  /* key in query range. If not, no qualified in disk file */
  if (key != -1 && key <= pQuery->ekey) {
    if (isPointInterpoQuery(pQuery)) { /* no qualified data in this query range */
      return getNeighborPoints(pSupporter, pMeterObj, pPointInterpSupporter);
    } else {
      getAlignedIntervalQueryRange(pQuery, key, pQuery->skey, pQuery->ekey);
      return true;
    }
  } else {  // key > pQuery->ekey, abort for normal query, continue for interp query
    if (isPointInterpoQuery(pQuery)) {
      return getNeighborPoints(pSupporter, pMeterObj, pPointInterpSupporter);
    } else {
      return false;
    }
  }
}