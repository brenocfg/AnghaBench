#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_3__ {int nVar; int expired; scalar_t__ expmask; scalar_t__ isPrepareV2; TYPE_2__* aVar; } ;
typedef  TYPE_1__ Vdbe ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_Null ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  sqlite3VdbeMemRelease (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

int sqlite3_clear_bindings(sqlite3_stmt *pStmt){
  int i;
  int rc = SQLITE_OK;
  Vdbe *p = (Vdbe*)pStmt;
#if SQLITE_THREADSAFE
  sqlite3_mutex *mutex = ((Vdbe*)pStmt)->db->mutex;
#endif
  sqlite3_mutex_enter(mutex);
  for(i=0; i<p->nVar; i++){
    sqlite3VdbeMemRelease(&p->aVar[i]);
    p->aVar[i].flags = MEM_Null;
  }
  if( p->isPrepareV2 && p->expmask ){
    p->expired = 1;
  }
  sqlite3_mutex_leave(mutex);
  return rc;
}