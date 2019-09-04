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
typedef  int /*<<< orphan*/  WhereMaskSet ;
struct TYPE_5__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_4__ {int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_2__ ExprList ;
typedef  int /*<<< orphan*/  Bitmask ;

/* Variables and functions */
 int /*<<< orphan*/  exprTableUsage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Bitmask exprListTableUsage(WhereMaskSet *pMaskSet, ExprList *pList){
  int i;
  Bitmask mask = 0;
  if( pList ){
    for(i=0; i<pList->nExpr; i++){
      mask |= exprTableUsage(pMaskSet, pList->a[i].pExpr);
    }
  }
  return mask;
}