#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ isDirty; int /*<<< orphan*/  schema; int /*<<< orphan*/  pTagData; } ;
typedef  TYPE_1__ STabObj ;

/* Variables and functions */
 int /*<<< orphan*/  addMeterIntoMetricIndex (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* mgmtGetMeter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmtMeterActionReset (TYPE_1__*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  removeMeterFromMetricIndex (TYPE_1__*,TYPE_1__*) ; 

void *mgmtMeterActionUpdate(void *row, char *str, int size, int *ssize) {
  STabObj *pMeter = NULL;
  STabObj *pMetric = NULL;

  pMeter = (STabObj *)row;
  STabObj *pNew = (STabObj *)str;

  if (pNew->isDirty) {
    pMetric = mgmtGetMeter(pMeter->pTagData);
    removeMeterFromMetricIndex(pMetric, pMeter);
  }
  mgmtMeterActionReset(pMeter, str, size, NULL);
  pMeter->pTagData = pMeter->schema;
  if (pNew->isDirty) {
    addMeterIntoMetricIndex(pMetric, pMeter);
    pMeter->isDirty = 0;
  }

  return NULL;
}