#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
struct TYPE_7__ {scalar_t__ nOverflow; unsigned char* aData; int hdrOffset; int cellOffset; int nCell; int (* xCellSize ) (TYPE_2__*,unsigned char*) ;unsigned char nFree; int /*<<< orphan*/  pDbPage; TYPE_1__* pBt; } ;
struct TYPE_6__ {int usableSize; int /*<<< orphan*/  pPager; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ MemPage ;

/* Variables and functions */
 int SQLITE_CORRUPT_PAGE (TYPE_2__*) ; 
 int SQLITE_MAX_PAGE_SIZE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int get2byte (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put2byte (unsigned char*,int) ; 
 int sqlite3PagerIswriteable (int /*<<< orphan*/ ) ; 
 unsigned char* sqlite3PagerTempSpace (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,unsigned char*) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int defragmentPage(MemPage *pPage, int nMaxFrag){
  int i;                     /* Loop counter */
  int pc;                    /* Address of the i-th cell */
  int hdr;                   /* Offset to the page header */
  int size;                  /* Size of a cell */
  int usableSize;            /* Number of usable bytes on a page */
  int cellOffset;            /* Offset to the cell pointer array */
  int cbrk;                  /* Offset to the cell content area */
  int nCell;                 /* Number of cells on the page */
  unsigned char *data;       /* The page data */
  unsigned char *temp;       /* Temp area for cell content */
  unsigned char *src;        /* Source of content */
  int iCellFirst;            /* First allowable cell index */
  int iCellLast;             /* Last possible cell index */

  assert( sqlite3PagerIswriteable(pPage->pDbPage) );
  assert( pPage->pBt!=0 );
  assert( pPage->pBt->usableSize <= SQLITE_MAX_PAGE_SIZE );
  assert( pPage->nOverflow==0 );
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  temp = 0;
  src = data = pPage->aData;
  hdr = pPage->hdrOffset;
  cellOffset = pPage->cellOffset;
  nCell = pPage->nCell;
  assert( nCell==get2byte(&data[hdr+3]) );
  iCellFirst = cellOffset + 2*nCell;
  usableSize = pPage->pBt->usableSize;

  /* This block handles pages with two or fewer free blocks and nMaxFrag
  ** or fewer fragmented bytes. In this case it is faster to move the
  ** two (or one) blocks of cells using memmove() and add the required
  ** offsets to each pointer in the cell-pointer array than it is to 
  ** reconstruct the entire page.  */
  if( (int)data[hdr+7]<=nMaxFrag ){
    int iFree = get2byte(&data[hdr+1]);
    if( iFree ){
      int iFree2 = get2byte(&data[iFree]);

      /* pageFindSlot() has already verified that free blocks are sorted
      ** in order of offset within the page, and that no block extends
      ** past the end of the page. Provided the two free slots do not 
      ** overlap, this guarantees that the memmove() calls below will not
      ** overwrite the usableSize byte buffer, even if the database page
      ** is corrupt.  */
      assert( iFree2==0 || iFree2>iFree );
      assert( iFree+get2byte(&data[iFree+2]) <= usableSize );
      assert( iFree2==0 || iFree2+get2byte(&data[iFree2+2]) <= usableSize );

      if( 0==iFree2 || (data[iFree2]==0 && data[iFree2+1]==0) ){
        u8 *pEnd = &data[cellOffset + nCell*2];
        u8 *pAddr;
        int sz2 = 0;
        int sz = get2byte(&data[iFree+2]);
        int top = get2byte(&data[hdr+5]);
        if( top>=iFree ){
          return SQLITE_CORRUPT_PAGE(pPage);
        }
        if( iFree2 ){
          assert( iFree+sz<=iFree2 ); /* Verified by pageFindSlot() */
          sz2 = get2byte(&data[iFree2+2]);
          assert( iFree+sz+sz2+iFree2-(iFree+sz) <= usableSize );
          memmove(&data[iFree+sz+sz2], &data[iFree+sz], iFree2-(iFree+sz));
          sz += sz2;
        }
        cbrk = top+sz;
        assert( cbrk+(iFree-top) <= usableSize );
        memmove(&data[cbrk], &data[top], iFree-top);
        for(pAddr=&data[cellOffset]; pAddr<pEnd; pAddr+=2){
          pc = get2byte(pAddr);
          if( pc<iFree ){ put2byte(pAddr, pc+sz); }
          else if( pc<iFree2 ){ put2byte(pAddr, pc+sz2); }
        }
        goto defragment_out;
      }
    }
  }

  cbrk = usableSize;
  iCellLast = usableSize - 4;
  for(i=0; i<nCell; i++){
    u8 *pAddr;     /* The i-th cell pointer */
    pAddr = &data[cellOffset + i*2];
    pc = get2byte(pAddr);
    testcase( pc==iCellFirst );
    testcase( pc==iCellLast );
    /* These conditions have already been verified in btreeInitPage()
    ** if PRAGMA cell_size_check=ON.
    */
    if( pc<iCellFirst || pc>iCellLast ){
      return SQLITE_CORRUPT_PAGE(pPage);
    }
    assert( pc>=iCellFirst && pc<=iCellLast );
    size = pPage->xCellSize(pPage, &src[pc]);
    cbrk -= size;
    if( cbrk<iCellFirst || pc+size>usableSize ){
      return SQLITE_CORRUPT_PAGE(pPage);
    }
    assert( cbrk+size<=usableSize && cbrk>=iCellFirst );
    testcase( cbrk+size==usableSize );
    testcase( pc+size==usableSize );
    put2byte(pAddr, cbrk);
    if( temp==0 ){
      int x;
      if( cbrk==pc ) continue;
      temp = sqlite3PagerTempSpace(pPage->pBt->pPager);
      x = get2byte(&data[hdr+5]);
      memcpy(&temp[x], &data[x], (cbrk+size) - x);
      src = temp;
    }
    memcpy(&data[cbrk], &src[pc], size);
  }
  data[hdr+7] = 0;

 defragment_out:
  if( data[hdr+7]+cbrk-iCellFirst!=pPage->nFree ){
    return SQLITE_CORRUPT_PAGE(pPage);
  }
  assert( cbrk>=iCellFirst );
  put2byte(&data[hdr+5], cbrk);
  data[hdr+1] = 0;
  data[hdr+2] = 0;
  memset(&data[iCellFirst], 0, cbrk-iCellFirst);
  assert( sqlite3PagerIswriteable(pPage->pDbPage) );
  return SQLITE_OK;
}