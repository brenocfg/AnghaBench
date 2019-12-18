#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  numOfMetrics; TYPE_2__* pMetric; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pSkipList; TYPE_2__* next; TYPE_1__* prev; } ;
struct TYPE_8__ {TYPE_1__* prev; } ;
struct TYPE_7__ {TYPE_2__* next; } ;
typedef  TYPE_3__ STabObj ;
typedef  TYPE_4__ SDbObj ;

/* Variables and functions */
 int /*<<< orphan*/ * tSkipListDestroy (int /*<<< orphan*/ *) ; 

int mgmtRemoveMetricFromDb(SDbObj *pDb, STabObj *pMetric) {
  if (pMetric->prev) pMetric->prev->next = pMetric->next;

  if (pMetric->next) pMetric->next->prev = pMetric->prev;

  if (pMetric->prev == NULL) pDb->pMetric = pMetric->next;

  pDb->numOfMetrics--;

  if (pMetric->pSkipList != NULL) {
    pMetric->pSkipList = tSkipListDestroy(pMetric->pSkipList);
  }
  return 0;
}