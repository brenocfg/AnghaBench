#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_13__ {TYPE_4__* pList; } ;
struct TYPE_17__ {int flags; TYPE_1__ x; } ;
struct TYPE_16__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_15__ {int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_14__ {TYPE_5__* pExpr; } ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ ExprList ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 int EP_xIsSelect ; 
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3CodeSubselect (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprCode (TYPE_3__*,TYPE_5__*,int) ; 
 scalar_t__ sqlite3ExprIsVector (TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void codeExprOrVector(Parse *pParse, Expr *p, int iReg, int nReg){
  assert( nReg>0 );
  if( p && sqlite3ExprIsVector(p) ){
#ifndef SQLITE_OMIT_SUBQUERY
    if( (p->flags & EP_xIsSelect) ){
      Vdbe *v = pParse->pVdbe;
      int iSelect = sqlite3CodeSubselect(pParse, p, 0, 0);
      sqlite3VdbeAddOp3(v, OP_Copy, iSelect, iReg, nReg-1);
    }else
#endif
    {
      int i;
      ExprList *pList = p->x.pList;
      assert( nReg<=pList->nExpr );
      for(i=0; i<nReg; i++){
        sqlite3ExprCode(pParse, pList->a[i].pExpr, iReg+i);
      }
    }
  }else{
    assert( nReg==1 );
    sqlite3ExprCode(pParse, p, iReg);
  }
}