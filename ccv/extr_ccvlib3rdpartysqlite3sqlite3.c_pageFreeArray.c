#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_9__ {int* szCell; int /*<<< orphan*/ ** apCell; } ;
struct TYPE_8__ {int hdrOffset; int childPtrSize; TYPE_1__* pBt; int /*<<< orphan*/ * aData; } ;
struct TYPE_7__ {size_t usableSize; } ;
typedef  TYPE_2__ MemPage ;
typedef  TYPE_3__ CellArray ;

/* Variables and functions */
 scalar_t__ SQLITE_WITHIN (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  freeSpace (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pageFreeArray(
  MemPage *pPg,                   /* Page to edit */
  int iFirst,                     /* First cell to delete */
  int nCell,                      /* Cells to delete */
  CellArray *pCArray              /* Array of cells */
){
  u8 * const aData = pPg->aData;
  u8 * const pEnd = &aData[pPg->pBt->usableSize];
  u8 * const pStart = &aData[pPg->hdrOffset + 8 + pPg->childPtrSize];
  int nRet = 0;
  int i;
  int iEnd = iFirst + nCell;
  u8 *pFree = 0;
  int szFree = 0;

  for(i=iFirst; i<iEnd; i++){
    u8 *pCell = pCArray->apCell[i];
    if( SQLITE_WITHIN(pCell, pStart, pEnd) ){
      int sz;
      /* No need to use cachedCellSize() here.  The sizes of all cells that
      ** are to be freed have already been computing while deciding which
      ** cells need freeing */
      sz = pCArray->szCell[i];  assert( sz>0 );
      if( pFree!=(pCell + sz) ){
        if( pFree ){
          assert( pFree>aData && (pFree - aData)<65536 );
          freeSpace(pPg, (u16)(pFree - aData), szFree);
        }
        pFree = pCell;
        szFree = sz;
        if( pFree+sz>pEnd ) return 0;
      }else{
        pFree = pCell;
        szFree += sz;
      }
      nRet++;
    }
  }
  if( pFree ){
    assert( pFree>aData && (pFree - aData)<65536 );
    freeSpace(pPg, (u16)(pFree - aData), szFree);
  }
  return nRet;
}