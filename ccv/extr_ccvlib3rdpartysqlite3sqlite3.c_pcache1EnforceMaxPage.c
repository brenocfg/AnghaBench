#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ nPage; scalar_t__ pFree; scalar_t__ pBulk; TYPE_4__* pGroup; } ;
struct TYPE_10__ {TYPE_3__* pLruPrev; } ;
struct TYPE_13__ {scalar_t__ nPurgeable; scalar_t__ nMaxPage; TYPE_1__ lru; int /*<<< orphan*/  mutex; } ;
struct TYPE_12__ {scalar_t__ isAnchor; TYPE_2__* pCache; } ;
struct TYPE_11__ {TYPE_4__* pGroup; } ;
typedef  TYPE_3__ PgHdr1 ;
typedef  TYPE_4__ PGroup ;
typedef  TYPE_5__ PCache1 ;

/* Variables and functions */
 int PAGE_IS_UNPINNED (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pcache1PinPage (TYPE_3__*) ; 
 int /*<<< orphan*/  pcache1RemoveFromHash (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcache1EnforceMaxPage(PCache1 *pCache){
  PGroup *pGroup = pCache->pGroup;
  PgHdr1 *p;
  assert( sqlite3_mutex_held(pGroup->mutex) );
  while( pGroup->nPurgeable>pGroup->nMaxPage
      && (p=pGroup->lru.pLruPrev)->isAnchor==0
  ){
    assert( p->pCache->pGroup==pGroup );
    assert( PAGE_IS_UNPINNED(p) );
    pcache1PinPage(p);
    pcache1RemoveFromHash(p, 1);
  }
  if( pCache->nPage==0 && pCache->pBulk ){
    sqlite3_free(pCache->pBulk);
    pCache->pBulk = pCache->pFree = 0;
  }
}