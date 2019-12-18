#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int SQLITE_CHECKPOINT_FULL ; 
 int SQLITE_CHECKPOINT_PASSIVE ; 
 int SQLITE_CHECKPOINT_RESTART ; 
 int SQLITE_ERROR ; 
 int SQLITE_MAX_ATTACHED ; 
 int SQLITE_MISUSE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3ApiExit (TYPE_1__*,int) ; 
 int sqlite3Checkpoint (TYPE_1__*,int,int,int*,int*) ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_1__*,int,char*,...) ; 
 int sqlite3FindDbName (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

int sqlite3_wal_checkpoint_v2(
  sqlite3 *db,                    /* Database handle */
  const char *zDb,                /* Name of attached database (or NULL) */
  int eMode,                      /* SQLITE_CHECKPOINT_* value */
  int *pnLog,                     /* OUT: Size of WAL log in frames */
  int *pnCkpt                     /* OUT: Total number of frames checkpointed */
){
#ifdef SQLITE_OMIT_WAL
  return SQLITE_OK;
#else
  int rc;                         /* Return code */
  int iDb = SQLITE_MAX_ATTACHED;  /* sqlite3.aDb[] index of db to checkpoint */

  /* Initialize the output variables to -1 in case an error occurs. */
  if( pnLog ) *pnLog = -1;
  if( pnCkpt ) *pnCkpt = -1;

  assert( SQLITE_CHECKPOINT_FULL>SQLITE_CHECKPOINT_PASSIVE );
  assert( SQLITE_CHECKPOINT_FULL<SQLITE_CHECKPOINT_RESTART );
  assert( SQLITE_CHECKPOINT_PASSIVE+2==SQLITE_CHECKPOINT_RESTART );
  if( eMode<SQLITE_CHECKPOINT_PASSIVE || eMode>SQLITE_CHECKPOINT_RESTART ){
    return SQLITE_MISUSE;
  }

  sqlite3_mutex_enter(db->mutex);
  if( zDb && zDb[0] ){
    iDb = sqlite3FindDbName(db, zDb);
  }
  if( iDb<0 ){
    rc = SQLITE_ERROR;
    sqlite3Error(db, SQLITE_ERROR, "unknown database: %s", zDb);
  }else{
    rc = sqlite3Checkpoint(db, iDb, eMode, pnLog, pnCkpt);
    sqlite3Error(db, rc, 0);
  }
  rc = sqlite3ApiExit(db, rc);
  sqlite3_mutex_leave(db->mutex);
  return rc;
#endif
}