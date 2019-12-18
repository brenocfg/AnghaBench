#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  size_t i16 ;
typedef  int /*<<< orphan*/  WhereInfo ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_30__ {TYPE_2__* aCol; } ;
typedef  TYPE_4__ Table ;
struct TYPE_35__ {int nCol; int /*<<< orphan*/  isDeferred; TYPE_4__* pFrom; TYPE_1__* aCol; } ;
struct TYPE_34__ {int nKeyCol; int* aiColumn; TYPE_4__* pTable; } ;
struct TYPE_33__ {TYPE_6__* pParse; TYPE_5__* pSrcList; } ;
struct TYPE_32__ {scalar_t__ nErr; int /*<<< orphan*/ * db; } ;
struct TYPE_31__ {TYPE_3__* a; } ;
struct TYPE_29__ {int /*<<< orphan*/  iCursor; } ;
struct TYPE_28__ {char* zName; } ;
struct TYPE_27__ {int iFrom; } ;
typedef  TYPE_5__ SrcList ;
typedef  TYPE_6__ Parse ;
typedef  TYPE_7__ NameContext ;
typedef  TYPE_8__ Index ;
typedef  TYPE_9__ FKey ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ HasRowid (TYPE_4__*) ; 
 int /*<<< orphan*/  OP_FkCounter ; 
 int /*<<< orphan*/  OP_FkIfZero ; 
 int /*<<< orphan*/  TK_EQ ; 
 int /*<<< orphan*/  TK_ID ; 
 int /*<<< orphan*/  TK_NE ; 
 int /*<<< orphan*/  TK_NOT ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * exprTableColumn (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * exprTableRegister (TYPE_6__*,TYPE_4__*,int,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sqlite3Expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * sqlite3ExprAnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_6__*) ; 
 int /*<<< orphan*/ * sqlite3PExpr (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_8__* sqlite3PrimaryKeyIndex (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3ResolveExprNames (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3WhereBegin (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3WhereEnd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fkScanChildren(
  Parse *pParse,                  /* Parse context */
  SrcList *pSrc,                  /* The child table to be scanned */
  Table *pTab,                    /* The parent table */
  Index *pIdx,                    /* Index on parent covering the foreign key */
  FKey *pFKey,                    /* The foreign key linking pSrc to pTab */
  int *aiCol,                     /* Map from pIdx cols to child table cols */
  int regData,                    /* Parent row data starts here */
  int nIncr                       /* Amount to increment deferred counter by */
){
  sqlite3 *db = pParse->db;       /* Database handle */
  int i;                          /* Iterator variable */
  Expr *pWhere = 0;               /* WHERE clause to scan with */
  NameContext sNameContext;       /* Context used to resolve WHERE clause */
  WhereInfo *pWInfo;              /* Context used by sqlite3WhereXXX() */
  int iFkIfZero = 0;              /* Address of OP_FkIfZero */
  Vdbe *v = sqlite3GetVdbe(pParse);

  assert( pIdx==0 || pIdx->pTable==pTab );
  assert( pIdx==0 || pIdx->nKeyCol==pFKey->nCol );
  assert( pIdx!=0 || pFKey->nCol==1 );
  assert( pIdx!=0 || HasRowid(pTab) );

  if( nIncr<0 ){
    iFkIfZero = sqlite3VdbeAddOp2(v, OP_FkIfZero, pFKey->isDeferred, 0);
    VdbeCoverage(v);
  }

  /* Create an Expr object representing an SQL expression like:
  **
  **   <parent-key1> = <child-key1> AND <parent-key2> = <child-key2> ...
  **
  ** The collation sequence used for the comparison should be that of
  ** the parent key columns. The affinity of the parent key column should
  ** be applied to each child key value before the comparison takes place.
  */
  for(i=0; i<pFKey->nCol; i++){
    Expr *pLeft;                  /* Value from parent table row */
    Expr *pRight;                 /* Column ref to child table */
    Expr *pEq;                    /* Expression (pLeft = pRight) */
    i16 iCol;                     /* Index of column in child table */ 
    const char *zCol;             /* Name of column in child table */

    iCol = pIdx ? pIdx->aiColumn[i] : -1;
    pLeft = exprTableRegister(pParse, pTab, regData, iCol);
    iCol = aiCol ? aiCol[i] : pFKey->aCol[0].iFrom;
    assert( iCol>=0 );
    zCol = pFKey->pFrom->aCol[iCol].zName;
    pRight = sqlite3Expr(db, TK_ID, zCol);
    pEq = sqlite3PExpr(pParse, TK_EQ, pLeft, pRight);
    pWhere = sqlite3ExprAnd(db, pWhere, pEq);
  }

  /* If the child table is the same as the parent table, then add terms
  ** to the WHERE clause that prevent this entry from being scanned.
  ** The added WHERE clause terms are like this:
  **
  **     $current_rowid!=rowid
  **     NOT( $current_a==a AND $current_b==b AND ... )
  **
  ** The first form is used for rowid tables.  The second form is used
  ** for WITHOUT ROWID tables.  In the second form, the primary key is
  ** (a,b,...)
  */
  if( pTab==pFKey->pFrom && nIncr>0 ){
    Expr *pNe;                    /* Expression (pLeft != pRight) */
    Expr *pLeft;                  /* Value from parent table row */
    Expr *pRight;                 /* Column ref to child table */
    if( HasRowid(pTab) ){
      pLeft = exprTableRegister(pParse, pTab, regData, -1);
      pRight = exprTableColumn(db, pTab, pSrc->a[0].iCursor, -1);
      pNe = sqlite3PExpr(pParse, TK_NE, pLeft, pRight);
    }else{
      Expr *pEq, *pAll = 0;
      Index *pPk = sqlite3PrimaryKeyIndex(pTab);
      assert( pIdx!=0 );
      for(i=0; i<pPk->nKeyCol; i++){
        i16 iCol = pIdx->aiColumn[i];
        assert( iCol>=0 );
        pLeft = exprTableRegister(pParse, pTab, regData, iCol);
        pRight = exprTableColumn(db, pTab, pSrc->a[0].iCursor, iCol);
        pEq = sqlite3PExpr(pParse, TK_EQ, pLeft, pRight);
        pAll = sqlite3ExprAnd(db, pAll, pEq);
      }
      pNe = sqlite3PExpr(pParse, TK_NOT, pAll, 0);
    }
    pWhere = sqlite3ExprAnd(db, pWhere, pNe);
  }

  /* Resolve the references in the WHERE clause. */
  memset(&sNameContext, 0, sizeof(NameContext));
  sNameContext.pSrcList = pSrc;
  sNameContext.pParse = pParse;
  sqlite3ResolveExprNames(&sNameContext, pWhere);

  /* Create VDBE to loop through the entries in pSrc that match the WHERE
  ** clause. For each row found, increment either the deferred or immediate
  ** foreign key constraint counter. */
  if( pParse->nErr==0 ){
    pWInfo = sqlite3WhereBegin(pParse, pSrc, pWhere, 0, 0, 0, 0);
    sqlite3VdbeAddOp2(v, OP_FkCounter, pFKey->isDeferred, nIncr);
    if( pWInfo ){
      sqlite3WhereEnd(pWInfo);
    }
  }

  /* Clean up the WHERE clause constructed above. */
  sqlite3ExprDelete(db, pWhere);
  if( iFkIfZero ){
    sqlite3VdbeJumpHere(v, iFkIfZero);
  }
}