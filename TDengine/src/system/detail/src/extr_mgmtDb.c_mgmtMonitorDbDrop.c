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
struct TYPE_3__ {scalar_t__ dropStatus; } ;
typedef  TYPE_1__ SDbObj ;

/* Variables and functions */
 scalar_t__ TSDB_DB_STATUS_DROPPING ; 
 int /*<<< orphan*/  dbSdb ; 
 int /*<<< orphan*/  mgmtDropDb (TYPE_1__*) ; 
 void* sdbFetchRow (int /*<<< orphan*/ ,void*,void**) ; 

void mgmtMonitorDbDrop(void *unused, void *unusedt) {
  void *  pNode = NULL;
  SDbObj *pDb = NULL;

  while (1) {
    pNode = sdbFetchRow(dbSdb, pNode, (void **)&pDb);
    if (pDb == NULL) break;
    if (pDb->dropStatus != TSDB_DB_STATUS_DROPPING) continue;
    mgmtDropDb(pDb);
    break;
  }
}