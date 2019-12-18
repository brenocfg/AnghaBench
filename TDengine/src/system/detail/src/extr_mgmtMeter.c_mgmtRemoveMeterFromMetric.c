#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  rwLock; int /*<<< orphan*/  numOfMeters; TYPE_1__* next; TYPE_1__* pHead; TYPE_2__* prev; } ;
struct TYPE_9__ {TYPE_1__* next; } ;
struct TYPE_8__ {TYPE_2__* prev; } ;
typedef  TYPE_3__ STabObj ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  removeMeterFromMetricIndex (TYPE_3__*,TYPE_3__*) ; 

int mgmtRemoveMeterFromMetric(STabObj *pMetric, STabObj *pMeter) {
  pthread_rwlock_wrlock(&(pMetric->rwLock));

  if (pMeter->prev) pMeter->prev->next = pMeter->next;

  if (pMeter->next) pMeter->next->prev = pMeter->prev;

  if (pMeter->prev == NULL) pMetric->pHead = pMeter->next;

  pMetric->numOfMeters--;

  removeMeterFromMetricIndex(pMetric, pMeter);

  pthread_rwlock_unlock(&(pMetric->rwLock));

  return 0;
}