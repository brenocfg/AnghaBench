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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  meterId; } ;
typedef  TYPE_1__ STabObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_INVALID_TABLE ; 
 int /*<<< orphan*/  mTrace (char*,char*,int /*<<< orphan*/ ) ; 
 int mgmtFindTagCol (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mgmtIsMetric (TYPE_1__*) ; 
 int /*<<< orphan*/  mgmtMeterDropTagByCol (TYPE_1__*,int) ; 

int32_t mgmtMeterDropTagByName(STabObj *pMetric, char *name) {
  if (pMetric == NULL || (!mgmtIsMetric(pMetric))) {
    mTrace("Failed to drop tag name: %s from table: %s", name, pMetric->meterId);
    return TSDB_CODE_INVALID_TABLE;
  }

  int col = mgmtFindTagCol(pMetric, name);

  return mgmtMeterDropTagByCol(pMetric, col);
}