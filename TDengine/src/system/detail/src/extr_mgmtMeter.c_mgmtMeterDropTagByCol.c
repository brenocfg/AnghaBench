#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_12__ {int cols; scalar_t__ data; int /*<<< orphan*/  type; int /*<<< orphan*/  meterId; } ;
struct TYPE_11__ {int numOfTags; int numOfColumns; int /*<<< orphan*/  meterId; scalar_t__ schema; } ;
struct TYPE_10__ {int col; int /*<<< orphan*/  schema; scalar_t__ pos; } ;
typedef  TYPE_1__ SchemaUnit ;
typedef  TYPE_2__ STabObj ;
typedef  int /*<<< orphan*/  SSchema ;
typedef  TYPE_3__ SMeterBatchUpdateMsg ;

/* Variables and functions */
 int /*<<< orphan*/  SDB_TYPE_DELETE ; 
 scalar_t__ TSDB_CODE_APP_ERROR ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_METER_ID_LEN ; 
 int /*<<< orphan*/  mError (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mTrace (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  meterSdb ; 
 scalar_t__ mgmtGetTagsLength (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mgmtIsMetric (TYPE_2__*) ; 
 scalar_t__ sdbBatchUpdateRow (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  tfree (TYPE_3__*) ; 

int32_t mgmtMeterDropTagByCol(STabObj *pMetric, int col) {
  if (pMetric == NULL || (!mgmtIsMetric(pMetric)) || col <= 0 || col >= pMetric->numOfTags) return TSDB_CODE_APP_ERROR;

  // Pack message to do batch update
  uint32_t              size = sizeof(SMeterBatchUpdateMsg) + sizeof(SchemaUnit);
  SMeterBatchUpdateMsg *msg = (SMeterBatchUpdateMsg *)malloc(size);
  memset(msg, 0, size);

  memcpy(msg->meterId, pMetric->meterId, TSDB_METER_ID_LEN);
  msg->type = SDB_TYPE_DELETE;  // TODO: what should here be ?
  msg->cols = 1;

  ((SchemaUnit *)(msg->data))->col = col;
  ((SchemaUnit *)(msg->data))->pos = mgmtGetTagsLength(pMetric, col) + TSDB_METER_ID_LEN;
  ((SchemaUnit *)(msg->data))->schema = *(SSchema *)(pMetric->schema + sizeof(SSchema) * (pMetric->numOfColumns + col));

  int32_t ret = sdbBatchUpdateRow(meterSdb, msg, size);
  tfree(msg);

  if (ret < 0) {
    mError("Failed to drop tag column: %d from table: %s", col, pMetric->meterId);
    return TSDB_CODE_APP_ERROR;
  }

  mTrace("Succeed to drop tag column: %d from table: %s", col, pMetric->meterId);
  return TSDB_CODE_SUCCESS;
}