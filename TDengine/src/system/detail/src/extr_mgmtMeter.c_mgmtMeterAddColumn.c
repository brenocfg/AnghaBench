#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_16__ {int numOfTimeSeries; } ;
struct TYPE_20__ {TYPE_2__ acctInfo; } ;
struct TYPE_15__ {int /*<<< orphan*/  acct; } ;
struct TYPE_19__ {int /*<<< orphan*/  name; TYPE_1__ cfg; } ;
struct TYPE_18__ {scalar_t__ colId; int /*<<< orphan*/  name; } ;
struct TYPE_17__ {scalar_t__ meterType; int numOfColumns; int numOfTags; int numOfMeters; scalar_t__ sversion; scalar_t__ nextColId; struct TYPE_17__* next; struct TYPE_17__* pHead; scalar_t__ schemaSize; scalar_t__ schema; int /*<<< orphan*/  meterId; } ;
typedef  TYPE_3__ STabObj ;
typedef  TYPE_4__ SSchema ;
typedef  TYPE_5__ SDbObj ;
typedef  TYPE_6__ SAcctObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_APP_ERROR ; 
 int /*<<< orphan*/  TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_METER_METRIC ; 
 scalar_t__ TSDB_METER_MTABLE ; 
 scalar_t__ TSDB_METER_OTABLE ; 
 scalar_t__ TSDB_METER_STABLE ; 
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  meterSdb ; 
 scalar_t__ mgmtFindColumnIndex (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* mgmtGetAcct (int /*<<< orphan*/ ) ; 
 TYPE_5__* mgmtGetDbByMeterId (int /*<<< orphan*/ ) ; 
 scalar_t__ mgmtIsNormalMeter (TYPE_3__*) ; 
 scalar_t__ realloc (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sdbUpdateRow (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 

int32_t mgmtMeterAddColumn(STabObj *pMeter, SSchema schema[], int ncols) {
  SAcctObj *pAcct = NULL;
  SDbObj *  pDb = NULL;

  if (pMeter == NULL || pMeter->meterType == TSDB_METER_MTABLE || pMeter->meterType == TSDB_METER_STABLE || ncols <= 0)
    return TSDB_CODE_APP_ERROR;

  // ASSUMPTION: no two tags are the same
  for (int i = 0; i < ncols; i++)
    if (mgmtFindColumnIndex(pMeter, schema[i].name) > 0) return TSDB_CODE_APP_ERROR;

  pDb = mgmtGetDbByMeterId(pMeter->meterId);
  if (pDb == NULL) {
    mError("meter: %s not belongs to any database", pMeter->meterId);
    return TSDB_CODE_APP_ERROR;
  }

  pAcct = mgmtGetAcct(pDb->cfg.acct);
  if (pAcct == NULL) {
    mError("DB: %s not belongs to andy account", pDb->name);
    return TSDB_CODE_APP_ERROR;
  }

  pMeter->schema = realloc(pMeter->schema, pMeter->schemaSize + sizeof(SSchema) * ncols);

  if (pMeter->meterType == TSDB_METER_OTABLE) {
    memcpy(pMeter->schema + pMeter->schemaSize, schema, sizeof(SSchema) * ncols);
  } else if (pMeter->meterType == TSDB_METER_METRIC) {
    memmove(pMeter->schema + sizeof(SSchema) * (pMeter->numOfColumns + ncols),
            pMeter->schema + sizeof(SSchema) * pMeter->numOfColumns, sizeof(SSchema) * pMeter->numOfTags);
    memcpy(pMeter->schema + sizeof(SSchema) * pMeter->numOfColumns, schema, sizeof(SSchema) * ncols);
  }

  SSchema *tschema = (SSchema *)(pMeter->schema + sizeof(SSchema) * pMeter->numOfColumns);
  for (int i = 0; i < ncols; i++) tschema[i].colId = pMeter->nextColId++;

  pMeter->schemaSize += sizeof(SSchema) * ncols;
  pMeter->numOfColumns += ncols;
  pMeter->sversion++;
  if (mgmtIsNormalMeter(pMeter))
    pAcct->acctInfo.numOfTimeSeries += ncols;
  else
    pAcct->acctInfo.numOfTimeSeries += (ncols * pMeter->numOfMeters);
  sdbUpdateRow(meterSdb, pMeter, 0, 1);

  if (pMeter->meterType == TSDB_METER_METRIC) {
    for (STabObj *pObj = pMeter->pHead; pObj != NULL; pObj = pObj->next) {
      pObj->numOfColumns++;
      pObj->nextColId = pMeter->nextColId;
      pObj->sversion = pMeter->sversion;
      sdbUpdateRow(meterSdb, pObj, 0, 1);
    }
  }

  return TSDB_CODE_SUCCESS;
}