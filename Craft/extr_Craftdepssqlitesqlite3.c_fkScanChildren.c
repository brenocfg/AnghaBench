#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_54__   TYPE_9__ ;
typedef  struct TYPE_53__   TYPE_8__ ;
typedef  struct TYPE_52__   TYPE_7__ ;
typedef  struct TYPE_51__   TYPE_6__ ;
typedef  struct TYPE_50__   TYPE_5__ ;
typedef  struct TYPE_49__   TYPE_4__ ;
typedef  struct TYPE_48__   TYPE_3__ ;
typedef  struct TYPE_47__   TYPE_2__ ;
typedef  struct TYPE_46__   TYPE_1__ ;
typedef  struct TYPE_45__   TYPE_18__ ;
typedef  struct TYPE_44__   TYPE_12__ ;
typedef  struct TYPE_43__   TYPE_11__ ;
typedef  struct TYPE_42__   TYPE_10__ ;

/* Type definitions */
struct TYPE_49__ {TYPE_1__* pDfltColl; } ;
typedef  TYPE_4__ sqlite3 ;
typedef  int /*<<< orphan*/  WhereInfo ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_50__ {int iPKey; TYPE_12__* aCol; } ;
typedef  TYPE_5__ Table ;
struct TYPE_54__ {int* aiColumn; TYPE_5__* pTable; } ;
struct TYPE_53__ {TYPE_7__* pParse; TYPE_6__* pSrcList; } ;
struct TYPE_52__ {TYPE_4__* db; } ;
struct TYPE_51__ {TYPE_3__* a; } ;
struct TYPE_48__ {int iCursor; } ;
struct TYPE_47__ {int iFrom; } ;
struct TYPE_46__ {char* zName; } ;
struct TYPE_45__ {int mayAbort; } ;
struct TYPE_44__ {char* zColl; char* zName; void* affinity; } ;
struct TYPE_43__ {int iTable; int iColumn; void* affinity; } ;
struct TYPE_42__ {scalar_t__ isDeferred; int nCol; TYPE_5__* pFrom; TYPE_2__* aCol; } ;
typedef  TYPE_6__ SrcList ;
typedef  TYPE_7__ Parse ;
typedef  TYPE_8__ NameContext ;
typedef  TYPE_9__ Index ;
typedef  TYPE_10__ FKey ;
typedef  TYPE_11__ Expr ;
typedef  TYPE_12__ Column ;

