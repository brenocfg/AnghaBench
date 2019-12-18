#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  acct; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pMetric; int /*<<< orphan*/ * vgTimer; scalar_t__ numOfTables; scalar_t__ numOfVgroups; int /*<<< orphan*/ * pTail; int /*<<< orphan*/ * pHead; TYPE_1__ cfg; } ;
typedef  TYPE_2__ SDbObj ;
typedef  int /*<<< orphan*/  SAcctObj ;

/* Variables and functions */
 int /*<<< orphan*/  mgmtAddDbIntoAcct (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * mgmtGetAcct (int /*<<< orphan*/ ) ; 

void *mgmtDbActionInsert(void *row, char *str, int size, int *ssize) {
  SDbObj *  pDb = (SDbObj *)row;
  SAcctObj *pAcct = mgmtGetAcct(pDb->cfg.acct);

  pDb->pHead = NULL;
  pDb->pTail = NULL;
  pDb->numOfVgroups = 0;
  pDb->numOfTables = 0;
  pDb->vgTimer = NULL;
  pDb->pMetric = NULL;
  mgmtAddDbIntoAcct(pAcct, pDb);

  return NULL;
}