#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
struct TYPE_6__ {scalar_t__ nOverflow; unsigned char* aData; int hdrOffset; int cellOffset; int nCell; int nFree; int /*<<< orphan*/  pDbPage; TYPE_1__* pBt; } ;
struct TYPE_5__ {int usableSize; int /*<<< orphan*/  pPager; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ MemPage ;

/* Variables and functions */
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_MAX_PAGE_SIZE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int cellSizePtr (TYPE_2__*,unsigned char*) ; 
 int get2byte (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put2byte (unsigned char*,int) ; 
 int sqlite3PagerIswriteable (int /*<<< orphan*/ ) ; 
 unsigned char* sqlite3PagerTempSpace (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int defragmentPage(MemPage *pPage){
  int i;                     /* Loop counter */
  int pc;                    /* Address of a i-th cell */
  int hdr;                   /* Offset to the page header */
  int size;                  /* Size of a cell */
  int usableSize;            /* Number of usable bytes on a page */
  int cellOffset;            /* Offset to the cell pointer array */
  int cbrk;                  /* Offset to the cell content area */
  int nCell;                 /* Number of cells on the page */
  unsigned char *data;       /* The page data */
  unsigned char *temp;       /* Temp area for cell content */
  int iCellFirst;            /* First allowable cell index */
  int iCellLast;             /* Last possible cell index */


  assert( sqlite3PagerIswriteable(pPage->pDbPage) );
  assert( pPage->pBt!=0 );
  assert( pPage->pBt->usableSize <= SQLITE_MAX_PAGE_SIZE );
  assert( pPage->nOverflow==0 );
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  temp = sqlite3PagerTempSpace(pPage->pBt->pPager);
  data = pPage->aData;
  hdr = pPage->hdrOffset;
  cellOffset = pPage->cellOffset;
  nCell = pPage->nCell;
  assert( nCell==get2byte(&data[hdr+3]) );
  usableSize = pPage->pBt->usableSize;
  cbrk = get2byte(&data[hdr+5]);
  memcpy(&temp[cbrk], &data[cbrk], usableSize - cbrk);
  cbrk = usableSize;
  iCellFirst = cellOffset + 2*nCell;
  iCellLast = usableSize - 4;
  for(i=0; i<nCell; i++){
    u8 *pAddr;     /* The i-th cell pointer */
    pAddr = &data[cellOffset + i*2];
    pc = get2byte(pAddr);
    testcase( pc==iCellFirst );
    testcase( pc==iCellLast );
#if !defined(SQLITE_ENABLE_OVERSIZE_CELL_CHECK)
    /* These conditions have already been verified in btreeInitPage()
    ** if SQLITE_ENABLE_OVERSIZE_CELL_CHECK is defined 
    */
    if( pc<iCellFirst || pc>iCellLast ){
      return SQLITE_CORRUPT_BKPT;
    }
#endif
    assert( pc>=iCellFirst && pc<=iCellLast );
    size = cellSizePtr(pPage, &temp[pc]);
    cbrk -= size;
#if defined(SQLITE_ENABLE_OVERSIZE_CELL_CHECK)
    if( cbrk<iCellFirst ){
      return SQLITE_CORRUPT_BKPT;
    }
#else
    if( cbrk<iCellFirst || pc+size>usableSize ){
      return SQLITE_CORRUPT_BKPT;
    }
#endif
    assert( cbrk+size<=usableSize && cbrk>=iCellFirst );
    testcase( cbrk+size==usableSize );
    testcase( pc+size==usableSize );
    memcpy(&data[cbrk], &temp[pc], size);
    put2byte(pAddr, cbrk);
  }
  assert( cbrk>=iCellFirst );
  put2byte(&data[hdr+5], cbrk);
  data[hdr+1] = 0;
  data[hdr+2] = 0;
  data[hdr+7] = 0;
  memset(&data[iCellFirst], 0, cbrk-iCellFirst);
  assert( sqlite3PagerIswriteable(pPage->pDbPage) );
  if( cbrk-iCellFirst!=pPage->nFree ){
    return SQLITE_CORRUPT_BKPT;
  }
  return SQLITE_OK;
}