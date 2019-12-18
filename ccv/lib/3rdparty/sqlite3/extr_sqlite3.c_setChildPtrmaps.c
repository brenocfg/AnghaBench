#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_8__ {int nCell; int hdrOffset; int /*<<< orphan*/ * aData; int /*<<< orphan*/  leaf; scalar_t__ isInit; TYPE_2__* pBt; int /*<<< orphan*/  pgno; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ BtShared ;

/* Variables and functions */
 int /*<<< orphan*/  PTRMAP_BTREE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int btreeInitPage (TYPE_1__*) ; 
 int /*<<< orphan*/ * findCell (TYPE_1__*,int) ; 
 int /*<<< orphan*/  get4byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptrmapPut (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ptrmapPutOvflPtr (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setChildPtrmaps(MemPage *pPage){
  int i;                             /* Counter variable */
  int nCell;                         /* Number of cells in page pPage */
  int rc;                            /* Return code */
  BtShared *pBt = pPage->pBt;
  Pgno pgno = pPage->pgno;

  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  rc = pPage->isInit ? SQLITE_OK : btreeInitPage(pPage);
  if( rc!=SQLITE_OK ) return rc;
  nCell = pPage->nCell;

  for(i=0; i<nCell; i++){
    u8 *pCell = findCell(pPage, i);

    ptrmapPutOvflPtr(pPage, pCell, &rc);

    if( !pPage->leaf ){
      Pgno childPgno = get4byte(pCell);
      ptrmapPut(pBt, childPgno, PTRMAP_BTREE, pgno, &rc);
    }
  }

  if( !pPage->leaf ){
    Pgno childPgno = get4byte(&pPage->aData[pPage->hdrOffset+8]);
    ptrmapPut(pBt, childPgno, PTRMAP_BTREE, pgno, &rc);
  }

  return rc;
}