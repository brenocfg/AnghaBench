#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct ExprList_item {int /*<<< orphan*/  sortOrder; int /*<<< orphan*/  pExpr; } ;
struct TYPE_12__ {int /*<<< orphan*/ * pDfltColl; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_15__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_14__ {int /*<<< orphan*/ * aSortOrder; int /*<<< orphan*/ ** aColl; TYPE_1__* db; int /*<<< orphan*/  enc; scalar_t__ nField; } ;
struct TYPE_13__ {TYPE_1__* db; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ KeyInfo ;
typedef  TYPE_4__ ExprList ;
typedef  int /*<<< orphan*/  CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  ENC (TYPE_1__*) ; 
 TYPE_3__* sqlite3DbMallocZero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * sqlite3ExprCollSeq (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static KeyInfo *keyInfoFromExprList(Parse *pParse, ExprList *pList){
  sqlite3 *db = pParse->db;
  int nExpr;
  KeyInfo *pInfo;
  struct ExprList_item *pItem;
  int i;

  nExpr = pList->nExpr;
  pInfo = sqlite3DbMallocZero(db, sizeof(*pInfo) + nExpr*(sizeof(CollSeq*)+1) );
  if( pInfo ){
    pInfo->aSortOrder = (u8*)&pInfo->aColl[nExpr];
    pInfo->nField = (u16)nExpr;
    pInfo->enc = ENC(db);
    pInfo->db = db;
    for(i=0, pItem=pList->a; i<nExpr; i++, pItem++){
      CollSeq *pColl;
      pColl = sqlite3ExprCollSeq(pParse, pItem->pExpr);
      if( !pColl ){
        pColl = db->pDfltColl;
      }
      pInfo->aColl[i] = pColl;
      pInfo->aSortOrder[i] = pItem->sortOrder;
    }
  }
  return pInfo;
}