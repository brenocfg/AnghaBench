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
struct TYPE_6__ {int /*<<< orphan*/  rwLock; int /*<<< orphan*/  numOfMeters; struct TYPE_6__* pHead; struct TYPE_6__* prev; struct TYPE_6__* next; } ;
typedef  TYPE_1__ STabObj ;

/* Variables and functions */
 int /*<<< orphan*/  addMeterIntoMetricIndex (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 

int mgmtAddMeterIntoMetric(STabObj *pMetric, STabObj *pMeter) {
  if (pMeter == NULL || pMetric == NULL) return -1;

  pthread_rwlock_wrlock(&(pMetric->rwLock));
  // add meter into skip list
  pMeter->next = pMetric->pHead;
  pMeter->prev = NULL;

  if (pMetric->pHead) pMetric->pHead->prev = pMeter;

  pMetric->pHead = pMeter;
  pMetric->numOfMeters++;

  addMeterIntoMetricIndex(pMetric, pMeter);

  pthread_rwlock_unlock(&(pMetric->rwLock));

  return 0;
}