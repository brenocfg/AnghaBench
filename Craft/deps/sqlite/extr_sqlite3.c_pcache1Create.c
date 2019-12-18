#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_7__ {int mxPinned; int nMinPage; int nMaxPage; } ;
struct TYPE_10__ {TYPE_1__ grp; } ;
struct TYPE_9__ {scalar_t__ bCoreMutex; } ;
struct TYPE_8__ {int szPage; int szExtra; int bPurgeable; int nMin; TYPE_1__* pGroup; } ;
typedef  TYPE_1__ PGroup ;
typedef  TYPE_2__ PCache1 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__ pcache1 ; 
 int /*<<< orphan*/  pcache1EnterMutex (TYPE_1__*) ; 
 int /*<<< orphan*/  pcache1LeaveMutex (TYPE_1__*) ; 
 TYPE_3__ sqlite3GlobalConfig ; 
 scalar_t__ sqlite3MallocZero (int) ; 

__attribute__((used)) static sqlite3_pcache *pcache1Create(int szPage, int szExtra, int bPurgeable){
  PCache1 *pCache;      /* The newly created page cache */
  PGroup *pGroup;       /* The group the new page cache will belong to */
  int sz;               /* Bytes of memory required to allocate the new cache */

  /*
  ** The seperateCache variable is true if each PCache has its own private
  ** PGroup.  In other words, separateCache is true for mode (1) where no
  ** mutexing is required.
  **
  **   *  Always use a unified cache (mode-2) if ENABLE_MEMORY_MANAGEMENT
  **
  **   *  Always use a unified cache in single-threaded applications
  **
  **   *  Otherwise (if multi-threaded and ENABLE_MEMORY_MANAGEMENT is off)
  **      use separate caches (mode-1)
  */
#if defined(SQLITE_ENABLE_MEMORY_MANAGEMENT) || SQLITE_THREADSAFE==0
  const int separateCache = 0;
#else
  int separateCache = sqlite3GlobalConfig.bCoreMutex>0;
#endif

  assert( (szPage & (szPage-1))==0 && szPage>=512 && szPage<=65536 );
  assert( szExtra < 300 );

  sz = sizeof(PCache1) + sizeof(PGroup)*separateCache;
  pCache = (PCache1 *)sqlite3MallocZero(sz);
  if( pCache ){
    if( separateCache ){
      pGroup = (PGroup*)&pCache[1];
      pGroup->mxPinned = 10;
    }else{
      pGroup = &pcache1.grp;
    }
    pCache->pGroup = pGroup;
    pCache->szPage = szPage;
    pCache->szExtra = szExtra;
    pCache->bPurgeable = (bPurgeable ? 1 : 0);
    if( bPurgeable ){
      pCache->nMin = 10;
      pcache1EnterMutex(pGroup);
      pGroup->nMinPage += pCache->nMin;
      pGroup->mxPinned = pGroup->nMaxPage + 10 - pGroup->nMinPage;
      pcache1LeaveMutex(pGroup);
    }
  }
  return (sqlite3_pcache *)pCache;
}