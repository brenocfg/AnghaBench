#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {char* pTagData; scalar_t__ numOfColumns; scalar_t__ schema; } ;
typedef  TYPE_1__ STabObj ;
typedef  int /*<<< orphan*/  SSchema ;

/* Variables and functions */
 scalar_t__ TSDB_METER_ID_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* mgmtGetMeter (char*) ; 
 scalar_t__ mgmtGetTagsLength (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mgmtMeterCreateFromMetric (TYPE_1__*) ; 

char* mgmtMeterGetTag(STabObj* pMeter, int32_t col, SSchema* pTagColSchema) {
  if (!mgmtMeterCreateFromMetric(pMeter)) {
    return NULL;
  }

  STabObj* pMetric = mgmtGetMeter(pMeter->pTagData);
  int32_t  offset = mgmtGetTagsLength(pMetric, col) + TSDB_METER_ID_LEN;
  assert(offset > 0);

  if (pTagColSchema != NULL) {
    *pTagColSchema = ((SSchema*)pMetric->schema)[pMetric->numOfColumns + col];
  }

  return (pMeter->pTagData + offset);
}