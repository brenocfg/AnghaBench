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
typedef  int /*<<< orphan*/  tSkipListKey ;
typedef  size_t int16_t ;
struct TYPE_6__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int numOfColumns; char* pTagData; scalar_t__ schema; } ;
typedef  TYPE_1__ STabObj ;
typedef  TYPE_2__ SSchema ;

/* Variables and functions */
 int TSDB_METER_ID_LEN ; 
 int /*<<< orphan*/  tSkipListCreateKey (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void createKeyFromTagValue(STabObj *pMetric, STabObj *pMeter, tSkipListKey *pKey) {
  SSchema *     pTagSchema = (SSchema *)(pMetric->schema + pMetric->numOfColumns * sizeof(SSchema));
  const int16_t KEY_COLUMN_OF_TAGS = 0;

  char *tagVal = pMeter->pTagData + TSDB_METER_ID_LEN;  // tag start position
  *pKey = tSkipListCreateKey(pTagSchema[KEY_COLUMN_OF_TAGS].type, tagVal, pTagSchema[KEY_COLUMN_OF_TAGS].bytes);
}