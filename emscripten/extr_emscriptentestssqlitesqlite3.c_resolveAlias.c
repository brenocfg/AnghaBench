#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_21__ {char* zToken; } ;
struct TYPE_24__ {int flags; scalar_t__ op; scalar_t__ iTable; int /*<<< orphan*/  pColl; TYPE_2__ u; int /*<<< orphan*/  flags2; } ;
struct TYPE_23__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_22__ {scalar_t__ nAlias; int /*<<< orphan*/ * db; } ;
struct TYPE_20__ {scalar_t__ iAlias; TYPE_5__* pExpr; } ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ ExprList ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP2_MallocedToken ; 
 int EP_ExpCollate ; 
 int /*<<< orphan*/  EP_IntValue ; 
 int EP_Reduced ; 
 int EP_Resolved ; 
 int /*<<< orphan*/  EP_Static ; 
 int EP_TokenOnly ; 
 scalar_t__ ExprHasProperty (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExprSetProperty (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TK_AS ; 
 scalar_t__ TK_COLUMN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_5__*) ; 
 char* sqlite3DbStrDup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_5__* sqlite3ExprDup (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* sqlite3PExpr (TYPE_3__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resolveAlias(
  Parse *pParse,         /* Parsing context */
  ExprList *pEList,      /* A result set */
  int iCol,              /* A column in the result set.  0..pEList->nExpr-1 */
  Expr *pExpr,           /* Transform this into an alias to the result set */
  const char *zType      /* "GROUP" or "ORDER" or "" */
){
  Expr *pOrig;           /* The iCol-th column of the result set */
  Expr *pDup;            /* Copy of pOrig */
  sqlite3 *db;           /* The database connection */

  assert( iCol>=0 && iCol<pEList->nExpr );
  pOrig = pEList->a[iCol].pExpr;
  assert( pOrig!=0 );
  assert( pOrig->flags & EP_Resolved );
  db = pParse->db;
  if( pOrig->op!=TK_COLUMN && zType[0]!='G' ){
    pDup = sqlite3ExprDup(db, pOrig, 0);
    pDup = sqlite3PExpr(pParse, TK_AS, pDup, 0, 0);
    if( pDup==0 ) return;
    if( pEList->a[iCol].iAlias==0 ){
      pEList->a[iCol].iAlias = (u16)(++pParse->nAlias);
    }
    pDup->iTable = pEList->a[iCol].iAlias;
  }else if( ExprHasProperty(pOrig, EP_IntValue) || pOrig->u.zToken==0 ){
    pDup = sqlite3ExprDup(db, pOrig, 0);
    if( pDup==0 ) return;
  }else{
    char *zToken = pOrig->u.zToken;
    assert( zToken!=0 );
    pOrig->u.zToken = 0;
    pDup = sqlite3ExprDup(db, pOrig, 0);
    pOrig->u.zToken = zToken;
    if( pDup==0 ) return;
    assert( (pDup->flags & (EP_Reduced|EP_TokenOnly))==0 );
    pDup->flags2 |= EP2_MallocedToken;
    pDup->u.zToken = sqlite3DbStrDup(db, zToken);
  }
  if( pExpr->flags & EP_ExpCollate ){
    pDup->pColl = pExpr->pColl;
    pDup->flags |= EP_ExpCollate;
  }

  /* Before calling sqlite3ExprDelete(), set the EP_Static flag. This 
  ** prevents ExprDelete() from deleting the Expr structure itself,
  ** allowing it to be repopulated by the memcpy() on the following line.
  */
  ExprSetProperty(pExpr, EP_Static);
  sqlite3ExprDelete(db, pExpr);
  memcpy(pExpr, pDup, sizeof(*pExpr));
  sqlite3DbFree(db, pDup);
}