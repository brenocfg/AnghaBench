#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_13__ {int /*<<< orphan*/  nCurrentPage; int /*<<< orphan*/  mutex; } ;
struct TYPE_12__ {int szPage; int szExtra; TYPE_6__* pGroup; scalar_t__ bPurgeable; } ;
struct TYPE_10__ {TYPE_2__* pExtra; void* pBuf; } ;
struct TYPE_11__ {TYPE_1__ page; } ;
typedef  TYPE_2__ PgHdr1 ;
typedef  TYPE_3__ PCache1 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* pcache1Alloc (int) ; 
 int /*<<< orphan*/  pcache1EnterMutex (TYPE_6__*) ; 
 int /*<<< orphan*/  pcache1Free (void*) ; 
 int /*<<< orphan*/  pcache1LeaveMutex (TYPE_6__*) ; 
 TYPE_2__* sqlite3Malloc (int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PgHdr1 *pcache1AllocPage(PCache1 *pCache){
  PgHdr1 *p = 0;
  void *pPg;

  /* The group mutex must be released before pcache1Alloc() is called. This
  ** is because it may call sqlite3_release_memory(), which assumes that 
  ** this mutex is not held. */
  assert( sqlite3_mutex_held(pCache->pGroup->mutex) );
  pcache1LeaveMutex(pCache->pGroup);
#ifdef SQLITE_PCACHE_SEPARATE_HEADER
  pPg = pcache1Alloc(pCache->szPage);
  p = sqlite3Malloc(sizeof(PgHdr1) + pCache->szExtra);
  if( !pPg || !p ){
    pcache1Free(pPg);
    sqlite3_free(p);
    pPg = 0;
  }
#else
  pPg = pcache1Alloc(sizeof(PgHdr1) + pCache->szPage + pCache->szExtra);
  p = (PgHdr1 *)&((u8 *)pPg)[pCache->szPage];
#endif
  pcache1EnterMutex(pCache->pGroup);

  if( pPg ){
    p->page.pBuf = pPg;
    p->page.pExtra = &p[1];
    if( pCache->bPurgeable ){
      pCache->pGroup->nCurrentPage++;
    }
    return p;
  }
  return 0;
}