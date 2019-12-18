#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ listed; TYPE_2__* prev; TYPE_1__* next; TYPE_3__* pTscObj; } ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; TYPE_1__* sqlList; } ;
struct TYPE_9__ {TYPE_1__* next; } ;
struct TYPE_8__ {TYPE_2__* prev; } ;
typedef  TYPE_3__ STscObj ;
typedef  TYPE_4__ SSqlObj ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscSaveSlowQuery (TYPE_4__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_4__*) ; 

void tscRemoveFromSqlList(SSqlObj *pSql) {
  STscObj *pObj = pSql->pTscObj;
  if (pSql->listed == 0) return;

  pthread_mutex_lock(&pObj->mutex);

  if (pSql->prev)
    pSql->prev->next = pSql->next;
  else
    pObj->sqlList = pSql->next;

  if (pSql->next) pSql->next->prev = pSql->prev;

  pthread_mutex_unlock(&pObj->mutex);

  pSql->next = NULL;
  pSql->prev = NULL;
  pSql->listed = 0;

  tscSaveSlowQuery(pSql);
  tscTrace("%p removed from sqlList", pSql);
}