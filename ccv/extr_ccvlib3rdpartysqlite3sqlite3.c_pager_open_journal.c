#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;
struct TYPE_10__ {int nStmtSpill; } ;
struct TYPE_9__ {scalar_t__ eState; scalar_t__ pInJournal; int errCode; scalar_t__ journalMode; scalar_t__ journalHdr; scalar_t__ setMaster; scalar_t__ journalOff; scalar_t__ nRec; int /*<<< orphan*/  jfd; int /*<<< orphan*/  zJournal; scalar_t__ tempFile; int /*<<< orphan*/  dbSize; int /*<<< orphan*/ * pVfs; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 scalar_t__ PAGER_JOURNALMODE_MEMORY ; 
 scalar_t__ PAGER_JOURNALMODE_OFF ; 
 scalar_t__ PAGER_WRITER_CACHEMOD ; 
 scalar_t__ PAGER_WRITER_LOCKED ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int SQLITE_OPEN_MAIN_JOURNAL ; 
 int SQLITE_OPEN_READWRITE ; 
 int SQLITE_OPEN_TEMP_JOURNAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int assert_pager_state (TYPE_1__*) ; 
 int databaseIsUnmoved (TYPE_1__*) ; 
 scalar_t__ isOpen (int /*<<< orphan*/ ) ; 
 int jrnlBufferSize (TYPE_1__*) ; 
 int /*<<< orphan*/  pagerUseWal (TYPE_1__*) ; 
 scalar_t__ sqlite3BitvecCreate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BitvecDestroy (scalar_t__) ; 
 TYPE_3__ sqlite3Config ; 
 int sqlite3JournalOpen (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3MemJournalOpen (int /*<<< orphan*/ ) ; 
 int writeJournalHdr (TYPE_1__*) ; 

__attribute__((used)) static int pager_open_journal(Pager *pPager){
  int rc = SQLITE_OK;                        /* Return code */
  sqlite3_vfs * const pVfs = pPager->pVfs;   /* Local cache of vfs pointer */

  assert( pPager->eState==PAGER_WRITER_LOCKED );
  assert( assert_pager_state(pPager) );
  assert( pPager->pInJournal==0 );
  
  /* If already in the error state, this function is a no-op.  But on
  ** the other hand, this routine is never called if we are already in
  ** an error state. */
  if( NEVER(pPager->errCode) ) return pPager->errCode;

  if( !pagerUseWal(pPager) && pPager->journalMode!=PAGER_JOURNALMODE_OFF ){
    pPager->pInJournal = sqlite3BitvecCreate(pPager->dbSize);
    if( pPager->pInJournal==0 ){
      return SQLITE_NOMEM_BKPT;
    }
  
    /* Open the journal file if it is not already open. */
    if( !isOpen(pPager->jfd) ){
      if( pPager->journalMode==PAGER_JOURNALMODE_MEMORY ){
        sqlite3MemJournalOpen(pPager->jfd);
      }else{
        int flags = SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE;
        int nSpill;

        if( pPager->tempFile ){
          flags |= (SQLITE_OPEN_DELETEONCLOSE|SQLITE_OPEN_TEMP_JOURNAL);
          nSpill = sqlite3Config.nStmtSpill;
        }else{
          flags |= SQLITE_OPEN_MAIN_JOURNAL;
          nSpill = jrnlBufferSize(pPager);
        }
          
        /* Verify that the database still has the same name as it did when
        ** it was originally opened. */
        rc = databaseIsUnmoved(pPager);
        if( rc==SQLITE_OK ){
          rc = sqlite3JournalOpen (
              pVfs, pPager->zJournal, pPager->jfd, flags, nSpill
          );
        }
      }
      assert( rc!=SQLITE_OK || isOpen(pPager->jfd) );
    }
  
  
    /* Write the first journal header to the journal file and open 
    ** the sub-journal if necessary.
    */
    if( rc==SQLITE_OK ){
      /* TODO: Check if all of these are really required. */
      pPager->nRec = 0;
      pPager->journalOff = 0;
      pPager->setMaster = 0;
      pPager->journalHdr = 0;
      rc = writeJournalHdr(pPager);
    }
  }

  if( rc!=SQLITE_OK ){
    sqlite3BitvecDestroy(pPager->pInJournal);
    pPager->pInJournal = 0;
  }else{
    assert( pPager->eState==PAGER_WRITER_LOCKED );
    pPager->eState = PAGER_WRITER_CACHEMOD;
  }

  return rc;
}