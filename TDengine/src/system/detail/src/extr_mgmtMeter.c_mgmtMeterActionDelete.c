#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  numOfTables; } ;
struct TYPE_17__ {size_t sid; int /*<<< orphan*/  vgId; } ;
struct TYPE_19__ {char* pTagData; int /*<<< orphan*/  meterId; TYPE_1__ gid; scalar_t__ schema; } ;
struct TYPE_18__ {scalar_t__ numOfMeters; int /*<<< orphan*/  idPool; int /*<<< orphan*/ ** meterList; int /*<<< orphan*/  dbName; int /*<<< orphan*/  vgId; } ;
typedef  TYPE_2__ SVgObj ;
typedef  TYPE_3__ STabObj ;
typedef  TYPE_4__ SDbObj ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* mgmtGetDb (int /*<<< orphan*/ ) ; 
 TYPE_4__* mgmtGetDbByMeterId (int /*<<< orphan*/ ) ; 
 TYPE_3__* mgmtGetMeter (char*) ; 
 TYPE_2__* mgmtGetVgroup (int /*<<< orphan*/ ) ; 
 scalar_t__ mgmtIsNormalMeter (TYPE_3__*) ; 
 scalar_t__ mgmtMeterCreateFromMetric (TYPE_3__*) ; 
 int /*<<< orphan*/  mgmtMoveVgroupToHead (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mgmtRemoveMeterFromMetric (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  mgmtRemoveMetricFromDb (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  taosFreeId (int /*<<< orphan*/ ,size_t) ; 

void *mgmtMeterActionDelete(void *row, char *str, int size, int *ssize) {
  STabObj *pMeter = NULL;
  SVgObj * pVgroup = NULL;
  SDbObj * pDb = NULL;
  STabObj *pMetric = NULL;

  pMeter = (STabObj *)row;

  if (mgmtIsNormalMeter(pMeter)) {
    pVgroup = mgmtGetVgroup(pMeter->gid.vgId);
    if (pVgroup == NULL) {
      mError("id:%s not in vgroup:%d", pMeter->meterId, pMeter->gid.vgId);
      return NULL;
    }

    pDb = mgmtGetDb(pVgroup->dbName);
    if (pDb == NULL) {
      mError("vgroup:%d not in DB:%s", pVgroup->vgId, pVgroup->dbName);
      return NULL;
    }
  }

  if (mgmtMeterCreateFromMetric(pMeter)) {
    pMeter->pTagData = (char *)pMeter->schema;
    pMetric = mgmtGetMeter(pMeter->pTagData);
    assert(pMetric != NULL);
  }

  if (mgmtIsNormalMeter(pMeter)) {
    if (pMetric) mgmtRemoveMeterFromMetric(pMetric, pMeter);

    pVgroup->meterList[pMeter->gid.sid] = NULL;
    pVgroup->numOfMeters--;
    pDb->numOfTables--;
    taosFreeId(pVgroup->idPool, pMeter->gid.sid);

    if (pVgroup->numOfMeters > 0) mgmtMoveVgroupToHead(pDb, pVgroup);
  } else {
    // remove a metric
    // remove all the associated meters

    pDb = mgmtGetDbByMeterId(pMeter->meterId);
    if (pDb) mgmtRemoveMetricFromDb(pDb, pMeter);
  }

  return NULL;
}