#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  sqlite3_vfs ;
struct TYPE_6__ {int useJournal; scalar_t__ eState; int /*<<< orphan*/  jfd; int /*<<< orphan*/  zJournal; int /*<<< orphan*/  exclusiveMode; int /*<<< orphan*/  fd; int /*<<< orphan*/ * pVfs; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ PAGER_OPEN ; 
 int /*<<< orphan*/  RESERVED_LOCK ; 
 int /*<<< orphan*/  SHARED_LOCK ; 
 int /*<<< orphan*/  SQLITE_ACCESS_EXISTS ; 
 int SQLITE_CANTOPEN ; 
 int SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN ; 
 int SQLITE_IOERR_SHORT_READ ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_MAIN_JOURNAL ; 
 int SQLITE_OPEN_READONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int isOpen (int /*<<< orphan*/ ) ; 
 int pagerLockDb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pagerPagecount (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  pagerUnlockDb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 
 int sqlite3OsAccess (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sqlite3OsCheckReservedLock (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sqlite3OsClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3OsDelete (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3OsDeviceCharacteristics (int /*<<< orphan*/ ) ; 
 int sqlite3OsOpen (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int sqlite3OsRead (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hasHotJournal(Pager *pPager, int *pExists){
  sqlite3_vfs * const pVfs = pPager->pVfs;
  int rc = SQLITE_OK;           /* Return code */
  int exists = 1;               /* True if a journal file is present */
  int jrnlOpen = !!isOpen(pPager->jfd);

  assert( pPager->useJournal );
  assert( isOpen(pPager->fd) );
  assert( pPager->eState==PAGER_OPEN );

  assert( jrnlOpen==0 || ( sqlite3OsDeviceCharacteristics(pPager->jfd) &
    SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN
  ));

  *pExists = 0;
  if( !jrnlOpen ){
    rc = sqlite3OsAccess(pVfs, pPager->zJournal, SQLITE_ACCESS_EXISTS, &exists);
  }
  if( rc==SQLITE_OK && exists ){
    int locked = 0;             /* True if some process holds a RESERVED lock */

    /* Race condition here:  Another process might have been holding the
    ** the RESERVED lock and have a journal open at the sqlite3OsAccess() 
    ** call above, but then delete the journal and drop the lock before
    ** we get to the following sqlite3OsCheckReservedLock() call.  If that
    ** is the case, this routine might think there is a hot journal when
    ** in fact there is none.  This results in a false-positive which will
    ** be dealt with by the playback routine.  Ticket #3883.
    */
    rc = sqlite3OsCheckReservedLock(pPager->fd, &locked);
    if( rc==SQLITE_OK && !locked ){
      Pgno nPage;                 /* Number of pages in database file */

      /* Check the size of the database file. If it consists of 0 pages,
      ** then delete the journal file. See the header comment above for 
      ** the reasoning here.  Delete the obsolete journal file under
      ** a RESERVED lock to avoid race conditions and to avoid violating
      ** [H33020].
      */
      rc = pagerPagecount(pPager, &nPage);
      if( rc==SQLITE_OK ){
        if( nPage==0 ){
          sqlite3BeginBenignMalloc();
          if( pagerLockDb(pPager, RESERVED_LOCK)==SQLITE_OK ){
            sqlite3OsDelete(pVfs, pPager->zJournal, 0);
            if( !pPager->exclusiveMode ) pagerUnlockDb(pPager, SHARED_LOCK);
          }
          sqlite3EndBenignMalloc();
        }else{
          /* The journal file exists and no other connection has a reserved
          ** or greater lock on the database file. Now check that there is
          ** at least one non-zero bytes at the start of the journal file.
          ** If there is, then we consider this journal to be hot. If not, 
          ** it can be ignored.
          */
          if( !jrnlOpen ){
            int f = SQLITE_OPEN_READONLY|SQLITE_OPEN_MAIN_JOURNAL;
            rc = sqlite3OsOpen(pVfs, pPager->zJournal, pPager->jfd, f, &f);
          }
          if( rc==SQLITE_OK ){
            u8 first = 0;
            rc = sqlite3OsRead(pPager->jfd, (void *)&first, 1, 0);
            if( rc==SQLITE_IOERR_SHORT_READ ){
              rc = SQLITE_OK;
            }
            if( !jrnlOpen ){
              sqlite3OsClose(pPager->jfd);
            }
            *pExists = (first!=0);
          }else if( rc==SQLITE_CANTOPEN ){
            /* If we cannot open the rollback journal file in order to see if
            ** its has a zero header, that might be due to an I/O error, or
            ** it might be due to the race condition described above and in
            ** ticket #3883.  Either way, assume that the journal is hot.
            ** This might be a false positive.  But if it is, then the
            ** automatic journal playback and recovery mechanism will deal
            ** with it under an EXCLUSIVE lock where we do not need to
            ** worry so much with race conditions.
            */
            *pExists = 1;
            rc = SQLITE_OK;
          }
        }
      }
    }
  }

  return rc;
}