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
struct TYPE_6__ {TYPE_1__* pDestructor; } ;
struct TYPE_5__ {scalar_t__ nRef; int /*<<< orphan*/  pUserData; int /*<<< orphan*/  (* xDestroy ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ FuncDestructor ;
typedef  TYPE_2__ FuncDef ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void functionDestroy(sqlite3 *db, FuncDef *p){
  FuncDestructor *pDestructor = p->pDestructor;
  if( pDestructor ){
    pDestructor->nRef--;
    if( pDestructor->nRef==0 ){
      pDestructor->xDestroy(pDestructor->pUserData);
      sqlite3DbFree(db, pDestructor);
    }
  }
}