#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_pcache_page ;
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_2__ {scalar_t__ bPurgeable; int nMin; scalar_t__ nHash; } ;

/* Variables and functions */
 int /*<<< orphan*/  PgHdr1 ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pCache ; 
 int /*<<< orphan*/  page ; 
 scalar_t__ pcache1FetchNoMutex (int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static sqlite3_pcache_page *pcache1Fetch(
  sqlite3_pcache *p, 
  unsigned int iKey, 
  int createFlag
){
#if PCACHE1_MIGHT_USE_GROUP_MUTEX || defined(SQLITE_DEBUG)
  PCache1 *pCache = (PCache1 *)p;
#endif

  assert( offsetof(PgHdr1,page)==0 );
  assert( pCache->bPurgeable || createFlag!=1 );
  assert( pCache->bPurgeable || pCache->nMin==0 );
  assert( pCache->bPurgeable==0 || pCache->nMin==10 );
  assert( pCache->nMin==0 || pCache->bPurgeable );
  assert( pCache->nHash>0 );
#if PCACHE1_MIGHT_USE_GROUP_MUTEX
  if( pCache->pGroup->mutex ){
    return (sqlite3_pcache_page*)pcache1FetchWithMutex(p, iKey, createFlag);
  }else
#endif
  {
    return (sqlite3_pcache_page*)pcache1FetchNoMutex(p, iKey, createFlag);
  }
}