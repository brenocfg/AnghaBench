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
struct TYPE_6__ {int /*<<< orphan*/  acct; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  STabObj ;
typedef  TYPE_2__ SDbObj ;
typedef  int /*<<< orphan*/  SAcctObj ;

/* Variables and functions */
 int TSDB_CODE_INVALID_TABLE ; 
 int TSDB_CODE_MONITOR_DB_FORBEIDDEN ; 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  dropAllMetersOfMetric (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dropMeterImp (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  meterSdb ; 
 scalar_t__ mgmtCheckIsMonitorDB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mgmtGetAcct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mgmtGetMeter (char*) ; 
 scalar_t__ mgmtIsNormalMeter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdbDeleteRow (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsMonitorDbName ; 

int mgmtDropMeter(SDbObj *pDb, char *meterId, int ignore) {
  STabObj * pMeter;
  SAcctObj *pAcct;

  pMeter = mgmtGetMeter(meterId);
  if (pMeter == NULL) {
    if (ignore) {
      return TSDB_CODE_SUCCESS;
    } else {
      return TSDB_CODE_INVALID_TABLE;
    }
  }

  pAcct = mgmtGetAcct(pDb->cfg.acct);

  // 0.log
  if (mgmtCheckIsMonitorDB(pDb->name, tsMonitorDbName)) {
    return TSDB_CODE_MONITOR_DB_FORBEIDDEN;
  }

  if (mgmtIsNormalMeter(pMeter)) {
    return dropMeterImp(pDb, pMeter, pAcct);
  } else {
    // remove a metric
    /*
    if (pMeter->numOfMeters > 0) {
      assert(pMeter->pSkipList != NULL && pMeter->pSkipList->nSize > 0);
      return TSDB_CODE_RELATED_TABLES_EXIST;
    }
    */
    // first delet all meters of metric
    dropAllMetersOfMetric(pDb, pMeter, pAcct);

    // finally delete metric
    sdbDeleteRow(meterSdb, pMeter);
  }

  return 0;
}