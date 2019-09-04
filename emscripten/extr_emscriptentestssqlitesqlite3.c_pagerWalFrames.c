#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_10__ {scalar_t__ pBackup; int /*<<< orphan*/  pageSize; TYPE_1__* pWal; } ;
struct TYPE_9__ {scalar_t__ pgno; scalar_t__ pData; struct TYPE_9__* pDirty; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  pager_write_changecounter (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3BackupUpdate (scalar_t__,int,int /*<<< orphan*/ *) ; 
 int sqlite3WalFrames (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int,int) ; 

__attribute__((used)) static int pagerWalFrames(
  Pager *pPager,                  /* Pager object */
  PgHdr *pList,                   /* List of frames to log */
  Pgno nTruncate,                 /* Database size after this commit */
  int isCommit,                   /* True if this is a commit */
  int syncFlags                   /* Flags to pass to OsSync() (or 0) */
){
  int rc;                         /* Return code */
#if defined(SQLITE_DEBUG) || defined(SQLITE_CHECK_PAGES)
  PgHdr *p;                       /* For looping over pages */
#endif

  assert( pPager->pWal );
#ifdef SQLITE_DEBUG
  /* Verify that the page list is in accending order */
  for(p=pList; p && p->pDirty; p=p->pDirty){
    assert( p->pgno < p->pDirty->pgno );
  }
#endif

  if( isCommit ){
    /* If a WAL transaction is being committed, there is no point in writing
    ** any pages with page numbers greater than nTruncate into the WAL file.
    ** They will never be read by any client. So remove them from the pDirty
    ** list here. */
    PgHdr *p;
    PgHdr **ppNext = &pList;
    for(p=pList; (*ppNext = p); p=p->pDirty){
      if( p->pgno<=nTruncate ) ppNext = &p->pDirty;
    }
    assert( pList );
  }

  if( pList->pgno==1 ) pager_write_changecounter(pList);
  rc = sqlite3WalFrames(pPager->pWal, 
      pPager->pageSize, pList, nTruncate, isCommit, syncFlags
  );
  if( rc==SQLITE_OK && pPager->pBackup ){
    PgHdr *p;
    for(p=pList; p; p=p->pDirty){
      sqlite3BackupUpdate(pPager->pBackup, p->pgno, (u8 *)p->pData);
    }
  }

#ifdef SQLITE_CHECK_PAGES
  pList = sqlite3PcacheDirtyList(pPager->pPCache);
  for(p=pList; p; p=p->pDirty){
    pager_set_pagehash(p);
  }
#endif

  return rc;
}