#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ tSkipListKey ;
typedef  size_t int16_t ;
struct TYPE_14__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int numOfColumns; int /*<<< orphan*/ * pSkipList; scalar_t__ schema; } ;
typedef  TYPE_2__ STabObj ;
typedef  TYPE_3__ SSchema ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SKIP_LIST_LEVEL ; 
 int /*<<< orphan*/  createKeyFromTagValue (TYPE_2__*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * tSkipListCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tSkipListDestroyKey (TYPE_1__*) ; 
 int /*<<< orphan*/  tSkipListPut (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,int) ; 

__attribute__((used)) static void addMeterIntoMetricIndex(STabObj *pMetric, STabObj *pMeter) {
  const int16_t KEY_COLUMN_OF_TAGS = 0;
  SSchema *     pTagSchema = (SSchema *)(pMetric->schema + pMetric->numOfColumns * sizeof(SSchema));

  if (pMetric->pSkipList == NULL) {
    pMetric->pSkipList = tSkipListCreate(MAX_SKIP_LIST_LEVEL, pTagSchema[KEY_COLUMN_OF_TAGS].type,
                    pTagSchema[KEY_COLUMN_OF_TAGS].bytes);
  }

  if (pMetric->pSkipList) {
    tSkipListKey key = {0};
    createKeyFromTagValue(pMetric, pMeter, &key);
    tSkipListPut(pMetric->pSkipList, pMeter, &key, 1);

    tSkipListDestroyKey(&key);
  }
}