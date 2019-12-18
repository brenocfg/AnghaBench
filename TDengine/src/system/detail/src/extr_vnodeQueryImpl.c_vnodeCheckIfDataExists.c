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
struct TYPE_4__ {int /*<<< orphan*/ * pQuery; } ;
typedef  TYPE_1__ SQueryRuntimeEnv ;
typedef  int /*<<< orphan*/  SQuery ;
typedef  int /*<<< orphan*/  SMeterObj ;

/* Variables and functions */
 int /*<<< orphan*/  QUERY_NOT_COMPLETED ; 
 int hasDataInCache (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int hasDataInDisk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setQueryStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vnodeCheckIfDataExists(SQueryRuntimeEnv *pRuntimeEnv, SMeterObj *pMeterObj, bool *dataInDisk, bool *dataInCache) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  *dataInCache = hasDataInCache(pRuntimeEnv, pMeterObj);
  *dataInDisk = hasDataInDisk(pQuery, pMeterObj);

  setQueryStatus(pQuery, QUERY_NOT_COMPLETED);
}