#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  acct; } ;
struct TYPE_21__ {TYPE_2__ cfg; } ;
struct TYPE_17__ {size_t sid; int /*<<< orphan*/  vgId; } ;
struct TYPE_20__ {scalar_t__ meterType; char* pSql; int numOfColumns; char* pTagData; scalar_t__ schema; TYPE_1__ gid; int /*<<< orphan*/  meterId; scalar_t__ numOfMeters; } ;
struct TYPE_19__ {int /*<<< orphan*/  idPool; TYPE_4__** meterList; } ;
typedef  TYPE_3__ SVgObj ;
typedef  TYPE_4__ STabObj ;
typedef  int /*<<< orphan*/  SSchema ;
typedef  TYPE_5__ SDbObj ;
typedef  int /*<<< orphan*/  SAcctObj ;

/* Variables and functions */
 int /*<<< orphan*/  SDB_KEYTYPE_STRING ; 
 int TSDB_MAX_COLUMNS ; 
 scalar_t__ TSDB_MAX_SQL_LEN ; 
 scalar_t__ TSDB_METER_STABLE ; 
 int /*<<< orphan*/  mError (char*,...) ; 
 int /*<<< orphan*/  mTrace (char*) ; 
 int /*<<< orphan*/ * meterSdb ; 
 int /*<<< orphan*/  mgmtAddMeterIntoMetric (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mgmtAddMeterStatisticToAcct (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmtAddMetricIntoDb (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mgmtDirectory ; 
 int /*<<< orphan*/ * mgmtGetAcct (int /*<<< orphan*/ ) ; 
 TYPE_5__* mgmtGetDbByMeterId (int /*<<< orphan*/ ) ; 
 TYPE_4__* mgmtGetMeter (char*) ; 
 TYPE_3__* mgmtGetVgroup (int /*<<< orphan*/ ) ; 
 scalar_t__ mgmtIsMetric (TYPE_4__*) ; 
 scalar_t__ mgmtIsNormalMeter (TYPE_4__*) ; 
 int /*<<< orphan*/  mgmtMeterAction ; 
 int /*<<< orphan*/  mgmtMeterActionInit () ; 
 scalar_t__ mgmtMeterCreateFromMetric (TYPE_4__*) ; 
 int /*<<< orphan*/  mgmtSetVgroupIdPool () ; 
 void* sdbFetchRow (int /*<<< orphan*/ *,void*,void**) ; 
 int /*<<< orphan*/ * sdbOpenTable (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosIdPoolMarkStatus (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  tsMaxTables ; 

int mgmtInitMeters() {
  void *    pNode = NULL;
  SVgObj *  pVgroup = NULL;
  STabObj * pMeter = NULL;
  STabObj * pMetric = NULL;
  SDbObj *  pDb = NULL;
  SAcctObj *pAcct = NULL;

  // TODO: Make sure this function only run once
  mgmtMeterActionInit();

  meterSdb = sdbOpenTable(tsMaxTables, sizeof(STabObj) + sizeof(SSchema) * TSDB_MAX_COLUMNS + TSDB_MAX_SQL_LEN,
                          "meters", SDB_KEYTYPE_STRING, mgmtDirectory, mgmtMeterAction);
  if (meterSdb == NULL) {
    mError("failed to init meter data");
    return -1;
  }

  pNode = NULL;
  while (1) {
    pNode = sdbFetchRow(meterSdb, pNode, (void **)&pMeter);
    if (pMeter == NULL) break;
    if (mgmtIsMetric(pMeter)) pMeter->numOfMeters = 0;
  }

  pNode = NULL;
  while (1) {
    pNode = sdbFetchRow(meterSdb, pNode, (void **)&pMeter);
    if (pMeter == NULL) break;

    pDb = mgmtGetDbByMeterId(pMeter->meterId);
    if (pDb == NULL) {
      mError("failed to get db: %s", pMeter->meterId);
      continue;
    }

    if (mgmtIsNormalMeter(pMeter)) {
      pVgroup = mgmtGetVgroup(pMeter->gid.vgId);
      if (pVgroup == NULL || pVgroup->meterList == NULL) {
        mError("failed to get vgroup:%i", pMeter->gid.vgId);
        continue;
      }
      pVgroup->meterList[pMeter->gid.sid] = pMeter;
      taosIdPoolMarkStatus(pVgroup->idPool, pMeter->gid.sid, 1);

      if (pMeter->meterType == TSDB_METER_STABLE) {
        pMeter->pSql = (char *)pMeter->schema + sizeof(SSchema) * pMeter->numOfColumns;
      }

      if (mgmtMeterCreateFromMetric(pMeter)) {
        pMeter->pTagData = (char *)pMeter->schema;  // + sizeof(SSchema)*pMeter->numOfColumns;
        pMetric = mgmtGetMeter(pMeter->pTagData);
        if (pMetric) mgmtAddMeterIntoMetric(pMetric, pMeter);
      }

      pAcct = mgmtGetAcct(pDb->cfg.acct);
      if (pAcct) mgmtAddMeterStatisticToAcct(pMeter, pAcct);
    } else {
      if (pDb) mgmtAddMetricIntoDb(pDb, pMeter);
    }
  }

  mgmtSetVgroupIdPool();

  mTrace("meter is initialized");
  return 0;
}