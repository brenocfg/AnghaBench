#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_66__   TYPE_9__ ;
typedef  struct TYPE_65__   TYPE_8__ ;
typedef  struct TYPE_64__   TYPE_7__ ;
typedef  struct TYPE_63__   TYPE_6__ ;
typedef  struct TYPE_62__   TYPE_5__ ;
typedef  struct TYPE_61__   TYPE_53__ ;
typedef  struct TYPE_60__   TYPE_50__ ;
typedef  struct TYPE_59__   TYPE_4__ ;
typedef  struct TYPE_58__   TYPE_3__ ;
typedef  struct TYPE_57__   TYPE_2__ ;
typedef  struct TYPE_56__   TYPE_1__ ;
typedef  struct TYPE_55__   TYPE_11__ ;
typedef  struct TYPE_54__   TYPE_10__ ;

/* Type definitions */
struct SrcList_item {scalar_t__ zName; char* zAlias; int jointype; int /*<<< orphan*/  pUsing; TYPE_6__* pTab; TYPE_8__* pSelect; int /*<<< orphan*/  zDatabase; } ;
struct ExprList_item {TYPE_11__* pExpr; scalar_t__ zSpan; scalar_t__ zName; } ;
struct TYPE_58__ {int flags; scalar_t__ mallocFailed; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_59__ {TYPE_9__* pParse; } ;
typedef  TYPE_4__ Walker ;
struct TYPE_62__ {char* z; int /*<<< orphan*/  n; } ;
typedef  TYPE_5__ Token ;
struct TYPE_63__ {int nRef; char* zName; int nCol; int iPKey; int nRowEst; TYPE_50__* aCol; scalar_t__ pSelect; int /*<<< orphan*/  tabFlags; } ;
typedef  TYPE_6__ Table ;
struct TYPE_66__ {TYPE_3__* db; } ;
struct TYPE_65__ {int selFlags; TYPE_10__* pEList; struct TYPE_65__* pPrior; TYPE_7__* pSrc; } ;
struct TYPE_64__ {int nSrc; struct SrcList_item* a; } ;
struct TYPE_57__ {char* zToken; } ;
struct TYPE_61__ {scalar_t__ op; TYPE_2__ u; } ;
struct TYPE_60__ {char* zName; } ;
struct TYPE_56__ {scalar_t__ op; } ;
struct TYPE_55__ {scalar_t__ op; TYPE_53__* pLeft; TYPE_1__* pRight; } ;
struct TYPE_54__ {int nExpr; struct ExprList_item* a; } ;
typedef  TYPE_7__ SrcList ;
typedef  TYPE_8__ Select ;
typedef  TYPE_9__ Parse ;
typedef  TYPE_10__ ExprList ;
typedef  TYPE_11__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_IntValue ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_53__*,int /*<<< orphan*/ ) ; 
 scalar_t__ IsHiddenColumn (TYPE_50__*) ; 
 int IsVirtual (TYPE_6__*) ; 
 int JT_NATURAL ; 
 scalar_t__ NEVER (int) ; 
 int SF_Expanded ; 
 int SQLITE_FullColNames ; 
 int SQLITE_ShortColNames ; 
 int /*<<< orphan*/  TF_Ephemeral ; 
 scalar_t__ TK_ALL ; 
 scalar_t__ TK_DOT ; 
 scalar_t__ TK_ID ; 
 int WRC_Abort ; 
 int WRC_Continue ; 
 int WRC_Prune ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  selectColumnsFromExprList (TYPE_9__*,TYPE_10__*,int*,TYPE_50__**) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_3__*,char*) ; 
 TYPE_6__* sqlite3DbMallocZero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_9__*,char*,...) ; 
 TYPE_11__* sqlite3Expr (TYPE_3__*,scalar_t__,char*) ; 
 TYPE_10__* sqlite3ExprListAppend (TYPE_9__*,TYPE_10__*,TYPE_11__*) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (TYPE_3__*,TYPE_10__*) ; 
 int /*<<< orphan*/  sqlite3ExprListSetName (TYPE_9__*,TYPE_10__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3IdListIndex (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sqlite3IndexedByLookup (TYPE_9__*,struct SrcList_item*) ; 
 TYPE_6__* sqlite3LocateTable (TYPE_9__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 void* sqlite3MPrintf (TYPE_3__*,char*,char*,...) ; 
 TYPE_11__* sqlite3PExpr (TYPE_9__*,scalar_t__,TYPE_11__*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* sqlite3SelectDup (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListAssignCursors (TYPE_9__*,TYPE_7__*) ; 
 scalar_t__ sqlite3StrICmp (char*,char*) ; 
 int /*<<< orphan*/  sqlite3Strlen30 (char*) ; 
 scalar_t__ sqlite3ViewGetColumnNames (TYPE_9__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3WalkSelect (TYPE_4__*,TYPE_8__*) ; 
 scalar_t__ sqliteProcessJoin (TYPE_9__*,TYPE_8__*) ; 
 scalar_t__ tableAndColumnIndex (TYPE_7__*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selectExpander(Walker *pWalker, Select *p){
  Parse *pParse = pWalker->pParse;
  int i, j, k;
  SrcList *pTabList;
  ExprList *pEList;
  struct SrcList_item *pFrom;
  sqlite3 *db = pParse->db;

  if( db->mallocFailed  ){
    return WRC_Abort;
  }
  if( NEVER(p->pSrc==0) || (p->selFlags & SF_Expanded)!=0 ){
    return WRC_Prune;
  }
  p->selFlags |= SF_Expanded;
  pTabList = p->pSrc;
  pEList = p->pEList;

  /* Make sure cursor numbers have been assigned to all entries in
  ** the FROM clause of the SELECT statement.
  */
  sqlite3SrcListAssignCursors(pParse, pTabList);

  /* Look up every table named in the FROM clause of the select.  If
  ** an entry of the FROM clause is a subquery instead of a table or view,
  ** then create a transient table structure to describe the subquery.
  */
  for(i=0, pFrom=pTabList->a; i<pTabList->nSrc; i++, pFrom++){
    Table *pTab;
    if( pFrom->pTab!=0 ){
      /* This statement has already been prepared.  There is no need
      ** to go further. */
      assert( i==0 );
      return WRC_Prune;
    }
    if( pFrom->zName==0 ){
#ifndef SQLITE_OMIT_SUBQUERY
      Select *pSel = pFrom->pSelect;
      /* A sub-query in the FROM clause of a SELECT */
      assert( pSel!=0 );
      assert( pFrom->pTab==0 );
      sqlite3WalkSelect(pWalker, pSel);
      pFrom->pTab = pTab = sqlite3DbMallocZero(db, sizeof(Table));
      if( pTab==0 ) return WRC_Abort;
      pTab->nRef = 1;
      pTab->zName = sqlite3MPrintf(db, "sqlite_subquery_%p_", (void*)pTab);
      while( pSel->pPrior ){ pSel = pSel->pPrior; }
      selectColumnsFromExprList(pParse, pSel->pEList, &pTab->nCol, &pTab->aCol);
      pTab->iPKey = -1;
      pTab->nRowEst = 1000000;
      pTab->tabFlags |= TF_Ephemeral;
#endif
    }else{
      /* An ordinary table or view name in the FROM clause */
      assert( pFrom->pTab==0 );
      pFrom->pTab = pTab = 
        sqlite3LocateTable(pParse,0,pFrom->zName,pFrom->zDatabase);
      if( pTab==0 ) return WRC_Abort;
      pTab->nRef++;
#if !defined(SQLITE_OMIT_VIEW) || !defined (SQLITE_OMIT_VIRTUALTABLE)
      if( pTab->pSelect || IsVirtual(pTab) ){
        /* We reach here if the named table is a really a view */
        if( sqlite3ViewGetColumnNames(pParse, pTab) ) return WRC_Abort;
        assert( pFrom->pSelect==0 );
        pFrom->pSelect = sqlite3SelectDup(db, pTab->pSelect, 0);
        sqlite3WalkSelect(pWalker, pFrom->pSelect);
      }
#endif
    }

    /* Locate the index named by the INDEXED BY clause, if any. */
    if( sqlite3IndexedByLookup(pParse, pFrom) ){
      return WRC_Abort;
    }
  }

  /* Process NATURAL keywords, and ON and USING clauses of joins.
  */
  if( db->mallocFailed || sqliteProcessJoin(pParse, p) ){
    return WRC_Abort;
  }

  /* For every "*" that occurs in the column list, insert the names of
  ** all columns in all tables.  And for every TABLE.* insert the names
  ** of all columns in TABLE.  The parser inserted a special expression
  ** with the TK_ALL operator for each "*" that it found in the column list.
  ** The following code just has to locate the TK_ALL expressions and expand
  ** each one to the list of all columns in all tables.
  **
  ** The first loop just checks to see if there are any "*" operators
  ** that need expanding.
  */
  for(k=0; k<pEList->nExpr; k++){
    Expr *pE = pEList->a[k].pExpr;
    if( pE->op==TK_ALL ) break;
    assert( pE->op!=TK_DOT || pE->pRight!=0 );
    assert( pE->op!=TK_DOT || (pE->pLeft!=0 && pE->pLeft->op==TK_ID) );
    if( pE->op==TK_DOT && pE->pRight->op==TK_ALL ) break;
  }
  if( k<pEList->nExpr ){
    /*
    ** If we get here it means the result set contains one or more "*"
    ** operators that need to be expanded.  Loop through each expression
    ** in the result set and expand them one by one.
    */
    struct ExprList_item *a = pEList->a;
    ExprList *pNew = 0;
    int flags = pParse->db->flags;
    int longNames = (flags & SQLITE_FullColNames)!=0
                      && (flags & SQLITE_ShortColNames)==0;

    for(k=0; k<pEList->nExpr; k++){
      Expr *pE = a[k].pExpr;
      assert( pE->op!=TK_DOT || pE->pRight!=0 );
      if( pE->op!=TK_ALL && (pE->op!=TK_DOT || pE->pRight->op!=TK_ALL) ){
        /* This particular expression does not need to be expanded.
        */
        pNew = sqlite3ExprListAppend(pParse, pNew, a[k].pExpr);
        if( pNew ){
          pNew->a[pNew->nExpr-1].zName = a[k].zName;
          pNew->a[pNew->nExpr-1].zSpan = a[k].zSpan;
          a[k].zName = 0;
          a[k].zSpan = 0;
        }
        a[k].pExpr = 0;
      }else{
        /* This expression is a "*" or a "TABLE.*" and needs to be
        ** expanded. */
        int tableSeen = 0;      /* Set to 1 when TABLE matches */
        char *zTName;            /* text of name of TABLE */
        if( pE->op==TK_DOT ){
          assert( pE->pLeft!=0 );
          assert( !ExprHasProperty(pE->pLeft, EP_IntValue) );
          zTName = pE->pLeft->u.zToken;
        }else{
          zTName = 0;
        }
        for(i=0, pFrom=pTabList->a; i<pTabList->nSrc; i++, pFrom++){
          Table *pTab = pFrom->pTab;
          char *zTabName = pFrom->zAlias;
          if( zTabName==0 ){
            zTabName = pTab->zName;
          }
          if( db->mallocFailed ) break;
          if( zTName && sqlite3StrICmp(zTName, zTabName)!=0 ){
            continue;
          }
          tableSeen = 1;
          for(j=0; j<pTab->nCol; j++){
            Expr *pExpr, *pRight;
            char *zName = pTab->aCol[j].zName;
            char *zColname;  /* The computed column name */
            char *zToFree;   /* Malloced string that needs to be freed */
            Token sColname;  /* Computed column name as a token */

            /* If a column is marked as 'hidden' (currently only possible
            ** for virtual tables), do not include it in the expanded
            ** result-set list.
            */
            if( IsHiddenColumn(&pTab->aCol[j]) ){
              assert(IsVirtual(pTab));
              continue;
            }

            if( i>0 && zTName==0 ){
              if( (pFrom->jointype & JT_NATURAL)!=0
                && tableAndColumnIndex(pTabList, i, zName, 0, 0)
              ){
                /* In a NATURAL join, omit the join columns from the 
                ** table to the right of the join */
                continue;
              }
              if( sqlite3IdListIndex(pFrom->pUsing, zName)>=0 ){
                /* In a join with a USING clause, omit columns in the
                ** using clause from the table on the right. */
                continue;
              }
            }
            pRight = sqlite3Expr(db, TK_ID, zName);
            zColname = zName;
            zToFree = 0;
            if( longNames || pTabList->nSrc>1 ){
              Expr *pLeft;
              pLeft = sqlite3Expr(db, TK_ID, zTabName);
              pExpr = sqlite3PExpr(pParse, TK_DOT, pLeft, pRight, 0);
              if( longNames ){
                zColname = sqlite3MPrintf(db, "%s.%s", zTabName, zName);
                zToFree = zColname;
              }
            }else{
              pExpr = pRight;
            }
            pNew = sqlite3ExprListAppend(pParse, pNew, pExpr);
            sColname.z = zColname;
            sColname.n = sqlite3Strlen30(zColname);
            sqlite3ExprListSetName(pParse, pNew, &sColname, 0);
            sqlite3DbFree(db, zToFree);
          }
        }
        if( !tableSeen ){
          if( zTName ){
            sqlite3ErrorMsg(pParse, "no such table: %s", zTName);
          }else{
            sqlite3ErrorMsg(pParse, "no tables specified");
          }
        }
      }
    }
    sqlite3ExprListDelete(db, pEList);
    p->pEList = pNew;
  }
#if SQLITE_MAX_COLUMN
  if( p->pEList && p->pEList->nExpr>db->aLimit[SQLITE_LIMIT_COLUMN] ){
    sqlite3ErrorMsg(pParse, "too many columns in result set");
  }
#endif
  return WRC_Continue;
}