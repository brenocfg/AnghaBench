#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int nLevel; int /*<<< orphan*/  pWC; struct TYPE_13__* zColAff; TYPE_3__* a; int /*<<< orphan*/  idxStr; scalar_t__ needToFreeIdxStr; } ;
typedef  TYPE_4__ sqlite3_index_info ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  TYPE_4__ WhereInfo ;
struct TYPE_10__ {TYPE_4__* pIdx; } ;
struct TYPE_11__ {int wsFlags; TYPE_1__ u; } ;
struct TYPE_12__ {TYPE_2__ plan; TYPE_4__* pIdxInfo; } ;
typedef  TYPE_4__ Index ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_4__*) ; 
 int WHERE_TEMP_INDEX ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whereClauseClear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void whereInfoFree(sqlite3 *db, WhereInfo *pWInfo){
  if( ALWAYS(pWInfo) ){
    int i;
    for(i=0; i<pWInfo->nLevel; i++){
      sqlite3_index_info *pInfo = pWInfo->a[i].pIdxInfo;
      if( pInfo ){
        /* assert( pInfo->needToFreeIdxStr==0 || db->mallocFailed ); */
        if( pInfo->needToFreeIdxStr ){
          sqlite3_free(pInfo->idxStr);
        }
        sqlite3DbFree(db, pInfo);
      }
      if( pWInfo->a[i].plan.wsFlags & WHERE_TEMP_INDEX ){
        Index *pIdx = pWInfo->a[i].plan.u.pIdx;
        if( pIdx ){
          sqlite3DbFree(db, pIdx->zColAff);
          sqlite3DbFree(db, pIdx);
        }
      }
    }
    whereClauseClear(pWInfo->pWC);
    sqlite3DbFree(db, pWInfo);
  }
}