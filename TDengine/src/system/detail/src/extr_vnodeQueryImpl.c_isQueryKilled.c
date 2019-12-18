#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int killed; int /*<<< orphan*/ * pObj; } ;
typedef  int /*<<< orphan*/  SQuery ;
typedef  TYPE_1__ SQInfo ;
typedef  int /*<<< orphan*/  SMeterObj ;

/* Variables and functions */
 scalar_t__ GET_QINFO_ADDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TSDB_METER_STATE_DELETING ; 
 scalar_t__ vnodeIsMeterState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool isQueryKilled(SQuery *pQuery) {
  SQInfo *pQInfo = (SQInfo *)GET_QINFO_ADDR(pQuery);

  /*
   * check if the queried meter is going to be deleted.
   * if it will be deleted soon, stop current query ASAP.
   */
  SMeterObj *pMeterObj = pQInfo->pObj;
  if (vnodeIsMeterState(pMeterObj, TSDB_METER_STATE_DELETING)) {
    pQInfo->killed = 1;
    return true;
  }

  return (pQInfo->killed == 1);
}