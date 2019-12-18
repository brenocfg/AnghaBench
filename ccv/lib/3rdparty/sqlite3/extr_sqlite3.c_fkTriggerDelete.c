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
struct TYPE_5__ {int /*<<< orphan*/  pSelect; int /*<<< orphan*/  pExprList; int /*<<< orphan*/  pWhere; } ;
typedef  TYPE_1__ TriggerStep ;
struct TYPE_6__ {int /*<<< orphan*/  pWhen; TYPE_1__* step_list; } ;
typedef  TYPE_2__ Trigger ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SelectDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fkTriggerDelete(sqlite3 *dbMem, Trigger *p){
  if( p ){
    TriggerStep *pStep = p->step_list;
    sqlite3ExprDelete(dbMem, pStep->pWhere);
    sqlite3ExprListDelete(dbMem, pStep->pExprList);
    sqlite3SelectDelete(dbMem, pStep->pSelect);
    sqlite3ExprDelete(dbMem, p->pWhen);
    sqlite3DbFree(dbMem, p);
  }
}