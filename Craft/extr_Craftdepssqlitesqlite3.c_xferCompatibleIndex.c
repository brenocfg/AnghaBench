#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pTable; int nColumn; scalar_t__ onError; scalar_t__* aiColumn; scalar_t__* aSortOrder; int /*<<< orphan*/ * azColl; } ;
typedef  TYPE_1__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  xferCompatibleCollation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xferCompatibleIndex(Index *pDest, Index *pSrc){
  int i;
  assert( pDest && pSrc );
  assert( pDest->pTable!=pSrc->pTable );
  if( pDest->nColumn!=pSrc->nColumn ){
    return 0;   /* Different number of columns */
  }
  if( pDest->onError!=pSrc->onError ){
    return 0;   /* Different conflict resolution strategies */
  }
  for(i=0; i<pSrc->nColumn; i++){
    if( pSrc->aiColumn[i]!=pDest->aiColumn[i] ){
      return 0;   /* Different columns indexed */
    }
    if( pSrc->aSortOrder[i]!=pDest->aSortOrder[i] ){
      return 0;   /* Different sort orders */
    }
    if( !xferCompatibleCollation(pSrc->azColl[i],pDest->azColl[i]) ){
      return 0;   /* Different collating sequences */
    }
  }

  /* If no test above fails then the indices must be compatible */
  return 1;
}