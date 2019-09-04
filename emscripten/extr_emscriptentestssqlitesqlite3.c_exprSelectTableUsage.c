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
typedef  int /*<<< orphan*/  WhereMaskSet ;
struct TYPE_3__ {struct TYPE_3__* pPrior; int /*<<< orphan*/  pHaving; int /*<<< orphan*/  pWhere; int /*<<< orphan*/  pOrderBy; int /*<<< orphan*/  pGroupBy; int /*<<< orphan*/  pEList; } ;
typedef  TYPE_1__ Select ;
typedef  int /*<<< orphan*/  Bitmask ;

/* Variables and functions */
 int /*<<< orphan*/  exprListTableUsage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprTableUsage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Bitmask exprSelectTableUsage(WhereMaskSet *pMaskSet, Select *pS){
  Bitmask mask = 0;
  while( pS ){
    mask |= exprListTableUsage(pMaskSet, pS->pEList);
    mask |= exprListTableUsage(pMaskSet, pS->pGroupBy);
    mask |= exprListTableUsage(pMaskSet, pS->pOrderBy);
    mask |= exprTableUsage(pMaskSet, pS->pWhere);
    mask |= exprTableUsage(pMaskSet, pS->pHaving);
    pS = pS->pPrior;
  }
  return mask;
}