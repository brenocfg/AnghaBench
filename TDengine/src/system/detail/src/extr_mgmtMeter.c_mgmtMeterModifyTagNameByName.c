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
 int /*<<< orphan*/  TSDB_CODE_APP_ERROR ; 
 int /*<<< orphan*/  TSDB_CODE_INVALID_MSG_TYPE ; 
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int mgmtFindTagCol (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  mgmtIsMetric (TYPE_1__*) ; 
 int /*<<< orphan*/  mgmtMeterModifyTagNameByCol (TYPE_1__*,int,char const*) ; 

int32_t mgmtMeterModifyTagNameByName(STabObj *pMetric, const char *oname, const char *nname) {
  if (pMetric == NULL || (!mgmtIsMetric(pMetric))) return TSDB_CODE_APP_ERROR;

  int index = mgmtFindTagCol(pMetric, oname);
  if (index < 0) {
    // Tag name does not exist
    mError("Failed to modify table %s tag column, oname: %s, nname: %s", pMetric->meterId, oname, nname);
    return TSDB_CODE_INVALID_MSG_TYPE;
  }

  return mgmtMeterModifyTagNameByCol(pMetric, index, nname);
}