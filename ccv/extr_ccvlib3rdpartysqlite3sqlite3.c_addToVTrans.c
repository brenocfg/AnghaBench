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
struct TYPE_3__ {int /*<<< orphan*/  nVTrans; int /*<<< orphan*/ ** aVTrans; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  int /*<<< orphan*/  VTable ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3VtabLock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void addToVTrans(sqlite3 *db, VTable *pVTab){
  /* Add pVtab to the end of sqlite3.aVTrans */
  db->aVTrans[db->nVTrans++] = pVTab;
  sqlite3VtabLock(pVTab);
}