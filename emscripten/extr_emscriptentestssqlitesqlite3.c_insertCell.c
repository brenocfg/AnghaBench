#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_10__ {scalar_t__ idx; int /*<<< orphan*/ * pCell; } ;
struct TYPE_9__ {scalar_t__ autoVacuum; scalar_t__ usableSize; int /*<<< orphan*/  mutex; } ;
struct TYPE_8__ {int nCell; int nOverflow; int nFree; int cellOffset; int hdrOffset; TYPE_6__* pBt; int /*<<< orphan*/ * aData; int /*<<< orphan*/  pDbPage; TYPE_7__* aOvfl; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ MemPage ;

/* Variables and functions */
 int ArraySize (TYPE_7__*) ; 
 int MX_CELL (TYPE_6__*) ; 
 int SQLITE_OK ; 
 int SQLITE_PTR_TO_INT (int /*<<< orphan*/ *) ; 
 int allocateSpace (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int cellSizePtr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptrmapPutOvflPtr (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  put2byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put4byte (int /*<<< orphan*/ *,scalar_t__) ; 
 int sqlite3PagerIswriteable (int /*<<< orphan*/ ) ; 
 int sqlite3PagerWrite (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void insertCell(
  MemPage *pPage,   /* Page into which we are copying */
  int i,            /* New cell becomes the i-th cell of the page */
  u8 *pCell,        /* Content of the new cell */
  int sz,           /* Bytes of content in pCell */
  u8 *pTemp,        /* Temp storage space for pCell, if needed */
  Pgno iChild,      /* If non-zero, replace first 4 bytes with this value */
  int *pRC          /* Read and write return code from here */
){
  int idx = 0;      /* Where to write new cell content in data[] */
  int j;            /* Loop counter */
  int end;          /* First byte past the last cell pointer in data[] */
  int ins;          /* Index in data[] where new cell pointer is inserted */
  int cellOffset;   /* Address of first cell pointer in data[] */
  u8 *data;         /* The content of the whole page */
  u8 *ptr;          /* Used for moving information around in data[] */
  u8 *endPtr;       /* End of the loop */

  int nSkip = (iChild ? 4 : 0);

  if( *pRC ) return;

  assert( i>=0 && i<=pPage->nCell+pPage->nOverflow );
  assert( pPage->nCell<=MX_CELL(pPage->pBt) && MX_CELL(pPage->pBt)<=10921 );
  assert( pPage->nOverflow<=ArraySize(pPage->aOvfl) );
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  /* The cell should normally be sized correctly.  However, when moving a
  ** malformed cell from a leaf page to an interior page, if the cell size
  ** wanted to be less than 4 but got rounded up to 4 on the leaf, then size
  ** might be less than 8 (leaf-size + pointer) on the interior node.  Hence
  ** the term after the || in the following assert(). */
  assert( sz==cellSizePtr(pPage, pCell) || (sz==8 && iChild>0) );
  if( pPage->nOverflow || sz+2>pPage->nFree ){
    if( pTemp ){
      memcpy(pTemp+nSkip, pCell+nSkip, sz-nSkip);
      pCell = pTemp;
    }
    if( iChild ){
      put4byte(pCell, iChild);
    }
    j = pPage->nOverflow++;
    assert( j<(int)(sizeof(pPage->aOvfl)/sizeof(pPage->aOvfl[0])) );
    pPage->aOvfl[j].pCell = pCell;
    pPage->aOvfl[j].idx = (u16)i;
  }else{
    int rc = sqlite3PagerWrite(pPage->pDbPage);
    if( rc!=SQLITE_OK ){
      *pRC = rc;
      return;
    }
    assert( sqlite3PagerIswriteable(pPage->pDbPage) );
    data = pPage->aData;
    cellOffset = pPage->cellOffset;
    end = cellOffset + 2*pPage->nCell;
    ins = cellOffset + 2*i;
    rc = allocateSpace(pPage, sz, &idx);
    if( rc ){ *pRC = rc; return; }
    /* The allocateSpace() routine guarantees the following two properties
    ** if it returns success */
    assert( idx >= end+2 );
    assert( idx+sz <= (int)pPage->pBt->usableSize );
    pPage->nCell++;
    pPage->nFree -= (u16)(2 + sz);
    memcpy(&data[idx+nSkip], pCell+nSkip, sz-nSkip);
    if( iChild ){
      put4byte(&data[idx], iChild);
    }
    ptr = &data[end];
    endPtr = &data[ins];
    assert( (SQLITE_PTR_TO_INT(ptr)&1)==0 );  /* ptr is always 2-byte aligned */
    while( ptr>endPtr ){
      *(u16*)ptr = *(u16*)&ptr[-2];
      ptr -= 2;
    }
    put2byte(&data[ins], idx);
    put2byte(&data[pPage->hdrOffset+3], pPage->nCell);
#ifndef SQLITE_OMIT_AUTOVACUUM
    if( pPage->pBt->autoVacuum ){
      /* The cell may contain a pointer to an overflow page. If so, write
      ** the entry for the overflow page into the pointer map.
      */
      ptrmapPutOvflPtr(pPage, pCell, pRC);
    }
#endif
  }
}