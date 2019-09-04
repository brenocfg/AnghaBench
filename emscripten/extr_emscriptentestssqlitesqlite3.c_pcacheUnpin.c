#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* xUnpin ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_1__ pcache; } ;
struct TYPE_9__ {int /*<<< orphan*/  pCache; scalar_t__ pPage1; scalar_t__ bPurgeable; } ;
struct TYPE_8__ {int pgno; TYPE_3__* pCache; } ;
typedef  TYPE_2__ PgHdr ;
typedef  TYPE_3__ PCache ;

/* Variables and functions */
 TYPE_5__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcacheUnpin(PgHdr *p){
  PCache *pCache = p->pCache;
  if( pCache->bPurgeable ){
    if( p->pgno==1 ){
      pCache->pPage1 = 0;
    }
    sqlite3GlobalConfig.pcache.xUnpin(pCache->pCache, p, 0);
  }
}