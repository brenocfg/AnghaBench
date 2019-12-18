#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* pGroup; scalar_t__ bPurgeable; } ;
struct TYPE_8__ {int /*<<< orphan*/  pBuf; } ;
struct TYPE_10__ {TYPE_1__ page; TYPE_4__* pCache; } ;
struct TYPE_9__ {int /*<<< orphan*/  nCurrentPage; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ PgHdr1 ;
typedef  TYPE_4__ PCache1 ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcache1Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcache1FreePage(PgHdr1 *p){
  if( ALWAYS(p) ){
    PCache1 *pCache = p->pCache;
    assert( sqlite3_mutex_held(p->pCache->pGroup->mutex) );
    pcache1Free(p->page.pBuf);
#ifdef SQLITE_PCACHE_SEPARATE_HEADER
    sqlite3_free(p);
#endif
    if( pCache->bPurgeable ){
      pCache->pGroup->nCurrentPage--;
    }
  }
}