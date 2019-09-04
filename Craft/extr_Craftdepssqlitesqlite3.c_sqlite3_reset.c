#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_5__ {TYPE_4__* db; } ;
typedef  TYPE_1__ Vdbe ;
struct TYPE_6__ {int errMask; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3ApiExit (TYPE_4__*,int) ; 
 int sqlite3VdbeReset (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeRewind (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

int sqlite3_reset(sqlite3_stmt *pStmt){
  int rc;
  if( pStmt==0 ){
    rc = SQLITE_OK;
  }else{
    Vdbe *v = (Vdbe*)pStmt;
    sqlite3_mutex_enter(v->db->mutex);
    rc = sqlite3VdbeReset(v);
    sqlite3VdbeRewind(v);
    assert( (rc & (v->db->errMask))==rc );
    rc = sqlite3ApiExit(v->db, rc);
    sqlite3_mutex_leave(v->db->mutex);
  }
  return rc;
}