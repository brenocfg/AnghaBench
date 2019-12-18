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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct TYPE_6__ {scalar_t__ maxSessions; } ;
struct TYPE_7__ {TYPE_3__** meterList; TYPE_1__ cfg; } ;
typedef  TYPE_2__ SVnodeObj ;
typedef  TYPE_3__ SMeterObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_ACTION_IN_PROGRESS ; 
 int /*<<< orphan*/  TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_METER_STATE_DELETED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vnodeIsSafeToDeleteMeter (TYPE_2__*,int) ; 

__attribute__((used)) static int32_t vnodeMarkAllMetersDropped(SVnodeObj* pVnode) {
  if (pVnode->meterList == NULL) {
    assert(pVnode->cfg.maxSessions == 0);
    return TSDB_CODE_SUCCESS;
  }

  bool ready = true;
  for (int sid = 0; sid < pVnode->cfg.maxSessions; ++sid) {
    if (!vnodeIsSafeToDeleteMeter(pVnode, sid)) {
      ready = false;
    } else { // set the meter is to be deleted
      SMeterObj* pObj = pVnode->meterList[sid];
      if (pObj != NULL) {
        pObj->state = TSDB_METER_STATE_DELETED;
      }
    }
  }

  return ready? TSDB_CODE_SUCCESS:TSDB_CODE_ACTION_IN_PROGRESS;
}