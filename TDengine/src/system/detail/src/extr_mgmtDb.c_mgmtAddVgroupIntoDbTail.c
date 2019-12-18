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
struct TYPE_6__ {int /*<<< orphan*/  numOfVgroups; TYPE_1__* pTail; TYPE_1__* pHead; } ;
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ SVgObj ;
typedef  TYPE_2__ SDbObj ;

/* Variables and functions */

int mgmtAddVgroupIntoDbTail(SDbObj *pDb, SVgObj *pVgroup) {
  pVgroup->next = NULL;
  pVgroup->prev = pDb->pTail;

  if (pDb->pTail) pDb->pTail->next = pVgroup;

  if (pDb->pHead == NULL) pDb->pHead = pVgroup;

  pDb->pTail = pVgroup;
  pDb->numOfVgroups++;

  return 0;
}