#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct SrcList_item {int /*<<< orphan*/  pTab; } ;
struct TYPE_8__ {int /*<<< orphan*/  idxStr; scalar_t__ needToFreeIdxStr; } ;
typedef  TYPE_1__ sqlite3_index_info ;
typedef  int /*<<< orphan*/  WhereCost ;
typedef  int /*<<< orphan*/  WhereClause ;
struct TYPE_9__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ Parse ;
typedef  int /*<<< orphan*/  ExprList ;
typedef  int /*<<< orphan*/  Bitmask ;

/* Variables and functions */
 scalar_t__ IsVirtual (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bestBtreeIndex (TYPE_2__*,int /*<<< orphan*/ *,struct SrcList_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bestVirtualIndex (TYPE_2__*,int /*<<< orphan*/ *,struct SrcList_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bestIndex(
  Parse *pParse,              /* The parsing context */
  WhereClause *pWC,           /* The WHERE clause */
  struct SrcList_item *pSrc,  /* The FROM clause term to search */
  Bitmask notReady,           /* Mask of cursors not available for indexing */
  Bitmask notValid,           /* Cursors not available for any purpose */
  ExprList *pOrderBy,         /* The ORDER BY clause */
  WhereCost *pCost            /* Lowest cost query plan */
){
#ifndef SQLITE_OMIT_VIRTUALTABLE
  if( IsVirtual(pSrc->pTab) ){
    sqlite3_index_info *p = 0;
    bestVirtualIndex(pParse, pWC, pSrc, notReady, notValid, pOrderBy, pCost,&p);
    if( p->needToFreeIdxStr ){
      sqlite3_free(p->idxStr);
    }
    sqlite3DbFree(pParse->db, p);
  }else
#endif
  {
    bestBtreeIndex(pParse, pWC, pSrc, notReady, notValid, pOrderBy, pCost);
  }
}