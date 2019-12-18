#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_13__ {int /*<<< orphan*/  bytes; } ;
struct TYPE_12__ {int numOfTags; int numOfColumns; int isDirty; int /*<<< orphan*/  meterId; scalar_t__ pTagData; scalar_t__ schema; } ;
typedef  TYPE_1__ STabObj ;
typedef  TYPE_2__ SSchema ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_APP_ERROR ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int TSDB_MAX_BYTES_PER_ROW ; 
 scalar_t__ TSDB_METER_ID_LEN ; 
 int /*<<< orphan*/  addMeterIntoMetricIndex (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mError (char*,...) ; 
 int /*<<< orphan*/  mTrace (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  meterSdb ; 
 TYPE_1__* mgmtGetMeter (scalar_t__) ; 
 scalar_t__ mgmtGetTagsLength (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mgmtMeterActionEncode (TYPE_1__*,char*,int,int*) ; 
 int /*<<< orphan*/  mgmtMeterCreateFromMetric (TYPE_1__*) ; 
 int /*<<< orphan*/  removeMeterFromMetricIndex (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ sdbUpdateRow (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  tfree (char*) ; 

int32_t mgmtMeterModifyTagValueByCol(STabObj *pMeter, int col, const char *nContent) {
  int rowSize = 0;
  if (pMeter == NULL || nContent == NULL || (!mgmtMeterCreateFromMetric(pMeter))) return TSDB_CODE_APP_ERROR;

  STabObj *pMetric = mgmtGetMeter(pMeter->pTagData);
  assert(pMetric != NULL);

  if (col < 0 || col > pMetric->numOfTags) return TSDB_CODE_APP_ERROR;

  SSchema *schema = (SSchema *)(pMetric->schema + (pMetric->numOfColumns + col) * sizeof(SSchema));

  if (col == 0) {
    pMeter->isDirty = 1;
    removeMeterFromMetricIndex(pMetric, pMeter);
  }
  memcpy(pMeter->pTagData + mgmtGetTagsLength(pMetric, col) + TSDB_METER_ID_LEN, nContent, schema->bytes);
  if (col == 0) {
    addMeterIntoMetricIndex(pMetric, pMeter);
  }

  // Encode the string
  int   size = sizeof(STabObj) + TSDB_MAX_BYTES_PER_ROW + 1;
  char *msg = (char *)malloc(size);
  if (msg == NULL) {
    mError("failed to allocate message memory while modify tag value");
    return TSDB_CODE_APP_ERROR;
  }
  memset(msg, 0, size);

  mgmtMeterActionEncode(pMeter, msg, size, &rowSize);

  int32_t ret = sdbUpdateRow(meterSdb, msg, rowSize, 1);  // Need callback function
  tfree(msg);

  if (pMeter->isDirty) pMeter->isDirty = 0;

  if (ret < 0) {
    mError("Failed to modify tag column %d of table %s", col, pMeter->meterId);
    return TSDB_CODE_APP_ERROR;
  }

  mTrace("Succeed to modify tag column %d of table %s", col, pMeter->meterId);
  return TSDB_CODE_SUCCESS;
}