#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_8__ {scalar_t__** apCell; } ;
struct TYPE_7__ {scalar_t__ hdrOffset; scalar_t__* aData; } ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ CellArray ;

/* Variables and functions */
 scalar_t__ CORRUPT_DB ; 
 int /*<<< orphan*/  assert (int) ; 
 int cachedCellSize (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__* pageFindSlot (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  put2byte (scalar_t__*,int) ; 

__attribute__((used)) static int pageInsertArray(
  MemPage *pPg,                   /* Page to add cells to */
  u8 *pBegin,                     /* End of cell-pointer array */
  u8 **ppData,                    /* IN/OUT: Page content -area pointer */
  u8 *pCellptr,                   /* Pointer to cell-pointer area */
  int iFirst,                     /* Index of first cell to add */
  int nCell,                      /* Number of cells to add to pPg */
  CellArray *pCArray              /* Array of cells */
){
  int i;
  u8 *aData = pPg->aData;
  u8 *pData = *ppData;
  int iEnd = iFirst + nCell;
  assert( CORRUPT_DB || pPg->hdrOffset==0 );    /* Never called on page 1 */
  for(i=iFirst; i<iEnd; i++){
    int sz, rc;
    u8 *pSlot;
    sz = cachedCellSize(pCArray, i);
    if( (aData[1]==0 && aData[2]==0) || (pSlot = pageFindSlot(pPg,sz,&rc))==0 ){
      if( (pData - pBegin)<sz ) return 1;
      pData -= sz;
      pSlot = pData;
    }
    /* pSlot and pCArray->apCell[i] will never overlap on a well-formed
    ** database.  But they might for a corrupt database.  Hence use memmove()
    ** since memcpy() sends SIGABORT with overlapping buffers on OpenBSD */
    assert( (pSlot+sz)<=pCArray->apCell[i]
         || pSlot>=(pCArray->apCell[i]+sz)
         || CORRUPT_DB );
    memmove(pSlot, pCArray->apCell[i], sz);
    put2byte(pCellptr, (pSlot - aData));
    pCellptr += 2;
  }
  *ppData = pData;
  return 0;
}