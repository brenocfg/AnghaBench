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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t int32_t ;
struct TYPE_6__ {scalar_t__ bytes; } ;
struct TYPE_5__ {int numOfColumns; char* pTagData; size_t numOfTags; scalar_t__ schema; } ;
typedef  TYPE_1__ STabObj ;
typedef  TYPE_2__ SSchema ;

/* Variables and functions */
 int TSDB_METER_ID_LEN ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t mgmtSetMeterTagValue(char *pTags, STabObj *pMetric, STabObj *pMeterObj) {
  SSchema *pTagSchema = (SSchema *)(pMetric->schema + pMetric->numOfColumns * sizeof(SSchema));

  char *tagVal = pMeterObj->pTagData + TSDB_METER_ID_LEN;  // tag start position

  uint32_t tagsLen = 0;
  for (int32_t i = 0; i < pMetric->numOfTags; ++i) {
    tagsLen += pTagSchema[i].bytes;
  }

  memcpy(pTags, tagVal, tagsLen);
  return tagsLen;
}