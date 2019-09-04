#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_16__ {scalar_t__ bPurgeable; int nMin; unsigned int nHash; unsigned int nPage; int nRecyclable; int n90pct; int nMax; scalar_t__ szPage; unsigned int iMaxKey; TYPE_1__** apHash; TYPE_2__* pGroup; } ;
struct TYPE_15__ {int mxPinned; int nMaxPage; int nMinPage; scalar_t__ nCurrentPage; TYPE_1__* pLruTail; } ;
struct TYPE_14__ {unsigned int iKey; scalar_t__ pLruNext; scalar_t__ pLruPrev; TYPE_3__* pCache; struct TYPE_14__* pNext; } ;
typedef  TYPE_1__ PgHdr1 ;
typedef  TYPE_2__ PGroup ;
typedef  TYPE_3__ PCache1 ;

/* Variables and functions */
 void* PGHDR1_TO_PAGE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* pcache1AllocPage (TYPE_3__*) ; 
 int /*<<< orphan*/  pcache1EnterMutex (TYPE_2__*) ; 
 int /*<<< orphan*/  pcache1FreePage (TYPE_1__*) ; 
 int /*<<< orphan*/  pcache1LeaveMutex (TYPE_2__*) ; 
 int /*<<< orphan*/  pcache1PinPage (TYPE_1__*) ; 
 int /*<<< orphan*/  pcache1RemoveFromHash (TYPE_1__*) ; 
 scalar_t__ pcache1ResizeHash (TYPE_3__*) ; 
 scalar_t__ pcache1UnderMemoryPressure (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 

__attribute__((used)) static void *pcache1Fetch(sqlite3_pcache *p, unsigned int iKey, int createFlag){
  int nPinned;
  PCache1 *pCache = (PCache1 *)p;
  PGroup *pGroup;
  PgHdr1 *pPage = 0;

  assert( pCache->bPurgeable || createFlag!=1 );
  assert( pCache->bPurgeable || pCache->nMin==0 );
  assert( pCache->bPurgeable==0 || pCache->nMin==10 );
  assert( pCache->nMin==0 || pCache->bPurgeable );
  pcache1EnterMutex(pGroup = pCache->pGroup);

  /* Step 1: Search the hash table for an existing entry. */
  if( pCache->nHash>0 ){
    unsigned int h = iKey % pCache->nHash;
    for(pPage=pCache->apHash[h]; pPage&&pPage->iKey!=iKey; pPage=pPage->pNext);
  }

  /* Step 2: Abort if no existing page is found and createFlag is 0 */
  if( pPage || createFlag==0 ){
    pcache1PinPage(pPage);
    goto fetch_out;
  }

  /* The pGroup local variable will normally be initialized by the
  ** pcache1EnterMutex() macro above.  But if SQLITE_MUTEX_OMIT is defined,
  ** then pcache1EnterMutex() is a no-op, so we have to initialize the
  ** local variable here.  Delaying the initialization of pGroup is an
  ** optimization:  The common case is to exit the module before reaching
  ** this point.
  */
#ifdef SQLITE_MUTEX_OMIT
  pGroup = pCache->pGroup;
#endif


  /* Step 3: Abort if createFlag is 1 but the cache is nearly full */
  nPinned = pCache->nPage - pCache->nRecyclable;
  assert( nPinned>=0 );
  assert( pGroup->mxPinned == pGroup->nMaxPage + 10 - pGroup->nMinPage );
  assert( pCache->n90pct == pCache->nMax*9/10 );
  if( createFlag==1 && (
        nPinned>=pGroup->mxPinned
     || nPinned>=(int)pCache->n90pct
     || pcache1UnderMemoryPressure(pCache)
  )){
    goto fetch_out;
  }

  if( pCache->nPage>=pCache->nHash && pcache1ResizeHash(pCache) ){
    goto fetch_out;
  }

  /* Step 4. Try to recycle a page. */
  if( pCache->bPurgeable && pGroup->pLruTail && (
         (pCache->nPage+1>=pCache->nMax)
      || pGroup->nCurrentPage>=pGroup->nMaxPage
      || pcache1UnderMemoryPressure(pCache)
  )){
    PCache1 *pOtherCache;
    pPage = pGroup->pLruTail;
    pcache1RemoveFromHash(pPage);
    pcache1PinPage(pPage);
    if( (pOtherCache = pPage->pCache)->szPage!=pCache->szPage ){
      pcache1FreePage(pPage);
      pPage = 0;
    }else{
      pGroup->nCurrentPage -= 
               (pOtherCache->bPurgeable - pCache->bPurgeable);
    }
  }

  /* Step 5. If a usable page buffer has still not been found, 
  ** attempt to allocate a new one. 
  */
  if( !pPage ){
    if( createFlag==1 ) sqlite3BeginBenignMalloc();
    pcache1LeaveMutex(pGroup);
    pPage = pcache1AllocPage(pCache);
    pcache1EnterMutex(pGroup);
    if( createFlag==1 ) sqlite3EndBenignMalloc();
  }

  if( pPage ){
    unsigned int h = iKey % pCache->nHash;
    pCache->nPage++;
    pPage->iKey = iKey;
    pPage->pNext = pCache->apHash[h];
    pPage->pCache = pCache;
    pPage->pLruPrev = 0;
    pPage->pLruNext = 0;
    *(void **)(PGHDR1_TO_PAGE(pPage)) = 0;
    pCache->apHash[h] = pPage;
  }

fetch_out:
  if( pPage && iKey>pCache->iMaxKey ){
    pCache->iMaxKey = iKey;
  }
  pcache1LeaveMutex(pGroup);
  return (pPage ? PGHDR1_TO_PAGE(pPage) : 0);
}