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
typedef  int uint32_t ;
struct TYPE_6__ {int listed; int /*<<< orphan*/  stime; scalar_t__ queryId; struct TYPE_6__* prev; struct TYPE_6__* next; TYPE_1__* pTscObj; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; TYPE_2__* sqlList; } ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlObj ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosGetTimestampMs () ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_2__*) ; 

void tscAddIntoSqlList(SSqlObj *pSql) {
  static uint32_t queryId = 1;

  STscObj *pObj = pSql->pTscObj;
  if (pSql->listed) return;

  pthread_mutex_lock(&pObj->mutex);

  assert(pSql != pObj->sqlList);
  pSql->next = pObj->sqlList;
  if (pObj->sqlList) pObj->sqlList->prev = pSql;
  pObj->sqlList = pSql;
  pSql->queryId = queryId++;

  pthread_mutex_unlock(&pObj->mutex);

  pSql->stime = taosGetTimestampMs();
  pSql->listed = 1;

  tscTrace("%p added into sqlList", pSql);
}