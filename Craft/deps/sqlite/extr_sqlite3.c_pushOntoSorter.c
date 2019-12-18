#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_17__ {int nExpr; int iECursor; } ;
struct TYPE_16__ {int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_15__ {int selFlags; int iLimit; int iOffset; } ;
typedef  TYPE_1__ Select ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ ExprList ;

/* Variables and functions */
 int OP_AddImm ; 
 int /*<<< orphan*/  OP_Delete ; 
 int /*<<< orphan*/  OP_Goto ; 
 int OP_IdxInsert ; 
 int /*<<< orphan*/  OP_IfZero ; 
 int /*<<< orphan*/  OP_Last ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int OP_Sequence ; 
 int OP_SorterInsert ; 
 int SF_UseSorter ; 
 int /*<<< orphan*/  sqlite3ExprCacheClear (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ExprCodeExprList (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprCodeMove (TYPE_2__*,int,int,int) ; 
 int sqlite3GetTempRange (TYPE_2__*,int) ; 
 int sqlite3GetTempReg (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempRange (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_2__*,int) ; 
 int sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pushOntoSorter(
  Parse *pParse,         /* Parser context */
  ExprList *pOrderBy,    /* The ORDER BY clause */
  Select *pSelect,       /* The whole SELECT statement */
  int regData            /* Register holding data to be sorted */
){
  Vdbe *v = pParse->pVdbe;
  int nExpr = pOrderBy->nExpr;
  int regBase = sqlite3GetTempRange(pParse, nExpr+2);
  int regRecord = sqlite3GetTempReg(pParse);
  int op;
  sqlite3ExprCacheClear(pParse);
  sqlite3ExprCodeExprList(pParse, pOrderBy, regBase, 0);
  sqlite3VdbeAddOp2(v, OP_Sequence, pOrderBy->iECursor, regBase+nExpr);
  sqlite3ExprCodeMove(pParse, regData, regBase+nExpr+1, 1);
  sqlite3VdbeAddOp3(v, OP_MakeRecord, regBase, nExpr + 2, regRecord);
  if( pSelect->selFlags & SF_UseSorter ){
    op = OP_SorterInsert;
  }else{
    op = OP_IdxInsert;
  }
  sqlite3VdbeAddOp2(v, op, pOrderBy->iECursor, regRecord);
  sqlite3ReleaseTempReg(pParse, regRecord);
  sqlite3ReleaseTempRange(pParse, regBase, nExpr+2);
  if( pSelect->iLimit ){
    int addr1, addr2;
    int iLimit;
    if( pSelect->iOffset ){
      iLimit = pSelect->iOffset+1;
    }else{
      iLimit = pSelect->iLimit;
    }
    addr1 = sqlite3VdbeAddOp1(v, OP_IfZero, iLimit);
    sqlite3VdbeAddOp2(v, OP_AddImm, iLimit, -1);
    addr2 = sqlite3VdbeAddOp0(v, OP_Goto);
    sqlite3VdbeJumpHere(v, addr1);
    sqlite3VdbeAddOp1(v, OP_Last, pOrderBy->iECursor);
    sqlite3VdbeAddOp1(v, OP_Delete, pOrderBy->iECursor);
    sqlite3VdbeJumpHere(v, addr2);
  }
}