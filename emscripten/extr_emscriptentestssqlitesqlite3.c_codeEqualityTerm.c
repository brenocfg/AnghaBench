#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct InLoop {int iCur; int /*<<< orphan*/  addrInTop; } ;
struct TYPE_19__ {TYPE_7__* pExpr; } ;
typedef  TYPE_4__ WhereTerm ;
struct TYPE_17__ {int nIn; struct InLoop* aInLoop; } ;
struct TYPE_18__ {TYPE_2__ in; } ;
struct TYPE_16__ {int wsFlags; } ;
struct TYPE_20__ {TYPE_3__ u; int /*<<< orphan*/  addrNxt; TYPE_1__ plan; } ;
typedef  TYPE_5__ WhereLevel ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_22__ {scalar_t__ op; int iTable; int /*<<< orphan*/  pRight; } ;
struct TYPE_21__ {int /*<<< orphan*/  db; int /*<<< orphan*/ * pVdbe; } ;
typedef  TYPE_6__ Parse ;
typedef  TYPE_7__ Expr ;

/* Variables and functions */
 int IN_INDEX_ROWID ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_IsNull ; 
 int /*<<< orphan*/  OP_Null ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  OP_Rowid ; 
 scalar_t__ TK_EQ ; 
 scalar_t__ TK_IN ; 
 scalar_t__ TK_ISNULL ; 
 int WHERE_IN_ABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  disableTerm (TYPE_5__*,TYPE_4__*) ; 
 struct InLoop* sqlite3DbReallocOrFree (int /*<<< orphan*/ ,struct InLoop*,int) ; 
 int sqlite3ExprCodeTarget (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3FindInIndex (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int codeEqualityTerm(
  Parse *pParse,      /* The parsing context */
  WhereTerm *pTerm,   /* The term of the WHERE clause to be coded */
  WhereLevel *pLevel, /* When level of the FROM clause we are working on */
  int iTarget         /* Attempt to leave results in this register */
){
  Expr *pX = pTerm->pExpr;
  Vdbe *v = pParse->pVdbe;
  int iReg;                  /* Register holding results */

  assert( iTarget>0 );
  if( pX->op==TK_EQ ){
    iReg = sqlite3ExprCodeTarget(pParse, pX->pRight, iTarget);
  }else if( pX->op==TK_ISNULL ){
    iReg = iTarget;
    sqlite3VdbeAddOp2(v, OP_Null, 0, iReg);
#ifndef SQLITE_OMIT_SUBQUERY
  }else{
    int eType;
    int iTab;
    struct InLoop *pIn;

    assert( pX->op==TK_IN );
    iReg = iTarget;
    eType = sqlite3FindInIndex(pParse, pX, 0);
    iTab = pX->iTable;
    sqlite3VdbeAddOp2(v, OP_Rewind, iTab, 0);
    assert( pLevel->plan.wsFlags & WHERE_IN_ABLE );
    if( pLevel->u.in.nIn==0 ){
      pLevel->addrNxt = sqlite3VdbeMakeLabel(v);
    }
    pLevel->u.in.nIn++;
    pLevel->u.in.aInLoop =
       sqlite3DbReallocOrFree(pParse->db, pLevel->u.in.aInLoop,
                              sizeof(pLevel->u.in.aInLoop[0])*pLevel->u.in.nIn);
    pIn = pLevel->u.in.aInLoop;
    if( pIn ){
      pIn += pLevel->u.in.nIn - 1;
      pIn->iCur = iTab;
      if( eType==IN_INDEX_ROWID ){
        pIn->addrInTop = sqlite3VdbeAddOp2(v, OP_Rowid, iTab, iReg);
      }else{
        pIn->addrInTop = sqlite3VdbeAddOp3(v, OP_Column, iTab, 0, iReg);
      }
      sqlite3VdbeAddOp1(v, OP_IsNull, iReg);
    }else{
      pLevel->u.in.nIn = 0;
    }
#endif
  }
  disableTerm(pLevel, pTerm);
  return iReg;
}