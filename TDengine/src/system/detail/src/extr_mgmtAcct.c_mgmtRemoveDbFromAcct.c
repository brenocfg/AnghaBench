#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  numOfDbs; } ;
struct TYPE_12__ {int /*<<< orphan*/  mutex; TYPE_1__ acctInfo; TYPE_3__* pHead; } ;
struct TYPE_11__ {TYPE_3__* next; TYPE_2__* prev; } ;
struct TYPE_10__ {TYPE_2__* prev; } ;
struct TYPE_9__ {TYPE_3__* next; } ;
typedef  TYPE_4__ SDbObj ;
typedef  TYPE_5__ SAcctObj ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int mgmtRemoveDbFromAcct(SAcctObj *pAcct, SDbObj *pDb) {
  pthread_mutex_lock(&pAcct->mutex);
  if (pDb->prev) pDb->prev->next = pDb->next;

  if (pDb->next) pDb->next->prev = pDb->prev;

  if (pDb->prev == NULL) pAcct->pHead = pDb->next;

  pAcct->acctInfo.numOfDbs--;
  pthread_mutex_unlock(&pAcct->mutex);

  return 0;
}