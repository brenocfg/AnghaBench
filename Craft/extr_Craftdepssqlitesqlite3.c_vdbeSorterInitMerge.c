#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_8__ {int /*<<< orphan*/  iEof; } ;
typedef  TYPE_1__ VdbeSorterIter ;
struct TYPE_9__ {int nTree; int /*<<< orphan*/  iWriteOff; int /*<<< orphan*/  iReadOff; TYPE_1__* aIter; } ;
typedef  TYPE_2__ VdbeSorter ;
struct TYPE_10__ {TYPE_2__* pSorter; } ;
typedef  TYPE_3__ VdbeCursor ;

/* Variables and functions */
 int SORTER_MAX_MERGE_COUNT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int vdbeSorterDoCompare (TYPE_3__ const*,int) ; 
 int vdbeSorterIterInit (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vdbeSorterInitMerge(
  sqlite3 *db,                    /* Database handle */
  const VdbeCursor *pCsr,         /* Cursor handle for this sorter */
  i64 *pnByte                     /* Sum of bytes in all opened PMAs */
){
  VdbeSorter *pSorter = pCsr->pSorter;
  int rc = SQLITE_OK;             /* Return code */
  int i;                          /* Used to iterator through aIter[] */
  i64 nByte = 0;                  /* Total bytes in all opened PMAs */

  /* Initialize the iterators. */
  for(i=0; i<SORTER_MAX_MERGE_COUNT; i++){
    VdbeSorterIter *pIter = &pSorter->aIter[i];
    rc = vdbeSorterIterInit(db, pSorter, pSorter->iReadOff, pIter, &nByte);
    pSorter->iReadOff = pIter->iEof;
    assert( rc!=SQLITE_OK || pSorter->iReadOff<=pSorter->iWriteOff );
    if( rc!=SQLITE_OK || pSorter->iReadOff>=pSorter->iWriteOff ) break;
  }

  /* Initialize the aTree[] array. */
  for(i=pSorter->nTree-1; rc==SQLITE_OK && i>0; i--){
    rc = vdbeSorterDoCompare(pCsr, i);
  }

  *pnByte = nByte;
  return rc;
}