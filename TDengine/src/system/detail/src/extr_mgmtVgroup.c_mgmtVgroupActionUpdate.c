#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int maxSessions; } ;
struct TYPE_7__ {TYPE_1__ cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  numOfVnodes; int /*<<< orphan*/  vgId; int /*<<< orphan*/ ** meterList; int /*<<< orphan*/  idPool; int /*<<< orphan*/  dbName; } ;
typedef  TYPE_2__ SVgObj ;
typedef  int /*<<< orphan*/  STabObj ;
typedef  TYPE_3__ SDbObj ;

/* Variables and functions */
 int /*<<< orphan*/  mPrint (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* mgmtGetDb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmtVgroupActionReset (void*,char*,int,int*) ; 
 scalar_t__ realloc (int /*<<< orphan*/ **,int) ; 
 int taosIdPoolMaxSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosUpdateIdPool (int /*<<< orphan*/ ,int) ; 

void *mgmtVgroupActionUpdate(void *row, char *str, int size, int *ssize) {
  mgmtVgroupActionReset(row, str, size, ssize);
  SVgObj *pVgroup = (SVgObj *)row;
  int oldTables = taosIdPoolMaxSize(pVgroup->idPool);

  SDbObj *pDb = mgmtGetDb(pVgroup->dbName);
  if (pDb != NULL) {
    if (pDb->cfg.maxSessions != oldTables) {
      mPrint("vgroup:%d tables change from %d to %d", pVgroup->vgId, oldTables, pDb->cfg.maxSessions);
      taosUpdateIdPool(pVgroup->idPool, pDb->cfg.maxSessions);
      int size = sizeof(STabObj *) * pDb->cfg.maxSessions;
      pVgroup->meterList = (STabObj **)realloc(pVgroup->meterList, size);
    }
  }

  mTrace("vgroup:%d update, numOfVnode:%d", pVgroup->vgId, pVgroup->numOfVnodes);

  return NULL;
}