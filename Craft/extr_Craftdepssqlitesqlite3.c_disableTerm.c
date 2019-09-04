#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int wtFlags; size_t iParent; scalar_t__ nChild; TYPE_1__* pWC; int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_2__ WhereTerm ;
struct TYPE_8__ {scalar_t__ iLeftJoin; } ;
typedef  TYPE_3__ WhereLevel ;
struct TYPE_6__ {TYPE_2__* a; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 scalar_t__ ExprHasProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TERM_CODED ; 

__attribute__((used)) static void disableTerm(WhereLevel *pLevel, WhereTerm *pTerm){
  if( pTerm
      && (pTerm->wtFlags & TERM_CODED)==0
      && (pLevel->iLeftJoin==0 || ExprHasProperty(pTerm->pExpr, EP_FromJoin))
  ){
    pTerm->wtFlags |= TERM_CODED;
    if( pTerm->iParent>=0 ){
      WhereTerm *pOther = &pTerm->pWC->a[pTerm->iParent];
      if( (--pOther->nChild)==0 ){
        disableTerm(pLevel, pOther);
      }
    }
  }
}