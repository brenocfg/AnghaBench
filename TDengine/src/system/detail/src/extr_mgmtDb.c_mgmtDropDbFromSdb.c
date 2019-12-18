#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; TYPE_1__* pMetric; scalar_t__ pHead; } ;
struct TYPE_7__ {int /*<<< orphan*/  meterId; struct TYPE_7__* next; } ;
typedef  TYPE_1__ STabObj ;
typedef  TYPE_2__ SDbObj ;

/* Variables and functions */
 int /*<<< orphan*/  dbSdb ; 
 int /*<<< orphan*/  mPrint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmtDropMeter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmtDropVgroup (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  sdbDeleteRow (int /*<<< orphan*/ ,TYPE_2__*) ; 

void mgmtDropDbFromSdb(SDbObj *pDb) {
  while (pDb->pHead) mgmtDropVgroup(pDb, pDb->pHead);

  STabObj *pMetric = pDb->pMetric;
  while (pMetric) {
    STabObj *pNext = pMetric->next;
    mgmtDropMeter(pDb, pMetric->meterId, 0);
    pMetric = pNext;
  }

  mPrint("db:%s all meters drop finished", pDb->name);
  sdbDeleteRow(dbSdb, pDb);
  mPrint("db:%s database drop finished", pDb->name);
}