#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {scalar_t__ meterType; size_t numOfColumns; scalar_t__ schema; int /*<<< orphan*/  meterId; int /*<<< orphan*/  pTagData; } ;
typedef  TYPE_1__ STabObj ;
typedef  TYPE_2__ SSchema ;

/* Variables and functions */
 scalar_t__ TSDB_METER_METRIC ; 
 scalar_t__ TSDB_METER_MTABLE ; 
 scalar_t__ TSDB_METER_OTABLE ; 
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mgmtGetMeter (int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

int32_t mgmtFindColumnIndex(STabObj *pMeter, const char *colName) {
  STabObj *pMetric = NULL;
  SSchema *schema = NULL;

  if (pMeter->meterType == TSDB_METER_OTABLE || pMeter->meterType == TSDB_METER_METRIC) {
    schema = (SSchema *)pMeter->schema;
    for (int32_t i = 0; i < pMeter->numOfColumns; i++) {
      if (strcasecmp(schema[i].name, colName) == 0) {
        return i;
      }
    }

  } else if (pMeter->meterType == TSDB_METER_MTABLE) {
    pMetric = mgmtGetMeter(pMeter->pTagData);
    if (pMetric == NULL) {
      mError("MTable not belongs to any metric, meter: %s", pMeter->meterId);
      return -1;
    }
    schema = (SSchema *)pMetric->schema;
    for (int32_t i = 0; i < pMetric->numOfColumns; i++) {
      if (strcasecmp(schema[i].name, colName) == 0) {
        return i;
      }
    }
  }

  return -1;
}