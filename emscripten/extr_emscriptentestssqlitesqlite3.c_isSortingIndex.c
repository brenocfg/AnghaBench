#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct ExprList_item {int sortOrder; TYPE_6__* pExpr; } ;
struct TYPE_16__ {TYPE_7__* pDfltColl; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  WhereMaskSet ;
struct TYPE_21__ {char* zName; } ;
struct TYPE_20__ {scalar_t__ op; int iTable; int iColumn; } ;
struct TYPE_19__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_18__ {int nColumn; int* aiColumn; int* aSortOrder; char** azColl; scalar_t__ onError; TYPE_1__* pTable; scalar_t__ zName; } ;
struct TYPE_17__ {TYPE_2__* db; } ;
struct TYPE_15__ {int iPKey; } ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ Index ;
typedef  TYPE_5__ ExprList ;
typedef  TYPE_6__ Expr ;
typedef  TYPE_7__ CollSeq ;

/* Variables and functions */
 scalar_t__ OE_None ; 
 scalar_t__ TK_COLUMN ; 
 int WHERE_COLUMN_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  referencesOtherTables (TYPE_5__*,int /*<<< orphan*/ *,int,int) ; 
 TYPE_7__* sqlite3ExprCollSeq (TYPE_3__*,TYPE_6__*) ; 
 scalar_t__ sqlite3StrICmp (char*,char const*) ; 

__attribute__((used)) static int isSortingIndex(
  Parse *pParse,          /* Parsing context */
  WhereMaskSet *pMaskSet, /* Mapping from table cursor numbers to bitmaps */
  Index *pIdx,            /* The index we are testing */
  int base,               /* Cursor number for the table to be sorted */
  ExprList *pOrderBy,     /* The ORDER BY clause */
  int nEqCol,             /* Number of index columns with == constraints */
  int wsFlags,            /* Index usages flags */
  int *pbRev              /* Set to 1 if ORDER BY is DESC */
){
  int i, j;                       /* Loop counters */
  int sortOrder = 0;              /* XOR of index and ORDER BY sort direction */
  int nTerm;                      /* Number of ORDER BY terms */
  struct ExprList_item *pTerm;    /* A term of the ORDER BY clause */
  sqlite3 *db = pParse->db;

  assert( pOrderBy!=0 );
  nTerm = pOrderBy->nExpr;
  assert( nTerm>0 );

  /* Argument pIdx must either point to a 'real' named index structure, 
  ** or an index structure allocated on the stack by bestBtreeIndex() to
  ** represent the rowid index that is part of every table.  */
  assert( pIdx->zName || (pIdx->nColumn==1 && pIdx->aiColumn[0]==-1) );

  /* Match terms of the ORDER BY clause against columns of
  ** the index.
  **
  ** Note that indices have pIdx->nColumn regular columns plus
  ** one additional column containing the rowid.  The rowid column
  ** of the index is also allowed to match against the ORDER BY
  ** clause.
  */
  for(i=j=0, pTerm=pOrderBy->a; j<nTerm && i<=pIdx->nColumn; i++){
    Expr *pExpr;       /* The expression of the ORDER BY pTerm */
    CollSeq *pColl;    /* The collating sequence of pExpr */
    int termSortOrder; /* Sort order for this term */
    int iColumn;       /* The i-th column of the index.  -1 for rowid */
    int iSortOrder;    /* 1 for DESC, 0 for ASC on the i-th index term */
    const char *zColl; /* Name of the collating sequence for i-th index term */

    pExpr = pTerm->pExpr;
    if( pExpr->op!=TK_COLUMN || pExpr->iTable!=base ){
      /* Can not use an index sort on anything that is not a column in the
      ** left-most table of the FROM clause */
      break;
    }
    pColl = sqlite3ExprCollSeq(pParse, pExpr);
    if( !pColl ){
      pColl = db->pDfltColl;
    }
    if( pIdx->zName && i<pIdx->nColumn ){
      iColumn = pIdx->aiColumn[i];
      if( iColumn==pIdx->pTable->iPKey ){
        iColumn = -1;
      }
      iSortOrder = pIdx->aSortOrder[i];
      zColl = pIdx->azColl[i];
    }else{
      iColumn = -1;
      iSortOrder = 0;
      zColl = pColl->zName;
    }
    if( pExpr->iColumn!=iColumn || sqlite3StrICmp(pColl->zName, zColl) ){
      /* Term j of the ORDER BY clause does not match column i of the index */
      if( i<nEqCol ){
        /* If an index column that is constrained by == fails to match an
        ** ORDER BY term, that is OK.  Just ignore that column of the index
        */
        continue;
      }else if( i==pIdx->nColumn ){
        /* Index column i is the rowid.  All other terms match. */
        break;
      }else{
        /* If an index column fails to match and is not constrained by ==
        ** then the index cannot satisfy the ORDER BY constraint.
        */
        return 0;
      }
    }
    assert( pIdx->aSortOrder!=0 || iColumn==-1 );
    assert( pTerm->sortOrder==0 || pTerm->sortOrder==1 );
    assert( iSortOrder==0 || iSortOrder==1 );
    termSortOrder = iSortOrder ^ pTerm->sortOrder;
    if( i>nEqCol ){
      if( termSortOrder!=sortOrder ){
        /* Indices can only be used if all ORDER BY terms past the
        ** equality constraints are all either DESC or ASC. */
        return 0;
      }
    }else{
      sortOrder = termSortOrder;
    }
    j++;
    pTerm++;
    if( iColumn<0 && !referencesOtherTables(pOrderBy, pMaskSet, j, base) ){
      /* If the indexed column is the primary key and everything matches
      ** so far and none of the ORDER BY terms to the right reference other
      ** tables in the join, then we are assured that the index can be used 
      ** to sort because the primary key is unique and so none of the other
      ** columns will make any difference
      */
      j = nTerm;
    }
  }

  *pbRev = sortOrder!=0;
  if( j>=nTerm ){
    /* All terms of the ORDER BY clause are covered by this index so
    ** this index can be used for sorting. */
    return 1;
  }
  if( pIdx->onError!=OE_None && i==pIdx->nColumn
      && (wsFlags & WHERE_COLUMN_NULL)==0
      && !referencesOtherTables(pOrderBy, pMaskSet, j, base) ){
    /* All terms of this index match some prefix of the ORDER BY clause
    ** and the index is UNIQUE and no terms on the tail of the ORDER BY
    ** clause reference other tables in a join.  If this is all true then
    ** the order by clause is superfluous.  Not that if the matching
    ** condition is IS NULL then the result is not necessarily unique
    ** even on a UNIQUE index, so disallow those cases. */
    return 1;
  }
  return 0;
}