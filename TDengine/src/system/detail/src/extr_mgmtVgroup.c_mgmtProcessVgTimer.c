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
struct TYPE_2__ {scalar_t__ vgStatus; int /*<<< orphan*/ * vgTimer; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ SDbObj ;

/* Variables and functions */
 scalar_t__ TSDB_VG_STATUS_IN_PROGRESS ; 
 scalar_t__ TSDB_VG_STATUS_READY ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void mgmtProcessVgTimer(void *handle, void *tmrId) {
  SDbObj *pDb = (SDbObj *)handle;
  if (pDb == NULL) return;

  if (pDb->vgStatus > TSDB_VG_STATUS_IN_PROGRESS) {
    mTrace("db:%s, set vgstatus from %d to %d", pDb->name, pDb->vgStatus, TSDB_VG_STATUS_READY);
    pDb->vgStatus = TSDB_VG_STATUS_READY;
  }

  pDb->vgTimer = NULL;
}