#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int nCol; int /*<<< orphan*/ * aCol; } ;
typedef  TYPE_5__ Table ;
struct TYPE_16__ {TYPE_7__* pSelect; } ;
struct TYPE_23__ {int op; int iColumn; TYPE_2__ x; TYPE_5__* pTab; int /*<<< orphan*/  iTable; } ;
struct TYPE_22__ {scalar_t__ pSrcList; int /*<<< orphan*/  pParse; struct TYPE_22__* pNext; } ;
struct TYPE_21__ {TYPE_6__* pSrc; TYPE_4__* pEList; } ;
struct TYPE_20__ {int nSrc; TYPE_1__* a; } ;
struct TYPE_18__ {int nExpr; TYPE_3__* a; } ;
struct TYPE_17__ {TYPE_9__* pExpr; } ;
struct TYPE_15__ {TYPE_7__* pSelect; TYPE_5__* pTab; int /*<<< orphan*/  iCursor; } ;
typedef  TYPE_6__ SrcList ;
typedef  TYPE_7__ Select ;
typedef  TYPE_8__ NameContext ;
typedef  TYPE_9__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_xIsSelect ; 
 int ExprHasProperty (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int TK_AGG_COLUMN ; 
#define  TK_COLUMN 129 
#define  TK_SELECT 128 
 int XN_ROWID ; 
 int /*<<< orphan*/  assert (int) ; 
 char* columnType (TYPE_8__*,TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* sqlite3ColumnType (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zOrigCol ; 
 int /*<<< orphan*/  zOrigDb ; 
 int /*<<< orphan*/  zOrigTab ; 

__attribute__((used)) static const char *columnTypeImpl(
  NameContext *pNC, 
#ifndef SQLITE_ENABLE_COLUMN_METADATA
  Expr *pExpr
#else
  Expr *pExpr,
  const char **pzOrigDb,
  const char **pzOrigTab,
  const char **pzOrigCol
#endif
){
  char const *zType = 0;
  int j;
#ifdef SQLITE_ENABLE_COLUMN_METADATA
  char const *zOrigDb = 0;
  char const *zOrigTab = 0;
  char const *zOrigCol = 0;
#endif

  assert( pExpr!=0 );
  assert( pNC->pSrcList!=0 );
  assert( pExpr->op!=TK_AGG_COLUMN );  /* This routine runes before aggregates
                                       ** are processed */
  switch( pExpr->op ){
    case TK_COLUMN: {
      /* The expression is a column. Locate the table the column is being
      ** extracted from in NameContext.pSrcList. This table may be real
      ** database table or a subquery.
      */
      Table *pTab = 0;            /* Table structure column is extracted from */
      Select *pS = 0;             /* Select the column is extracted from */
      int iCol = pExpr->iColumn;  /* Index of column in pTab */
      while( pNC && !pTab ){
        SrcList *pTabList = pNC->pSrcList;
        for(j=0;j<pTabList->nSrc && pTabList->a[j].iCursor!=pExpr->iTable;j++);
        if( j<pTabList->nSrc ){
          pTab = pTabList->a[j].pTab;
          pS = pTabList->a[j].pSelect;
        }else{
          pNC = pNC->pNext;
        }
      }

      if( pTab==0 ){
        /* At one time, code such as "SELECT new.x" within a trigger would
        ** cause this condition to run.  Since then, we have restructured how
        ** trigger code is generated and so this condition is no longer 
        ** possible. However, it can still be true for statements like
        ** the following:
        **
        **   CREATE TABLE t1(col INTEGER);
        **   SELECT (SELECT t1.col) FROM FROM t1;
        **
        ** when columnType() is called on the expression "t1.col" in the 
        ** sub-select. In this case, set the column type to NULL, even
        ** though it should really be "INTEGER".
        **
        ** This is not a problem, as the column type of "t1.col" is never
        ** used. When columnType() is called on the expression 
        ** "(SELECT t1.col)", the correct type is returned (see the TK_SELECT
        ** branch below.  */
        break;
      }

      assert( pTab && pExpr->pTab==pTab );
      if( pS ){
        /* The "table" is actually a sub-select or a view in the FROM clause
        ** of the SELECT statement. Return the declaration type and origin
        ** data for the result-set column of the sub-select.
        */
        if( iCol>=0 && iCol<pS->pEList->nExpr ){
          /* If iCol is less than zero, then the expression requests the
          ** rowid of the sub-select or view. This expression is legal (see 
          ** test case misc2.2.2) - it always evaluates to NULL.
          */
          NameContext sNC;
          Expr *p = pS->pEList->a[iCol].pExpr;
          sNC.pSrcList = pS->pSrc;
          sNC.pNext = pNC;
          sNC.pParse = pNC->pParse;
          zType = columnType(&sNC, p,&zOrigDb,&zOrigTab,&zOrigCol); 
        }
      }else{
        /* A real table or a CTE table */
        assert( !pS );
#ifdef SQLITE_ENABLE_COLUMN_METADATA
        if( iCol<0 ) iCol = pTab->iPKey;
        assert( iCol==XN_ROWID || (iCol>=0 && iCol<pTab->nCol) );
        if( iCol<0 ){
          zType = "INTEGER";
          zOrigCol = "rowid";
        }else{
          zOrigCol = pTab->aCol[iCol].zName;
          zType = sqlite3ColumnType(&pTab->aCol[iCol],0);
        }
        zOrigTab = pTab->zName;
        if( pNC->pParse && pTab->pSchema ){
          int iDb = sqlite3SchemaToIndex(pNC->pParse->db, pTab->pSchema);
          zOrigDb = pNC->pParse->db->aDb[iDb].zDbSName;
        }
#else
        assert( iCol==XN_ROWID || (iCol>=0 && iCol<pTab->nCol) );
        if( iCol<0 ){
          zType = "INTEGER";
        }else{
          zType = sqlite3ColumnType(&pTab->aCol[iCol],0);
        }
#endif
      }
      break;
    }
#ifndef SQLITE_OMIT_SUBQUERY
    case TK_SELECT: {
      /* The expression is a sub-select. Return the declaration type and
      ** origin info for the single column in the result set of the SELECT
      ** statement.
      */
      NameContext sNC;
      Select *pS = pExpr->x.pSelect;
      Expr *p = pS->pEList->a[0].pExpr;
      assert( ExprHasProperty(pExpr, EP_xIsSelect) );
      sNC.pSrcList = pS->pSrc;
      sNC.pNext = pNC;
      sNC.pParse = pNC->pParse;
      zType = columnType(&sNC, p, &zOrigDb, &zOrigTab, &zOrigCol); 
      break;
    }
#endif
  }

#ifdef SQLITE_ENABLE_COLUMN_METADATA  
  if( pzOrigDb ){
    assert( pzOrigTab && pzOrigCol );
    *pzOrigDb = zOrigDb;
    *pzOrigTab = zOrigTab;
    *pzOrigCol = zOrigCol;
  }
#endif
  return zType;
}