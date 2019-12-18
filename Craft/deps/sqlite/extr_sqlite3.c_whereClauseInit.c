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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  WhereMaskSet ;
struct TYPE_3__ {int /*<<< orphan*/  wctrlFlags; int /*<<< orphan*/  aStatic; int /*<<< orphan*/  a; int /*<<< orphan*/  nSlot; scalar_t__ nTerm; scalar_t__ pOuter; int /*<<< orphan*/ * pMaskSet; int /*<<< orphan*/ * pParse; } ;
typedef  TYPE_1__ WhereClause ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  ArraySize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void whereClauseInit(
  WhereClause *pWC,        /* The WhereClause to be initialized */
  Parse *pParse,           /* The parsing context */
  WhereMaskSet *pMaskSet,  /* Mapping from table cursor numbers to bitmasks */
  u16 wctrlFlags           /* Might include WHERE_AND_ONLY */
){
  pWC->pParse = pParse;
  pWC->pMaskSet = pMaskSet;
  pWC->pOuter = 0;
  pWC->nTerm = 0;
  pWC->nSlot = ArraySize(pWC->aStatic);
  pWC->a = pWC->aStatic;
  pWC->wctrlFlags = wctrlFlags;
}