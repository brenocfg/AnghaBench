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
struct TYPE_12__ {int /*<<< orphan*/  idxStr; scalar_t__ needToFreeIdxStr; } ;
typedef  TYPE_3__ sqlite3_index_info ;
struct TYPE_13__ {TYPE_2__* pParse; TYPE_3__** ppIdxInfo; TYPE_1__* pSrc; } ;
typedef  TYPE_4__ WhereBestIdx ;
struct TYPE_14__ {scalar_t__ mallocFailed; } ;
struct TYPE_11__ {TYPE_5__* db; } ;
struct TYPE_10__ {int /*<<< orphan*/  pTab; } ;

/* Variables and functions */
 scalar_t__ IsVirtual (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bestBtreeIndex (TYPE_4__*) ; 
 int /*<<< orphan*/  bestVirtualIndex (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bestIndex(WhereBestIdx *p){
#ifndef SQLITE_OMIT_VIRTUALTABLE
  if( IsVirtual(p->pSrc->pTab) ){
    sqlite3_index_info *pIdxInfo = 0;
    p->ppIdxInfo = &pIdxInfo;
    bestVirtualIndex(p);
    assert( pIdxInfo!=0 || p->pParse->db->mallocFailed );
    if( pIdxInfo && pIdxInfo->needToFreeIdxStr ){
      sqlite3_free(pIdxInfo->idxStr);
    }
    sqlite3DbFree(p->pParse->db, pIdxInfo);
  }else
#endif
  {
    bestBtreeIndex(p);
  }
}