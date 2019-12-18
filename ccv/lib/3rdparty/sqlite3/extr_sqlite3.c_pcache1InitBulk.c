#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int i64 ;
struct TYPE_9__ {scalar_t__ nInitPage; } ;
struct TYPE_8__ {int nMax; int szAlloc; char* pBulk; size_t szPage; scalar_t__ pFree; } ;
struct TYPE_6__ {char* pBuf; TYPE_2__* pExtra; } ;
struct TYPE_7__ {int isBulkLocal; struct TYPE_7__* pNext; scalar_t__ isAnchor; TYPE_1__ page; } ;
typedef  TYPE_2__ PgHdr1 ;
typedef  TYPE_3__ PCache1 ;

/* Variables and functions */
 TYPE_5__ pcache1 ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 
 char* sqlite3Malloc (int) ; 
 int sqlite3MallocSize (char*) ; 

__attribute__((used)) static int pcache1InitBulk(PCache1 *pCache){
  i64 szBulk;
  char *zBulk;
  if( pcache1.nInitPage==0 ) return 0;
  /* Do not bother with a bulk allocation if the cache size very small */
  if( pCache->nMax<3 ) return 0;
  sqlite3BeginBenignMalloc();
  if( pcache1.nInitPage>0 ){
    szBulk = pCache->szAlloc * (i64)pcache1.nInitPage;
  }else{
    szBulk = -1024 * (i64)pcache1.nInitPage;
  }
  if( szBulk > pCache->szAlloc*(i64)pCache->nMax ){
    szBulk = pCache->szAlloc*(i64)pCache->nMax;
  }
  zBulk = pCache->pBulk = sqlite3Malloc( szBulk );
  sqlite3EndBenignMalloc();
  if( zBulk ){
    int nBulk = sqlite3MallocSize(zBulk)/pCache->szAlloc;
    do{
      PgHdr1 *pX = (PgHdr1*)&zBulk[pCache->szPage];
      pX->page.pBuf = zBulk;
      pX->page.pExtra = &pX[1];
      pX->isBulkLocal = 1;
      pX->isAnchor = 0;
      pX->pNext = pCache->pFree;
      pCache->pFree = pX;
      zBulk += pCache->szAlloc;
    }while( --nBulk );
  }
  return pCache->pFree!=0;
}