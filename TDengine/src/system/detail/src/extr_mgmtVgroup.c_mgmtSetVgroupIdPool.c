#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int maxSessions; } ;
struct TYPE_11__ {TYPE_1__ cfg; int /*<<< orphan*/  numOfTables; } ;
struct TYPE_10__ {scalar_t__ idPool; int numOfMeters; int /*<<< orphan*/  dbName; } ;
typedef  TYPE_2__ SVgObj ;
typedef  TYPE_3__ SDbObj ;

/* Variables and functions */
 int /*<<< orphan*/  mgmtAddVgroupIntoDb (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mgmtAddVgroupIntoDbTail (TYPE_3__*,TYPE_2__*) ; 
 TYPE_3__* mgmtGetDb (int /*<<< orphan*/ ) ; 
 void* sdbFetchRow (int /*<<< orphan*/ ,void*,void**) ; 
 int taosIdPoolNumOfUsed (scalar_t__) ; 
 int /*<<< orphan*/  taosIdPoolSetFreeList (scalar_t__) ; 
 int /*<<< orphan*/  vgSdb ; 

void mgmtSetVgroupIdPool() {
  void *  pNode = NULL;
  SVgObj *pVgroup = NULL;
  SDbObj *pDb;

  while (1) {
    pNode = sdbFetchRow(vgSdb, pNode, (void **)&pVgroup);
    if (pVgroup == NULL || pVgroup->idPool == 0) break;

    taosIdPoolSetFreeList(pVgroup->idPool);
    pVgroup->numOfMeters = taosIdPoolNumOfUsed(pVgroup->idPool);

    pDb = mgmtGetDb(pVgroup->dbName);
    pDb->numOfTables += pVgroup->numOfMeters;
    if (pVgroup->numOfMeters >= pDb->cfg.maxSessions - 1)
      mgmtAddVgroupIntoDbTail(pDb, pVgroup);
    else
      mgmtAddVgroupIntoDb(pDb, pVgroup);
  }
}