/* Variables and functions */
 int /*<<< orphan*/  OP_FkCounter ; 
 int /*<<< orphan*/  OP_FkIfZero ; 
 void* SQLITE_AFF_INTEGER ; 
 int /*<<< orphan*/  TK_COLUMN ; 
 int /*<<< orphan*/  TK_EQ ; 
 int /*<<< orphan*/  TK_ID ; 
 int /*<<< orphan*/  TK_NE ; 
 int /*<<< orphan*/  TK_REGISTER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 TYPE_11__* sqlite3Expr (TYPE_4__*,int /*<<< orphan*/ ,char const*) ; 
 TYPE_11__* sqlite3ExprAddCollateString (TYPE_7__*,TYPE_11__*,char const*) ; 
 TYPE_11__* sqlite3ExprAnd (TYPE_4__*,TYPE_11__*,TYPE_11__*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_4__*,TYPE_11__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_7__*) ; 
 TYPE_11__* sqlite3PExpr (TYPE_7__*,int /*<<< orphan*/ ,TYPE_11__*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 TYPE_18__* sqlite3ParseToplevel (TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3ResolveExprNames (TYPE_8__*,TYPE_11__*) ; 
 int sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3WhereBegin (TYPE_7__*,TYPE_6__*,TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3WhereEnd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fkScanChildren(
  Parse *pParse,                  /* Parse context */
  SrcList *pSrc,                  /* SrcList containing the table to scan */
  Table *pTab,
  Index *pIdx,                    /* Foreign key index */
  FKey *pFKey,                    /* Foreign key relationship */
  int *aiCol,                     /* Map from pIdx cols to child table cols */
  int regData,                    /* Referenced table data starts here */
  int nIncr                       /* Amount to increment deferred counter by */
){
  sqlite3 *db = pParse->db;       /* Database handle */
  int i;                          /* Iterator variable */
  Expr *pWhere = 0;               /* WHERE clause to scan with */
  NameContext sNameContext;       /* Context used to resolve WHERE clause */
  WhereInfo *pWInfo;              /* Context used by sqlite3WhereXXX() */
  int iFkIfZero = 0;              /* Address of OP_FkIfZero */
  Vdbe *v = sqlite3GetVdbe(pParse);

  assert( !pIdx || pIdx->pTable==pTab );

  if( nIncr<0 ){
    iFkIfZero = sqlite3VdbeAddOp2(v, OP_FkIfZero, pFKey->isDeferred, 0);
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
    int iCol;                     /* Index of column in child table */ 
    const char *zCol;             /* Name of column in child table */

    pLeft = sqlite3Expr(db, TK_REGISTER, 0);
    if( pLeft ){
      /* Set the collation sequence and affinity of the LHS of each TK_EQ
      ** expression to the parent key column defaults.  */
      if( pIdx ){
        Column *pCol;
        const char *zColl;
        iCol = pIdx->aiColumn[i];
        pCol = &pTab->aCol[iCol];
        if( pTab->iPKey==iCol ) iCol = -1;
        pLeft->iTable = regData+iCol+1;
        pLeft->affinity = pCol->affinity;
        zColl = pCol->zColl;
        if( zColl==0 ) zColl = db->pDfltColl->zName;
        pLeft = sqlite3ExprAddCollateString(pParse, pLeft, zColl);
      }else{
        pLeft->iTable = regData;
        pLeft->affinity = SQLITE_AFF_INTEGER;
      }
    }
    iCol = aiCol ? aiCol[i] : pFKey->aCol[0].iFrom;
    assert( iCol>=0 );
    zCol = pFKey->pFrom->aCol[iCol].zName;
    pRight = sqlite3Expr(db, TK_ID, zCol);
    pEq = sqlite3PExpr(pParse, TK_EQ, pLeft, pRight, 0);
    pWhere = sqlite3ExprAnd(db, pWhere, pEq);
  }

  /* If the child table is the same as the parent table, and this scan
  ** is taking place as part of a DELETE operation (operation D.2), omit the
  ** row being deleted from the scan by adding ($rowid != rowid) to the WHERE 
  ** clause, where $rowid is the rowid of the row being deleted.  */
  if( pTab==pFKey->pFrom && nIncr>0 ){
    Expr *pEq;                    /* Expression (pLeft = pRight) */
    Expr *pLeft;                  /* Value from parent table row */
    Expr *pRight;                 /* Column ref to child table */
    pLeft = sqlite3Expr(db, TK_REGISTER, 0);
    pRight = sqlite3Expr(db, TK_COLUMN, 0);
    if( pLeft && pRight ){
      pLeft->iTable = regData;
      pLeft->affinity = SQLITE_AFF_INTEGER;
      pRight->iTable = pSrc->a[0].iCursor;
      pRight->iColumn = -1;
    }
    pEq = sqlite3PExpr(pParse, TK_NE, pLeft, pRight, 0);
    pWhere = sqlite3ExprAnd(db, pWhere, pEq);
  }

  /* Resolve the references in the WHERE clause. */
  memset(&sNameContext, 0, sizeof(NameContext));
  sNameContext.pSrcList = pSrc;
  sNameContext.pParse = pParse;
  sqlite3ResolveExprNames(&sNameContext, pWhere);

  /* Create VDBE to loop through the entries in pSrc that match the WHERE
  ** clause. If the constraint is not deferred, throw an exception for
  ** each row found. Otherwise, for deferred constraints, increment the
  ** deferred constraint counter by nIncr for each row selected.  */
  pWInfo = sqlite3WhereBegin(pParse, pSrc, pWhere, 0, 0, 0, 0);
  if( nIncr>0 && pFKey->isDeferred==0 ){
    sqlite3ParseToplevel(pParse)->mayAbort = 1;
  }
  sqlite3VdbeAddOp2(v, OP_FkCounter, pFKey->isDeferred, nIncr);
  if( pWInfo ){
    sqlite3WhereEnd(pWInfo);
  }

  /* Clean up the WHERE clause constructed above. */
  sqlite3ExprDelete(db, pWhere);
  if( iFkIfZero ){
    sqlite3VdbeJumpHere(v, iFkIfZero);
  }
}