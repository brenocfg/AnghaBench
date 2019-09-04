#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Vdbe ;

/* Variables and functions */
 int SQLITE_MISUSE_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  mutex ; 
 int sqlite3ApiExit (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeFinalize (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 scalar_t__ vdbeSafety (TYPE_1__*) ; 

int sqlite3_finalize(sqlite3_stmt *pStmt){
  int rc;
  if( pStmt==0 ){
    /* IMPLEMENTATION-OF: R-57228-12904 Invoking sqlite3_finalize() on a NULL
    ** pointer is a harmless no-op. */
    rc = SQLITE_OK;
  }else{
    Vdbe *v = (Vdbe*)pStmt;
    sqlite3 *db = v->db;
#if SQLITE_THREADSAFE
    sqlite3_mutex *mutex;
#endif
    if( vdbeSafety(v) ) return SQLITE_MISUSE_BKPT;
#if SQLITE_THREADSAFE
    mutex = v->db->mutex;
#endif
    sqlite3_mutex_enter(mutex);
    rc = sqlite3VdbeFinalize(v);
    rc = sqlite3ApiExit(db, rc);
    sqlite3_mutex_leave(mutex);
  }
  return rc;
}