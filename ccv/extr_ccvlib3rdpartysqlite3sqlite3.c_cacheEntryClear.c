#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nTempReg; int nColCache; TYPE_1__* aColCache; int /*<<< orphan*/ * aTempReg; } ;
struct TYPE_4__ {int /*<<< orphan*/  iReg; scalar_t__ tempReg; } ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 scalar_t__ ArraySize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cacheEntryClear(Parse *pParse, int i){
  if( pParse->aColCache[i].tempReg ){
    if( pParse->nTempReg<ArraySize(pParse->aTempReg) ){
      pParse->aTempReg[pParse->nTempReg++] = pParse->aColCache[i].iReg;
    }
  }
  pParse->nColCache--;
  if( i<pParse->nColCache ){
    pParse->aColCache[i] = pParse->aColCache[pParse->nColCache];
  }
}