#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  meterList; int /*<<< orphan*/  numOfVnodes; int /*<<< orphan*/  vnodeGid; int /*<<< orphan*/  dbName; } ;
typedef  TYPE_1__ SVgObj ;
typedef  int /*<<< orphan*/  SDbObj ;

/* Variables and functions */
 int /*<<< orphan*/ * mgmtGetDb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmtRemoveVgroupFromDb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mgmtUnSetDnodeVgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ ) ; 

void *mgmtVgroupActionDelete(void *row, char *str, int size, int *ssize) {
  SVgObj *pVgroup = (SVgObj *)row;
  SDbObj *pDb = mgmtGetDb(pVgroup->dbName);

  if (pDb != NULL) mgmtRemoveVgroupFromDb(pDb, pVgroup);
  mgmtUnSetDnodeVgid(pVgroup->vnodeGid, pVgroup->numOfVnodes);
  tfree(pVgroup->meterList);

  return NULL;
}