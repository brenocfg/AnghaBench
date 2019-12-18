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
struct TYPE_10__ {int /*<<< orphan*/  numOfVgroups; TYPE_1__* pTail; TYPE_2__* pHead; } ;
struct TYPE_9__ {TYPE_1__* prev; TYPE_2__* next; } ;
struct TYPE_8__ {TYPE_1__* prev; } ;
struct TYPE_7__ {TYPE_2__* next; } ;
typedef  TYPE_3__ SVgObj ;
typedef  TYPE_4__ SDbObj ;

/* Variables and functions */

int mgmtRemoveVgroupFromDb(SDbObj *pDb, SVgObj *pVgroup) {
  if (pVgroup->prev) pVgroup->prev->next = pVgroup->next;

  if (pVgroup->next) pVgroup->next->prev = pVgroup->prev;

  if (pVgroup->prev == NULL) pDb->pHead = pVgroup->next;

  if (pVgroup->next == NULL) pDb->pTail = pVgroup->prev;

  pDb->numOfVgroups--;

  return 0;
}