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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {int /*<<< orphan*/  p; } ;
struct TYPE_6__ {struct TYPE_6__* zComment; TYPE_1__ p4; int /*<<< orphan*/  p4type; } ;
typedef  TYPE_2__ Op ;

/* Variables and functions */
 int /*<<< orphan*/  freeP4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void vdbeFreeOpArray(sqlite3 *db, Op *aOp, int nOp){
  if( aOp ){
    Op *pOp;
    for(pOp=aOp; pOp<&aOp[nOp]; pOp++){
      freeP4(db, pOp->p4type, pOp->p4.p);
#ifdef SQLITE_DEBUG
      sqlite3DbFree(db, pOp->zComment);
#endif     
    }
  }
  sqlite3DbFree(db, aOp);
}