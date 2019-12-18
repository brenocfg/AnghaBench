#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_7__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_6__ {int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_2__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  substExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__*) ; 

__attribute__((used)) static void substExprList(
  sqlite3 *db,         /* Report malloc errors here */
  ExprList *pList,     /* List to scan and in which to make substitutes */
  int iTable,          /* Table to be substituted */
  ExprList *pEList     /* Substitute values */
){
  int i;
  if( pList==0 ) return;
  for(i=0; i<pList->nExpr; i++){
    pList->a[i].pExpr = substExpr(db, pList->a[i].pExpr, iTable, pEList);
  }
}