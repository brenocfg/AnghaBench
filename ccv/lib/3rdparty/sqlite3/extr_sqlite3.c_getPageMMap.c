#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int i64 ;
struct TYPE_9__ {scalar_t__ eState; scalar_t__ xCodec; int hasHeldSharedLock; int errCode; int pageSize; int /*<<< orphan*/  fd; scalar_t__ tempFile; int /*<<< orphan*/  pWal; } ;
typedef  int Pgno ;
typedef  int /*<<< orphan*/  PgHdr ;
typedef  TYPE_1__ Pager ;
typedef  int /*<<< orphan*/  DbPage ;

/* Variables and functions */
 int PAGER_GET_READONLY ; 
 scalar_t__ PAGER_READER ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int USEFETCH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int assert_pager_state (TYPE_1__*) ; 
 int getPageNormal (TYPE_1__*,int,int /*<<< orphan*/ **,int) ; 
 int pagerAcquireMapPage (TYPE_1__*,int,void*,int /*<<< orphan*/ **) ; 
 scalar_t__ pagerUseWal (TYPE_1__*) ; 
 int sqlite3OsFetch (int /*<<< orphan*/ ,int,int,void**) ; 
 int /*<<< orphan*/  sqlite3OsUnfetch (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/ * sqlite3PagerLookup (TYPE_1__*,int) ; 
 int sqlite3WalFindFrame (int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static int getPageMMap(
  Pager *pPager,      /* The pager open on the database file */
  Pgno pgno,          /* Page number to fetch */
  DbPage **ppPage,    /* Write a pointer to the page here */
  int flags           /* PAGER_GET_XXX flags */
){
  int rc = SQLITE_OK;
  PgHdr *pPg = 0;
  u32 iFrame = 0;                 /* Frame to read from WAL file */

  /* It is acceptable to use a read-only (mmap) page for any page except
  ** page 1 if there is no write-transaction open or the ACQUIRE_READONLY
  ** flag was specified by the caller. And so long as the db is not a 
  ** temporary or in-memory database.  */
  const int bMmapOk = (pgno>1
   && (pPager->eState==PAGER_READER || (flags & PAGER_GET_READONLY))
  );

  assert( USEFETCH(pPager) );
#ifdef SQLITE_HAS_CODEC
  assert( pPager->xCodec==0 );
#endif

  /* Optimization note:  Adding the "pgno<=1" term before "pgno==0" here
  ** allows the compiler optimizer to reuse the results of the "pgno>1"
  ** test in the previous statement, and avoid testing pgno==0 in the
  ** common case where pgno is large. */
  if( pgno<=1 && pgno==0 ){
    return SQLITE_CORRUPT_BKPT;
  }
  assert( pPager->eState>=PAGER_READER );
  assert( assert_pager_state(pPager) );
  assert( pPager->hasHeldSharedLock==1 );
  assert( pPager->errCode==SQLITE_OK );

  if( bMmapOk && pagerUseWal(pPager) ){
    rc = sqlite3WalFindFrame(pPager->pWal, pgno, &iFrame);
    if( rc!=SQLITE_OK ){
      *ppPage = 0;
      return rc;
    }
  }
  if( bMmapOk && iFrame==0 ){
    void *pData = 0;
    rc = sqlite3OsFetch(pPager->fd, 
        (i64)(pgno-1) * pPager->pageSize, pPager->pageSize, &pData
    );
    if( rc==SQLITE_OK && pData ){
      if( pPager->eState>PAGER_READER || pPager->tempFile ){
        pPg = sqlite3PagerLookup(pPager, pgno);
      }
      if( pPg==0 ){
        rc = pagerAcquireMapPage(pPager, pgno, pData, &pPg);
      }else{
        sqlite3OsUnfetch(pPager->fd, (i64)(pgno-1)*pPager->pageSize, pData);
      }
      if( pPg ){
        assert( rc==SQLITE_OK );
        *ppPage = pPg;
        return SQLITE_OK;
      }
    }
    if( rc!=SQLITE_OK ){
      *ppPage = 0;
      return rc;
    }
  }
  return getPageNormal(pPager, pgno, ppPage, flags);
}