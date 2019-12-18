#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  pTagData; } ;
typedef  TYPE_1__ STabObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_APP_ERROR ; 
 int /*<<< orphan*/  TSDB_CODE_INVALID_MSG_TYPE ; 
 int mgmtFindTagCol (TYPE_1__*,char*) ; 
 TYPE_1__* mgmtGetMeter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmtMeterCreateFromMetric (TYPE_1__*) ; 
 int /*<<< orphan*/  mgmtMeterModifyTagValueByCol (TYPE_1__*,int,char*) ; 

int32_t mgmtMeterModifyTagValueByName(STabObj *pMeter, char *tagName, char *nContent) {
  if (pMeter == NULL || tagName == NULL || nContent == NULL || (!mgmtMeterCreateFromMetric(pMeter)))
    return TSDB_CODE_INVALID_MSG_TYPE;

  STabObj *pMetric = mgmtGetMeter(pMeter->pTagData);
  if (pMetric == NULL) return TSDB_CODE_APP_ERROR;

  int col = mgmtFindTagCol(pMetric, tagName);
  if (col < 0) return TSDB_CODE_APP_ERROR;

  return mgmtMeterModifyTagValueByCol(pMeter, col, nContent);
}