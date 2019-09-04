#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i16 ;
struct TYPE_6__ {struct TYPE_6__* pRight; struct TYPE_6__* pLeft; scalar_t__ iRightJoinTable; } ;
typedef  TYPE_1__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 int EP_Reduced ; 
 int EP_TokenOnly ; 
 int /*<<< orphan*/  ExprHasAnyProperty (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ExprSetIrreducible (TYPE_1__*) ; 
 int /*<<< orphan*/  ExprSetProperty (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void setJoinExpr(Expr *p, int iTable){
  while( p ){
    ExprSetProperty(p, EP_FromJoin);
    assert( !ExprHasAnyProperty(p, EP_TokenOnly|EP_Reduced) );
    ExprSetIrreducible(p);
    p->iRightJoinTable = (i16)iTable;
    setJoinExpr(p->pLeft, iTable);
    p = p->pRight;
  } 
}