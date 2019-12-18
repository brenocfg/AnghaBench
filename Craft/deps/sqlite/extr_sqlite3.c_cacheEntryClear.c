#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct yColCache {scalar_t__ tempReg; int /*<<< orphan*/  iReg; } ;
struct TYPE_3__ {scalar_t__ nTempReg; int /*<<< orphan*/ * aTempReg; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 scalar_t__ ArraySize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cacheEntryClear(Parse *pParse, struct yColCache *p){
  if( p->tempReg ){
    if( pParse->nTempReg<ArraySize(pParse->aTempReg) ){
      pParse->aTempReg[pParse->nTempReg++] = p->iReg;
    }
    p->tempReg = 0;
  }
}