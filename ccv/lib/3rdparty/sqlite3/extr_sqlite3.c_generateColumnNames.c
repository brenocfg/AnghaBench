#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int flags; scalar_t__ mallocFailed; } ;
typedef  TYPE_3__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_20__ {int iPKey; int nCol; int /*<<< orphan*/  zName; TYPE_1__* aCol; } ;
typedef  TYPE_4__ Table ;
struct TYPE_24__ {scalar_t__ op; int iColumn; TYPE_4__* pTab; } ;
struct TYPE_23__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_22__ {int colNamesSet; scalar_t__ explain; TYPE_3__* db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_21__ {TYPE_7__* pEList; int /*<<< orphan*/ * pSrc; struct TYPE_21__* pPrior; } ;
struct TYPE_18__ {char* zName; char* zSpan; TYPE_8__* pExpr; } ;
struct TYPE_17__ {char* zName; } ;
typedef  int /*<<< orphan*/  SrcList ;
typedef  TYPE_5__ Select ;
typedef  TYPE_6__ Parse ;
typedef  TYPE_7__ ExprList ;
typedef  TYPE_8__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  COLNAME_NAME ; 
 int /*<<< orphan*/  SELECTTRACE (int,TYPE_6__*,TYPE_5__*,char*) ; 
 int /*<<< orphan*/  SQLITE_DYNAMIC ; 
 int SQLITE_FullColNames ; 
 int SQLITE_ShortColNames ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 scalar_t__ TK_AGG_COLUMN ; 
 scalar_t__ TK_COLUMN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  generateColumnTypes (TYPE_6__*,int /*<<< orphan*/ *,TYPE_7__*) ; 
 void* sqlite3DbStrDup (TYPE_3__*,char const*) ; 
 void* sqlite3MPrintf (TYPE_3__*,char*,int,...) ; 
 int /*<<< orphan*/  sqlite3VdbeSetColName (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeSetNumCols (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void generateColumnNames(
  Parse *pParse,      /* Parser context */
  Select *pSelect     /* Generate column names for this SELECT statement */
){
  Vdbe *v = pParse->pVdbe;
  int i;
  Table *pTab;
  SrcList *pTabList;
  ExprList *pEList;
  sqlite3 *db = pParse->db;
  int fullName;    /* TABLE.COLUMN if no AS clause and is a direct table ref */
  int srcName;     /* COLUMN or TABLE.COLUMN if no AS clause and is direct */

#ifndef SQLITE_OMIT_EXPLAIN
  /* If this is an EXPLAIN, skip this step */
  if( pParse->explain ){
    return;
  }
#endif

  if( pParse->colNamesSet || db->mallocFailed ) return;
  /* Column names are determined by the left-most term of a compound select */
  while( pSelect->pPrior ) pSelect = pSelect->pPrior;
  SELECTTRACE(1,pParse,pSelect,("generating column names\n"));
  pTabList = pSelect->pSrc;
  pEList = pSelect->pEList;
  assert( v!=0 );
  assert( pTabList!=0 );
  pParse->colNamesSet = 1;
  fullName = (db->flags & SQLITE_FullColNames)!=0;
  srcName = (db->flags & SQLITE_ShortColNames)!=0 || fullName;
  sqlite3VdbeSetNumCols(v, pEList->nExpr);
  for(i=0; i<pEList->nExpr; i++){
    Expr *p = pEList->a[i].pExpr;

    assert( p!=0 );
    assert( p->op!=TK_AGG_COLUMN );  /* Agg processing has not run yet */
    assert( p->op!=TK_COLUMN || p->pTab!=0 ); /* Covering idx not yet coded */
    if( pEList->a[i].zName ){
      /* An AS clause always takes first priority */
      char *zName = pEList->a[i].zName;
      sqlite3VdbeSetColName(v, i, COLNAME_NAME, zName, SQLITE_TRANSIENT);
    }else if( srcName && p->op==TK_COLUMN ){
      char *zCol;
      int iCol = p->iColumn;
      pTab = p->pTab;
      assert( pTab!=0 );
      if( iCol<0 ) iCol = pTab->iPKey;
      assert( iCol==-1 || (iCol>=0 && iCol<pTab->nCol) );
      if( iCol<0 ){
        zCol = "rowid";
      }else{
        zCol = pTab->aCol[iCol].zName;
      }
      if( fullName ){
        char *zName = 0;
        zName = sqlite3MPrintf(db, "%s.%s", pTab->zName, zCol);
        sqlite3VdbeSetColName(v, i, COLNAME_NAME, zName, SQLITE_DYNAMIC);
      }else{
        sqlite3VdbeSetColName(v, i, COLNAME_NAME, zCol, SQLITE_TRANSIENT);
      }
    }else{
      const char *z = pEList->a[i].zSpan;
      z = z==0 ? sqlite3MPrintf(db, "column%d", i+1) : sqlite3DbStrDup(db, z);
      sqlite3VdbeSetColName(v, i, COLNAME_NAME, z, SQLITE_DYNAMIC);
    }
  }
  generateColumnTypes(pParse, pTabList, pEList);
}