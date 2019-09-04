#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int usableSize; } ;
typedef  int Pgno ;
typedef  TYPE_1__ BtShared ;

/* Variables and functions */
 int PENDING_BYTE_PAGE (TYPE_1__*) ; 
 scalar_t__ PTRMAP_ISPAGE (TYPE_1__*,int) ; 
 int PTRMAP_PAGENO (TYPE_1__*,int) ; 

__attribute__((used)) static Pgno finalDbSize(BtShared *pBt, Pgno nOrig, Pgno nFree){
  int nEntry;                     /* Number of entries on one ptrmap page */
  Pgno nPtrmap;                   /* Number of PtrMap pages to be freed */
  Pgno nFin;                      /* Return value */

  nEntry = pBt->usableSize/5;
  nPtrmap = (nFree-nOrig+PTRMAP_PAGENO(pBt, nOrig)+nEntry)/nEntry;
  nFin = nOrig - nFree - nPtrmap;
  if( nOrig>PENDING_BYTE_PAGE(pBt) && nFin<PENDING_BYTE_PAGE(pBt) ){
    nFin--;
  }
  while( PTRMAP_ISPAGE(pBt, nFin) || nFin==PENDING_BYTE_PAGE(pBt) ){
    nFin--;
  }

  return nFin;
}