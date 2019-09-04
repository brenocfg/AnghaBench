#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_10__ ;

/* Type definitions */
typedef  char u8 ;
struct TYPE_41__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_5__ sqlite3 ;
struct TYPE_40__ {int /*<<< orphan*/  leftColumn; } ;
struct TYPE_42__ {int prereqRight; int prereqAll; int leftCursor; int iParent; int nChild; int /*<<< orphan*/  wtFlags; void* eOperator; TYPE_4__ u; TYPE_10__* pExpr; } ;
typedef  TYPE_6__ WhereTerm ;
typedef  int /*<<< orphan*/  WhereMaskSet ;
struct TYPE_43__ {scalar_t__ op; TYPE_6__* a; int /*<<< orphan*/ * pMaskSet; TYPE_8__* pParse; } ;
typedef  TYPE_7__ WhereClause ;
struct TYPE_45__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_44__ {TYPE_5__* db; } ;
struct TYPE_39__ {TYPE_9__* pList; int /*<<< orphan*/  pSelect; } ;
struct TYPE_38__ {TYPE_10__* pExpr; } ;
struct TYPE_37__ {int /*<<< orphan*/ * zToken; } ;
struct TYPE_36__ {int op; int iTable; int /*<<< orphan*/  iColumn; TYPE_3__ x; TYPE_1__ u; struct TYPE_36__* pLeft; struct TYPE_36__* pRight; int /*<<< orphan*/  iRightJoinTable; } ;
typedef  int /*<<< orphan*/  SrcList ;
typedef  TYPE_8__ Parse ;
typedef  TYPE_9__ ExprList ;
typedef  TYPE_10__ Expr ;
typedef  int /*<<< orphan*/  CollSeq ;
typedef  int Bitmask ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 int /*<<< orphan*/  EP_xIsSelect ; 
 scalar_t__ ExprHasProperty (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  TERM_COPIED ; 
 int TERM_DYNAMIC ; 
 int TERM_VIRTUAL ; 
 scalar_t__ TK_AND ; 
 int TK_BETWEEN ; 
 scalar_t__ TK_COLUMN ; 
#define  TK_GE 129 
 int TK_IN ; 
 int TK_ISNULL ; 
#define  TK_LE 128 
 char const TK_LT ; 
 char const TK_MATCH ; 
 int TK_OR ; 
 void* WO_MATCH ; 
 scalar_t__ allowedOp (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exprAnalyzeOrTerm (int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 int /*<<< orphan*/  exprCommute (TYPE_8__*,TYPE_10__*) ; 
 int exprListTableUsage (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int exprSelectTableUsage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* exprTableUsage (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int getMask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isLikeOrGlob (TYPE_8__*,TYPE_10__*,TYPE_10__**,int*,int*) ; 
 scalar_t__ isMatchOfColumn (TYPE_10__*) ; 
 void* operatorMask (int) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_5__*,TYPE_10__*) ; 
 TYPE_10__* sqlite3ExprDup (TYPE_5__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* sqlite3ExprSetColl (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3FindCollSeq (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_10__* sqlite3PExpr (TYPE_8__*,char const,TYPE_10__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int sqlite3Strlen30 (int /*<<< orphan*/ *) ; 
 char* sqlite3UpperToLower ; 
 int /*<<< orphan*/  testcase (int) ; 
 int whereClauseInsert (TYPE_7__*,TYPE_10__*,int) ; 

__attribute__((used)) static void exprAnalyze(
  SrcList *pSrc,            /* the FROM clause */
  WhereClause *pWC,         /* the WHERE clause */
  int idxTerm               /* Index of the term to be analyzed */
){
  WhereTerm *pTerm;                /* The term to be analyzed */
  WhereMaskSet *pMaskSet;          /* Set of table index masks */
  Expr *pExpr;                     /* The expression to be analyzed */
  Bitmask prereqLeft;              /* Prerequesites of the pExpr->pLeft */
  Bitmask prereqAll;               /* Prerequesites of pExpr */
  Bitmask extraRight = 0;          /* Extra dependencies on LEFT JOIN */
  Expr *pStr1 = 0;                 /* RHS of LIKE/GLOB operator */
  int isComplete = 0;              /* RHS of LIKE/GLOB ends with wildcard */
  int noCase = 0;                  /* LIKE/GLOB distinguishes case */
  int op;                          /* Top-level operator.  pExpr->op */
  Parse *pParse = pWC->pParse;     /* Parsing context */
  sqlite3 *db = pParse->db;        /* Database connection */

  if( db->mallocFailed ){
    return;
  }
  pTerm = &pWC->a[idxTerm];
  pMaskSet = pWC->pMaskSet;
  pExpr = pTerm->pExpr;
  prereqLeft = exprTableUsage(pMaskSet, pExpr->pLeft);
  op = pExpr->op;
  if( op==TK_IN ){
    assert( pExpr->pRight==0 );
    if( ExprHasProperty(pExpr, EP_xIsSelect) ){
      pTerm->prereqRight = exprSelectTableUsage(pMaskSet, pExpr->x.pSelect);
    }else{
      pTerm->prereqRight = exprListTableUsage(pMaskSet, pExpr->x.pList);
    }
  }else if( op==TK_ISNULL ){
    pTerm->prereqRight = 0;
  }else{
    pTerm->prereqRight = exprTableUsage(pMaskSet, pExpr->pRight);
  }
  prereqAll = exprTableUsage(pMaskSet, pExpr);
  if( ExprHasProperty(pExpr, EP_FromJoin) ){
    Bitmask x = getMask(pMaskSet, pExpr->iRightJoinTable);
    prereqAll |= x;
    extraRight = x-1;  /* ON clause terms may not be used with an index
                       ** on left table of a LEFT JOIN.  Ticket #3015 */
  }
  pTerm->prereqAll = prereqAll;
  pTerm->leftCursor = -1;
  pTerm->iParent = -1;
  pTerm->eOperator = 0;
  if( allowedOp(op) && (pTerm->prereqRight & prereqLeft)==0 ){
    Expr *pLeft = pExpr->pLeft;
    Expr *pRight = pExpr->pRight;
    if( pLeft->op==TK_COLUMN ){
      pTerm->leftCursor = pLeft->iTable;
      pTerm->u.leftColumn = pLeft->iColumn;
      pTerm->eOperator = operatorMask(op);
    }
    if( pRight && pRight->op==TK_COLUMN ){
      WhereTerm *pNew;
      Expr *pDup;
      if( pTerm->leftCursor>=0 ){
        int idxNew;
        pDup = sqlite3ExprDup(db, pExpr, 0);
        if( db->mallocFailed ){
          sqlite3ExprDelete(db, pDup);
          return;
        }
        idxNew = whereClauseInsert(pWC, pDup, TERM_VIRTUAL|TERM_DYNAMIC);
        if( idxNew==0 ) return;
        pNew = &pWC->a[idxNew];
        pNew->iParent = idxTerm;
        pTerm = &pWC->a[idxTerm];
        pTerm->nChild = 1;
        pTerm->wtFlags |= TERM_COPIED;
      }else{
        pDup = pExpr;
        pNew = pTerm;
      }
      exprCommute(pParse, pDup);
      pLeft = pDup->pLeft;
      pNew->leftCursor = pLeft->iTable;
      pNew->u.leftColumn = pLeft->iColumn;
      testcase( (prereqLeft | extraRight) != prereqLeft );
      pNew->prereqRight = prereqLeft | extraRight;
      pNew->prereqAll = prereqAll;
      pNew->eOperator = operatorMask(pDup->op);
    }
  }

#ifndef SQLITE_OMIT_BETWEEN_OPTIMIZATION
  /* If a term is the BETWEEN operator, create two new virtual terms
  ** that define the range that the BETWEEN implements.  For example:
  **
  **      a BETWEEN b AND c
  **
  ** is converted into:
  **
  **      (a BETWEEN b AND c) AND (a>=b) AND (a<=c)
  **
  ** The two new terms are added onto the end of the WhereClause object.
  ** The new terms are "dynamic" and are children of the original BETWEEN
  ** term.  That means that if the BETWEEN term is coded, the children are
  ** skipped.  Or, if the children are satisfied by an index, the original
  ** BETWEEN term is skipped.
  */
  else if( pExpr->op==TK_BETWEEN && pWC->op==TK_AND ){
    ExprList *pList = pExpr->x.pList;
    int i;
    static const u8 ops[] = {TK_GE, TK_LE};
    assert( pList!=0 );
    assert( pList->nExpr==2 );
    for(i=0; i<2; i++){
      Expr *pNewExpr;
      int idxNew;
      pNewExpr = sqlite3PExpr(pParse, ops[i], 
                             sqlite3ExprDup(db, pExpr->pLeft, 0),
                             sqlite3ExprDup(db, pList->a[i].pExpr, 0), 0);
      idxNew = whereClauseInsert(pWC, pNewExpr, TERM_VIRTUAL|TERM_DYNAMIC);
      testcase( idxNew==0 );
      exprAnalyze(pSrc, pWC, idxNew);
      pTerm = &pWC->a[idxTerm];
      pWC->a[idxNew].iParent = idxTerm;
    }
    pTerm->nChild = 2;
  }
#endif /* SQLITE_OMIT_BETWEEN_OPTIMIZATION */

#if !defined(SQLITE_OMIT_OR_OPTIMIZATION) && !defined(SQLITE_OMIT_SUBQUERY)
  /* Analyze a term that is composed of two or more subterms connected by
  ** an OR operator.
  */
  else if( pExpr->op==TK_OR ){
    assert( pWC->op==TK_AND );
    exprAnalyzeOrTerm(pSrc, pWC, idxTerm);
    pTerm = &pWC->a[idxTerm];
  }
#endif /* SQLITE_OMIT_OR_OPTIMIZATION */

#ifndef SQLITE_OMIT_LIKE_OPTIMIZATION
  /* Add constraints to reduce the search space on a LIKE or GLOB
  ** operator.
  **
  ** A like pattern of the form "x LIKE 'abc%'" is changed into constraints
  **
  **          x>='abc' AND x<'abd' AND x LIKE 'abc%'
  **
  ** The last character of the prefix "abc" is incremented to form the
  ** termination condition "abd".
  */
  if( pWC->op==TK_AND 
   && isLikeOrGlob(pParse, pExpr, &pStr1, &isComplete, &noCase)
  ){
    Expr *pLeft;       /* LHS of LIKE/GLOB operator */
    Expr *pStr2;       /* Copy of pStr1 - RHS of LIKE/GLOB operator */
    Expr *pNewExpr1;
    Expr *pNewExpr2;
    int idxNew1;
    int idxNew2;
    CollSeq *pColl;    /* Collating sequence to use */

    pLeft = pExpr->x.pList->a[1].pExpr;
    pStr2 = sqlite3ExprDup(db, pStr1, 0);
    if( !db->mallocFailed ){
      u8 c, *pC;       /* Last character before the first wildcard */
      pC = (u8*)&pStr2->u.zToken[sqlite3Strlen30(pStr2->u.zToken)-1];
      c = *pC;
      if( noCase ){
        /* The point is to increment the last character before the first
        ** wildcard.  But if we increment '@', that will push it into the
        ** alphabetic range where case conversions will mess up the 
        ** inequality.  To avoid this, make sure to also run the full
        ** LIKE on all candidate expressions by clearing the isComplete flag
        */
        if( c=='A'-1 ) isComplete = 0;   /* EV: R-64339-08207 */


        c = sqlite3UpperToLower[c];
      }
      *pC = c + 1;
    }
    pColl = sqlite3FindCollSeq(db, SQLITE_UTF8, noCase ? "NOCASE" : "BINARY",0);
    pNewExpr1 = sqlite3PExpr(pParse, TK_GE, 
                     sqlite3ExprSetColl(sqlite3ExprDup(db,pLeft,0), pColl),
                     pStr1, 0);
    idxNew1 = whereClauseInsert(pWC, pNewExpr1, TERM_VIRTUAL|TERM_DYNAMIC);
    testcase( idxNew1==0 );
    exprAnalyze(pSrc, pWC, idxNew1);
    pNewExpr2 = sqlite3PExpr(pParse, TK_LT,
                     sqlite3ExprSetColl(sqlite3ExprDup(db,pLeft,0), pColl),
                     pStr2, 0);
    idxNew2 = whereClauseInsert(pWC, pNewExpr2, TERM_VIRTUAL|TERM_DYNAMIC);
    testcase( idxNew2==0 );
    exprAnalyze(pSrc, pWC, idxNew2);
    pTerm = &pWC->a[idxTerm];
    if( isComplete ){
      pWC->a[idxNew1].iParent = idxTerm;
      pWC->a[idxNew2].iParent = idxTerm;
      pTerm->nChild = 2;
    }
  }
#endif /* SQLITE_OMIT_LIKE_OPTIMIZATION */

#ifndef SQLITE_OMIT_VIRTUALTABLE
  /* Add a WO_MATCH auxiliary term to the constraint set if the
  ** current expression is of the form:  column MATCH expr.
  ** This information is used by the xBestIndex methods of
  ** virtual tables.  The native query optimizer does not attempt
  ** to do anything with MATCH functions.
  */
  if( isMatchOfColumn(pExpr) ){
    int idxNew;
    Expr *pRight, *pLeft;
    WhereTerm *pNewTerm;
    Bitmask prereqColumn, prereqExpr;

    pRight = pExpr->x.pList->a[0].pExpr;
    pLeft = pExpr->x.pList->a[1].pExpr;
    prereqExpr = exprTableUsage(pMaskSet, pRight);
    prereqColumn = exprTableUsage(pMaskSet, pLeft);
    if( (prereqExpr & prereqColumn)==0 ){
      Expr *pNewExpr;
      pNewExpr = sqlite3PExpr(pParse, TK_MATCH, 
                              0, sqlite3ExprDup(db, pRight, 0), 0);
      idxNew = whereClauseInsert(pWC, pNewExpr, TERM_VIRTUAL|TERM_DYNAMIC);
      testcase( idxNew==0 );
      pNewTerm = &pWC->a[idxNew];
      pNewTerm->prereqRight = prereqExpr;
      pNewTerm->leftCursor = pLeft->iTable;
      pNewTerm->u.leftColumn = pLeft->iColumn;
      pNewTerm->eOperator = WO_MATCH;
      pNewTerm->iParent = idxTerm;
      pTerm = &pWC->a[idxTerm];
      pTerm->nChild = 1;
      pTerm->wtFlags |= TERM_COPIED;
      pNewTerm->prereqAll = pTerm->prereqAll;
    }
  }
#endif /* SQLITE_OMIT_VIRTUALTABLE */

#ifdef SQLITE_ENABLE_STAT2
  /* When sqlite_stat2 histogram data is available an operator of the
  ** form "x IS NOT NULL" can sometimes be evaluated more efficiently
  ** as "x>NULL" if x is not an INTEGER PRIMARY KEY.  So construct a
  ** virtual term of that form.
  **
  ** Note that the virtual term must be tagged with TERM_VNULL.  This
  ** TERM_VNULL tag will suppress the not-null check at the beginning
  ** of the loop.  Without the TERM_VNULL flag, the not-null check at
  ** the start of the loop will prevent any results from being returned.
  */
  if( pExpr->op==TK_NOTNULL
   && pExpr->pLeft->op==TK_COLUMN
   && pExpr->pLeft->iColumn>=0
  ){
    Expr *pNewExpr;
    Expr *pLeft = pExpr->pLeft;
    int idxNew;
    WhereTerm *pNewTerm;

    pNewExpr = sqlite3PExpr(pParse, TK_GT,
                            sqlite3ExprDup(db, pLeft, 0),
                            sqlite3PExpr(pParse, TK_NULL, 0, 0, 0), 0);

    idxNew = whereClauseInsert(pWC, pNewExpr,
                              TERM_VIRTUAL|TERM_DYNAMIC|TERM_VNULL);
    if( idxNew ){
      pNewTerm = &pWC->a[idxNew];
      pNewTerm->prereqRight = 0;
      pNewTerm->leftCursor = pLeft->iTable;
      pNewTerm->u.leftColumn = pLeft->iColumn;
      pNewTerm->eOperator = WO_GT;
      pNewTerm->iParent = idxTerm;
      pTerm = &pWC->a[idxTerm];
      pTerm->nChild = 1;
      pTerm->wtFlags |= TERM_COPIED;
      pNewTerm->prereqAll = pTerm->prereqAll;
    }
  }
#endif /* SQLITE_ENABLE_STAT2 */

  /* Prevent ON clause terms of a LEFT JOIN from being used to drive
  ** an index for tables to the left of the join.
  */
  pTerm->prereqRight |= extraRight;
}