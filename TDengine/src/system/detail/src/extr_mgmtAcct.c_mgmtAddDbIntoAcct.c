#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  numOfDbs; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; TYPE_1__ acctInfo; TYPE_2__* pHead; } ;
struct TYPE_7__ {struct TYPE_7__* prev; struct TYPE_7__* next; } ;
typedef  TYPE_2__ SDbObj ;
typedef  TYPE_3__ SAcctObj ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int mgmtAddDbIntoAcct(SAcctObj *pAcct, SDbObj *pDb) {
  pthread_mutex_lock(&pAcct->mutex);
  pDb->next = pAcct->pHead;
  pDb->prev = NULL;

  if (pAcct->pHead) pAcct->pHead->prev = pDb;

  pAcct->pHead = pDb;
  pAcct->acctInfo.numOfDbs++;
  pthread_mutex_unlock(&pAcct->mutex);

  return 0;
}