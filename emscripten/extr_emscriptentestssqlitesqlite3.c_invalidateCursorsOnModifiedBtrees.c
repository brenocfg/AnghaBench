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
struct TYPE_5__ {int nDb; TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_4__ {int /*<<< orphan*/ * pBt; } ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_ABORT ; 
 scalar_t__ sqlite3BtreeIsInTrans (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3BtreeTripAllCursors (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void invalidateCursorsOnModifiedBtrees(sqlite3 *db){
  int i;
  for(i=0; i<db->nDb; i++){
    Btree *p = db->aDb[i].pBt;
    if( p && sqlite3BtreeIsInTrans(p) ){
      sqlite3BtreeTripAllCursors(p, SQLITE_ABORT);
    }
  }
}