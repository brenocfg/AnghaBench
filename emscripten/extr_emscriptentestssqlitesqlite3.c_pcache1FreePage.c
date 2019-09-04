#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* pGroup; scalar_t__ bPurgeable; } ;
struct TYPE_8__ {TYPE_3__* pCache; } ;
struct TYPE_7__ {int /*<<< orphan*/  nCurrentPage; } ;
typedef  TYPE_2__ PgHdr1 ;
typedef  TYPE_3__ PCache1 ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_2__*) ; 
 int /*<<< orphan*/  PGHDR1_TO_PAGE (TYPE_2__*) ; 
 int /*<<< orphan*/  pcache1Free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcache1FreePage(PgHdr1 *p){
  if( ALWAYS(p) ){
    PCache1 *pCache = p->pCache;
    if( pCache->bPurgeable ){
      pCache->pGroup->nCurrentPage--;
    }
    pcache1Free(PGHDR1_TO_PAGE(p));
  }
}