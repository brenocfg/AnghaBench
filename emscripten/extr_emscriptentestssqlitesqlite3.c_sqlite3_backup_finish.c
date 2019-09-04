#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_mutex ;
struct TYPE_11__ {int rc; TYPE_6__* pDestDb; TYPE_7__* pSrc; int /*<<< orphan*/  pDest; struct TYPE_11__* pNext; scalar_t__ isAttached; TYPE_1__* pSrcDb; } ;
typedef  TYPE_2__ sqlite3_backup ;
struct TYPE_13__ {int /*<<< orphan*/  nBackup; } ;
struct TYPE_12__ {int /*<<< orphan*/ * mutex; } ;
struct TYPE_10__ {int /*<<< orphan*/ * mutex; } ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3BtreePager (TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3BtreeRollback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__** sqlite3PagerBackupPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ *) ; 

int sqlite3_backup_finish(sqlite3_backup *p){
  sqlite3_backup **pp;                 /* Ptr to head of pagers backup list */
  sqlite3_mutex *mutex;                /* Mutex to protect source database */
  int rc;                              /* Value to return */

  /* Enter the mutexes */
  if( p==0 ) return SQLITE_OK;
  sqlite3_mutex_enter(p->pSrcDb->mutex);
  sqlite3BtreeEnter(p->pSrc);
  mutex = p->pSrcDb->mutex;
  if( p->pDestDb ){
    sqlite3_mutex_enter(p->pDestDb->mutex);
  }

  /* Detach this backup from the source pager. */
  if( p->pDestDb ){
    p->pSrc->nBackup--;
  }
  if( p->isAttached ){
    pp = sqlite3PagerBackupPtr(sqlite3BtreePager(p->pSrc));
    while( *pp!=p ){
      pp = &(*pp)->pNext;
    }
    *pp = p->pNext;
  }

  /* If a transaction is still open on the Btree, roll it back. */
  sqlite3BtreeRollback(p->pDest);

  /* Set the error code of the destination database handle. */
  rc = (p->rc==SQLITE_DONE) ? SQLITE_OK : p->rc;
  sqlite3Error(p->pDestDb, rc, 0);

  /* Exit the mutexes and free the backup context structure. */
  if( p->pDestDb ){
    sqlite3_mutex_leave(p->pDestDb->mutex);
  }
  sqlite3BtreeLeave(p->pSrc);
  if( p->pDestDb ){
    /* EVIDENCE-OF: R-64852-21591 The sqlite3_backup object is created by a
    ** call to sqlite3_backup_init() and is destroyed by a call to
    ** sqlite3_backup_finish(). */
    sqlite3_free(p);
  }
  sqlite3_mutex_leave(mutex);
  return rc;
}