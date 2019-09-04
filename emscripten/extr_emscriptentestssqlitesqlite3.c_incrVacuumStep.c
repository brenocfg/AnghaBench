#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_17__ {scalar_t__ nPage; int /*<<< orphan*/  pPager; TYPE_1__* pPage1; int /*<<< orphan*/  mutex; } ;
struct TYPE_16__ {int /*<<< orphan*/  pDbPage; } ;
struct TYPE_15__ {int /*<<< orphan*/ * aData; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_2__ MemPage ;
typedef  TYPE_3__ BtShared ;

/* Variables and functions */
 scalar_t__ PENDING_BYTE_PAGE (TYPE_3__*) ; 
 scalar_t__ PTRMAP_FREEPAGE ; 
 scalar_t__ PTRMAP_ISPAGE (TYPE_3__*,scalar_t__) ; 
 scalar_t__ PTRMAP_ROOTPAGE ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int allocateBtreePage (TYPE_3__*,TYPE_2__**,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int btreeGetPage (TYPE_3__*,scalar_t__,TYPE_2__**,int /*<<< orphan*/ ) ; 
 scalar_t__ get4byte (int /*<<< orphan*/ *) ; 
 int ptrmapGet (TYPE_3__*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  releasePage (TYPE_2__*) ; 
 int relocatePage (TYPE_3__*,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  sqlite3PagerTruncateImage (int /*<<< orphan*/ ,scalar_t__) ; 
 int sqlite3PagerWrite (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int incrVacuumStep(BtShared *pBt, Pgno nFin, Pgno iLastPg){
  Pgno nFreeList;           /* Number of pages still on the free-list */
  int rc;

  assert( sqlite3_mutex_held(pBt->mutex) );
  assert( iLastPg>nFin );

  if( !PTRMAP_ISPAGE(pBt, iLastPg) && iLastPg!=PENDING_BYTE_PAGE(pBt) ){
    u8 eType;
    Pgno iPtrPage;

    nFreeList = get4byte(&pBt->pPage1->aData[36]);
    if( nFreeList==0 ){
      return SQLITE_DONE;
    }

    rc = ptrmapGet(pBt, iLastPg, &eType, &iPtrPage);
    if( rc!=SQLITE_OK ){
      return rc;
    }
    if( eType==PTRMAP_ROOTPAGE ){
      return SQLITE_CORRUPT_BKPT;
    }

    if( eType==PTRMAP_FREEPAGE ){
      if( nFin==0 ){
        /* Remove the page from the files free-list. This is not required
        ** if nFin is non-zero. In that case, the free-list will be
        ** truncated to zero after this function returns, so it doesn't 
        ** matter if it still contains some garbage entries.
        */
        Pgno iFreePg;
        MemPage *pFreePg;
        rc = allocateBtreePage(pBt, &pFreePg, &iFreePg, iLastPg, 1);
        if( rc!=SQLITE_OK ){
          return rc;
        }
        assert( iFreePg==iLastPg );
        releasePage(pFreePg);
      }
    } else {
      Pgno iFreePg;             /* Index of free page to move pLastPg to */
      MemPage *pLastPg;

      rc = btreeGetPage(pBt, iLastPg, &pLastPg, 0);
      if( rc!=SQLITE_OK ){
        return rc;
      }

      /* If nFin is zero, this loop runs exactly once and page pLastPg
      ** is swapped with the first free page pulled off the free list.
      **
      ** On the other hand, if nFin is greater than zero, then keep
      ** looping until a free-page located within the first nFin pages
      ** of the file is found.
      */
      do {
        MemPage *pFreePg;
        rc = allocateBtreePage(pBt, &pFreePg, &iFreePg, 0, 0);
        if( rc!=SQLITE_OK ){
          releasePage(pLastPg);
          return rc;
        }
        releasePage(pFreePg);
      }while( nFin!=0 && iFreePg>nFin );
      assert( iFreePg<iLastPg );
      
      rc = sqlite3PagerWrite(pLastPg->pDbPage);
      if( rc==SQLITE_OK ){
        rc = relocatePage(pBt, pLastPg, eType, iPtrPage, iFreePg, nFin!=0);
      }
      releasePage(pLastPg);
      if( rc!=SQLITE_OK ){
        return rc;
      }
    }
  }

  if( nFin==0 ){
    iLastPg--;
    while( iLastPg==PENDING_BYTE_PAGE(pBt)||PTRMAP_ISPAGE(pBt, iLastPg) ){
      if( PTRMAP_ISPAGE(pBt, iLastPg) ){
        MemPage *pPg;
        rc = btreeGetPage(pBt, iLastPg, &pPg, 0);
        if( rc!=SQLITE_OK ){
          return rc;
        }
        rc = sqlite3PagerWrite(pPg->pDbPage);
        releasePage(pPg);
        if( rc!=SQLITE_OK ){
          return rc;
        }
      }
      iLastPg--;
    }
    sqlite3PagerTruncateImage(pBt->pPager, iLastPg);
    pBt->nPage = iLastPg;
  }
  return SQLITE_OK;
}