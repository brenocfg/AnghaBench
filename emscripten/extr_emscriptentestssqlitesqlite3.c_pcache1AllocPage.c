#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int szPage; TYPE_1__* pGroup; scalar_t__ bPurgeable; } ;
struct TYPE_5__ {int /*<<< orphan*/  nCurrentPage; } ;
typedef  int /*<<< orphan*/  PgHdr1 ;
typedef  TYPE_2__ PCache1 ;

/* Variables and functions */
 int /*<<< orphan*/ * PAGE_TO_PGHDR1 (TYPE_2__*,void*) ; 
 void* pcache1Alloc (int) ; 

__attribute__((used)) static PgHdr1 *pcache1AllocPage(PCache1 *pCache){
  int nByte = sizeof(PgHdr1) + pCache->szPage;
  void *pPg = pcache1Alloc(nByte);
  PgHdr1 *p;
  if( pPg ){
    p = PAGE_TO_PGHDR1(pCache, pPg);
    if( pCache->bPurgeable ){
      pCache->pGroup->nCurrentPage++;
    }
  }else{
    p = 0;
  }
  return p;
}