#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ i64 ;
struct TYPE_15__ {size_t pageSize; int usableSize; scalar_t__ autoVacuum; int /*<<< orphan*/  mutex; } ;
struct TYPE_14__ {int nHeader; scalar_t__ nKey; scalar_t__ nData; int nSize; int nLocal; size_t iOverflow; } ;
struct TYPE_13__ {unsigned char* aData; int /*<<< orphan*/  pDbPage; scalar_t__ intKey; scalar_t__ hasData; int /*<<< orphan*/  leaf; TYPE_3__* pBt; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ CellInfo ;
typedef  TYPE_3__ BtShared ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 scalar_t__ PENDING_BYTE_PAGE (TYPE_3__*) ; 
 scalar_t__ PTRMAP_ISPAGE (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  PTRMAP_OVERFLOW1 ; 
 int /*<<< orphan*/  PTRMAP_OVERFLOW2 ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int allocateBtreePage (TYPE_3__*,TYPE_1__**,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreeParseCellPtr (TYPE_1__*,unsigned char*,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptrmapPut (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  put4byte (unsigned char*,scalar_t__) ; 
 scalar_t__ putVarint (unsigned char*,int) ; 
 int /*<<< orphan*/  releasePage (TYPE_1__*) ; 
 scalar_t__ sqlite3PagerIswriteable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fillInCell(
  MemPage *pPage,                /* The page that contains the cell */
  unsigned char *pCell,          /* Complete text of the cell */
  const void *pKey, i64 nKey,    /* The key */
  const void *pData,int nData,   /* The data */
  int nZero,                     /* Extra zero bytes to append to pData */
  int *pnSize                    /* Write cell size here */
){
  int nPayload;
  const u8 *pSrc;
  int nSrc, n, rc;
  int spaceLeft;
  MemPage *pOvfl = 0;
  MemPage *pToRelease = 0;
  unsigned char *pPrior;
  unsigned char *pPayload;
  BtShared *pBt = pPage->pBt;
  Pgno pgnoOvfl = 0;
  int nHeader;
  CellInfo info;

  assert( sqlite3_mutex_held(pPage->pBt->mutex) );

  /* pPage is not necessarily writeable since pCell might be auxiliary
  ** buffer space that is separate from the pPage buffer area */
  assert( pCell<pPage->aData || pCell>=&pPage->aData[pBt->pageSize]
            || sqlite3PagerIswriteable(pPage->pDbPage) );

  /* Fill in the header. */
  nHeader = 0;
  if( !pPage->leaf ){
    nHeader += 4;
  }
  if( pPage->hasData ){
    nHeader += putVarint(&pCell[nHeader], nData+nZero);
  }else{
    nData = nZero = 0;
  }
  nHeader += putVarint(&pCell[nHeader], *(u64*)&nKey);
  btreeParseCellPtr(pPage, pCell, &info);
  assert( info.nHeader==nHeader );
  assert( info.nKey==nKey );
  assert( info.nData==(u32)(nData+nZero) );
  
  /* Fill in the payload */
  nPayload = nData + nZero;
  if( pPage->intKey ){
    pSrc = pData;
    nSrc = nData;
    nData = 0;
  }else{ 
    if( NEVER(nKey>0x7fffffff || pKey==0) ){
      return SQLITE_CORRUPT_BKPT;
    }
    nPayload += (int)nKey;
    pSrc = pKey;
    nSrc = (int)nKey;
  }
  *pnSize = info.nSize;
  spaceLeft = info.nLocal;
  pPayload = &pCell[nHeader];
  pPrior = &pCell[info.iOverflow];

  while( nPayload>0 ){
    if( spaceLeft==0 ){
#ifndef SQLITE_OMIT_AUTOVACUUM
      Pgno pgnoPtrmap = pgnoOvfl; /* Overflow page pointer-map entry page */
      if( pBt->autoVacuum ){
        do{
          pgnoOvfl++;
        } while( 
          PTRMAP_ISPAGE(pBt, pgnoOvfl) || pgnoOvfl==PENDING_BYTE_PAGE(pBt) 
        );
      }
#endif
      rc = allocateBtreePage(pBt, &pOvfl, &pgnoOvfl, pgnoOvfl, 0);
#ifndef SQLITE_OMIT_AUTOVACUUM
      /* If the database supports auto-vacuum, and the second or subsequent
      ** overflow page is being allocated, add an entry to the pointer-map
      ** for that page now. 
      **
      ** If this is the first overflow page, then write a partial entry 
      ** to the pointer-map. If we write nothing to this pointer-map slot,
      ** then the optimistic overflow chain processing in clearCell()
      ** may misinterpret the uninitialized values and delete the
      ** wrong pages from the database.
      */
      if( pBt->autoVacuum && rc==SQLITE_OK ){
        u8 eType = (pgnoPtrmap?PTRMAP_OVERFLOW2:PTRMAP_OVERFLOW1);
        ptrmapPut(pBt, pgnoOvfl, eType, pgnoPtrmap, &rc);
        if( rc ){
          releasePage(pOvfl);
        }
      }
#endif
      if( rc ){
        releasePage(pToRelease);
        return rc;
      }

      /* If pToRelease is not zero than pPrior points into the data area
      ** of pToRelease.  Make sure pToRelease is still writeable. */
      assert( pToRelease==0 || sqlite3PagerIswriteable(pToRelease->pDbPage) );

      /* If pPrior is part of the data area of pPage, then make sure pPage
      ** is still writeable */
      assert( pPrior<pPage->aData || pPrior>=&pPage->aData[pBt->pageSize]
            || sqlite3PagerIswriteable(pPage->pDbPage) );

      put4byte(pPrior, pgnoOvfl);
      releasePage(pToRelease);
      pToRelease = pOvfl;
      pPrior = pOvfl->aData;
      put4byte(pPrior, 0);
      pPayload = &pOvfl->aData[4];
      spaceLeft = pBt->usableSize - 4;
    }
    n = nPayload;
    if( n>spaceLeft ) n = spaceLeft;

    /* If pToRelease is not zero than pPayload points into the data area
    ** of pToRelease.  Make sure pToRelease is still writeable. */
    assert( pToRelease==0 || sqlite3PagerIswriteable(pToRelease->pDbPage) );

    /* If pPayload is part of the data area of pPage, then make sure pPage
    ** is still writeable */
    assert( pPayload<pPage->aData || pPayload>=&pPage->aData[pBt->pageSize]
            || sqlite3PagerIswriteable(pPage->pDbPage) );

    if( nSrc>0 ){
      if( n>nSrc ) n = nSrc;
      assert( pSrc );
      memcpy(pPayload, pSrc, n);
    }else{
      memset(pPayload, 0, n);
    }
    nPayload -= n;
    pPayload += n;
    pSrc += n;
    nSrc -= n;
    spaceLeft -= n;
    if( nSrc==0 ){
      nSrc = nData;
      pSrc = pData;
    }
  }
  releasePage(pToRelease);
  return SQLITE_OK;
}