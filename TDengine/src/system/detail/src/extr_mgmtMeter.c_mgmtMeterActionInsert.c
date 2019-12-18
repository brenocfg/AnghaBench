#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  numOfTimeSeries; } ;
struct TYPE_27__ {TYPE_1__ acctInfo; } ;
struct TYPE_23__ {int maxSessions; int /*<<< orphan*/  acct; } ;
struct TYPE_26__ {int numOfVgroups; TYPE_3__ cfg; int /*<<< orphan*/  numOfTables; } ;
struct TYPE_22__ {int vgId; int sid; } ;
struct TYPE_25__ {int meterId; char* pTagData; scalar_t__ meterType; char* pSql; int numOfColumns; int /*<<< orphan*/ * pSkipList; int /*<<< orphan*/ * pHead; TYPE_2__ gid; scalar_t__ schema; } ;
struct TYPE_24__ {int dbName; int vgId; int numOfMeters; TYPE_5__** meterList; int /*<<< orphan*/  idPool; } ;
typedef  TYPE_4__ SVgObj ;
typedef  TYPE_5__ STabObj ;
typedef  int /*<<< orphan*/  SSchema ;
typedef  TYPE_6__ SDbObj ;
typedef  TYPE_7__ SAcctObj ;

/* Variables and functions */
 scalar_t__ TSDB_METER_STABLE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mError (char*,...) ; 
 int /*<<< orphan*/  mgmtAddMeterIntoMetric (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  mgmtAddMetricIntoDb (TYPE_6__*,TYPE_5__*) ; 
 TYPE_7__* mgmtGetAcct (int /*<<< orphan*/ ) ; 
 TYPE_6__* mgmtGetDb (int) ; 
 TYPE_6__* mgmtGetDbByMeterId (int) ; 
 TYPE_5__* mgmtGetMeter (char*) ; 
 TYPE_4__* mgmtGetVgroup (int) ; 
 scalar_t__ mgmtIsNormalMeter (TYPE_5__*) ; 
 scalar_t__ mgmtMeterCreateFromMetric (TYPE_5__*) ; 
 int /*<<< orphan*/  mgmtMoveVgroupToTail (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sdbMaster ; 
 int taosAllocateId (int /*<<< orphan*/ ) ; 

void *mgmtMeterActionInsert(void *row, char *str, int size, int *ssize) {
  STabObj * pMeter = NULL;
  SVgObj *  pVgroup = NULL;
  SDbObj *  pDb = NULL;
  STabObj * pMetric = NULL;
  SAcctObj *pAcct = NULL;

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

    pAcct = mgmtGetAcct(pDb->cfg.acct);
    // TODO : check if account exists.
    if (pAcct == NULL) {
      mError("account not exists");
      return NULL;
    }
  }

  if (mgmtMeterCreateFromMetric(pMeter)) {
    pMeter->pTagData = (char *)pMeter->schema;
    pMetric = mgmtGetMeter(pMeter->pTagData);
    assert(pMetric != NULL);
  }

  if (pMeter->meterType == TSDB_METER_STABLE) {
    pMeter->pSql = (char *)pMeter->schema + sizeof(SSchema) * pMeter->numOfColumns;
  }

  if (mgmtIsNormalMeter(pMeter)) {
    if (pMetric) mgmtAddMeterIntoMetric(pMetric, pMeter);

    if (!sdbMaster) {
      int sid = taosAllocateId(pVgroup->idPool);
      if (sid != pMeter->gid.sid) {
        mError("sid:%d is not matched from the master:%d", sid, pMeter->gid.sid);
        return NULL;
      }
    }

    pAcct->acctInfo.numOfTimeSeries += (pMeter->numOfColumns - 1);
    pVgroup->numOfMeters++;
    pDb->numOfTables++;
    pVgroup->meterList[pMeter->gid.sid] = pMeter;

    if (pVgroup->numOfMeters >= pDb->cfg.maxSessions - 1 && pDb->numOfVgroups > 1) mgmtMoveVgroupToTail(pDb, pVgroup);
  } else {
    // insert a metric
    pMeter->pHead = NULL;
    pMeter->pSkipList = NULL;
    pDb = mgmtGetDbByMeterId(pMeter->meterId);
    if (pDb) {
      mgmtAddMetricIntoDb(pDb, pMeter);
    }
  }

  return NULL;
}