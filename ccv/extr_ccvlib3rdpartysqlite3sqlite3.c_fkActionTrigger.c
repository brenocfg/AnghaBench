#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_70__   TYPE_9__ ;
typedef  struct TYPE_69__   TYPE_8__ ;
typedef  struct TYPE_68__   TYPE_7__ ;
typedef  struct TYPE_67__   TYPE_6__ ;
typedef  struct TYPE_66__   TYPE_5__ ;
typedef  struct TYPE_65__   TYPE_4__ ;
typedef  struct TYPE_64__   TYPE_3__ ;
typedef  struct TYPE_63__   TYPE_2__ ;
typedef  struct TYPE_62__   TYPE_1__ ;
typedef  struct TYPE_61__   TYPE_14__ ;
typedef  struct TYPE_60__   TYPE_13__ ;
typedef  struct TYPE_59__   TYPE_12__ ;
typedef  struct TYPE_58__   TYPE_11__ ;
typedef  struct TYPE_57__   TYPE_10__ ;

/* Type definitions */
struct TYPE_62__ {int /*<<< orphan*/  bDisable; } ;
struct TYPE_67__ {int flags; int mallocFailed; TYPE_1__ lookaside; } ;
typedef  TYPE_6__ sqlite3 ;
struct TYPE_68__ {char* zTarget; TYPE_8__* pTrig; void* op; int /*<<< orphan*/  pSelect; int /*<<< orphan*/  pExprList; void* pWhere; } ;
typedef  TYPE_7__ TriggerStep ;
struct TYPE_69__ {void* op; int /*<<< orphan*/  pTabSchema; int /*<<< orphan*/  pSchema; void* pWhen; TYPE_7__* step_list; } ;
typedef  TYPE_8__ Trigger ;
struct TYPE_70__ {char* member_0; int member_1; char const* z; int n; } ;
typedef  TYPE_9__ Token ;
struct TYPE_57__ {size_t iPKey; size_t nCol; int /*<<< orphan*/  pSchema; TYPE_3__* aCol; } ;
typedef  TYPE_10__ Table ;
struct TYPE_66__ {char* zName; TYPE_4__* aCol; } ;
struct TYPE_65__ {TYPE_14__* pDflt; int /*<<< orphan*/  zName; } ;
struct TYPE_64__ {int /*<<< orphan*/  zName; } ;
struct TYPE_63__ {int iFrom; } ;
struct TYPE_61__ {int /*<<< orphan*/  affinity; } ;
struct TYPE_60__ {int* aAction; int nCol; TYPE_8__** apTrigger; TYPE_5__* pFrom; TYPE_2__* aCol; } ;
struct TYPE_59__ {size_t* aiColumn; } ;
struct TYPE_58__ {TYPE_6__* db; } ;
typedef  int /*<<< orphan*/  Select ;
typedef  TYPE_11__ Parse ;
typedef  TYPE_12__ Index ;
typedef  TYPE_13__ FKey ;
typedef  int /*<<< orphan*/  ExprList ;
typedef  TYPE_14__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPRDUP_REDUCE ; 
 int /*<<< orphan*/  OE_Abort ; 
#define  OE_Cascade 129 
 int OE_None ; 
#define  OE_Restrict 128 
 int OE_SetDflt ; 
 int SQLITE_DeferFKs ; 
 void* TK_DELETE ; 
 int /*<<< orphan*/  TK_DOT ; 
 int /*<<< orphan*/  TK_EQ ; 
 int /*<<< orphan*/  TK_ID ; 
 int /*<<< orphan*/  TK_IS ; 
 int /*<<< orphan*/  TK_NOT ; 
 int /*<<< orphan*/  TK_NULL ; 
 int /*<<< orphan*/  TK_RAISE ; 
 void* TK_SELECT ; 
 void* TK_UPDATE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fkTriggerDelete (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_6__*,int*) ; 
 scalar_t__ sqlite3DbMallocZero (TYPE_6__*,int) ; 
 TYPE_14__* sqlite3Expr (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_14__* sqlite3ExprAlloc (TYPE_6__*,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 
 TYPE_14__* sqlite3ExprAnd (TYPE_6__*,TYPE_14__*,TYPE_14__*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_6__*,TYPE_14__*) ; 
 void* sqlite3ExprDup (TYPE_6__*,TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3ExprListAppend (TYPE_11__*,int /*<<< orphan*/ *,TYPE_14__*) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ExprListDup (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListSetName (TYPE_11__*,int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3FkLocateIndex (TYPE_11__*,TYPE_10__*,TYPE_13__*,TYPE_12__**,int**) ; 
 TYPE_14__* sqlite3PExpr (TYPE_11__*,int /*<<< orphan*/ ,TYPE_14__*,TYPE_14__*) ; 
 int /*<<< orphan*/  sqlite3SelectDelete (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3SelectDup (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3SelectNew (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListAppend (TYPE_6__*,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int sqlite3Strlen30 (char const*) ; 
 int /*<<< orphan*/  sqlite3TokenInit (TYPE_9__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Trigger *fkActionTrigger(
  Parse *pParse,                  /* Parse context */
  Table *pTab,                    /* Table being updated or deleted from */
  FKey *pFKey,                    /* Foreign key to get action for */
  ExprList *pChanges              /* Change-list for UPDATE, NULL for DELETE */
){
  sqlite3 *db = pParse->db;       /* Database handle */
  int action;                     /* One of OE_None, OE_Cascade etc. */
  Trigger *pTrigger;              /* Trigger definition to return */
  int iAction = (pChanges!=0);    /* 1 for UPDATE, 0 for DELETE */

  action = pFKey->aAction[iAction];
  if( action==OE_Restrict && (db->flags & SQLITE_DeferFKs) ){
    return 0;
  }
  pTrigger = pFKey->apTrigger[iAction];

  if( action!=OE_None && !pTrigger ){
    char const *zFrom;            /* Name of child table */
    int nFrom;                    /* Length in bytes of zFrom */
    Index *pIdx = 0;              /* Parent key index for this FK */
    int *aiCol = 0;               /* child table cols -> parent key cols */
    TriggerStep *pStep = 0;        /* First (only) step of trigger program */
    Expr *pWhere = 0;             /* WHERE clause of trigger step */
    ExprList *pList = 0;          /* Changes list if ON UPDATE CASCADE */
    Select *pSelect = 0;          /* If RESTRICT, "SELECT RAISE(...)" */
    int i;                        /* Iterator variable */
    Expr *pWhen = 0;              /* WHEN clause for the trigger */

    if( sqlite3FkLocateIndex(pParse, pTab, pFKey, &pIdx, &aiCol) ) return 0;
    assert( aiCol || pFKey->nCol==1 );

    for(i=0; i<pFKey->nCol; i++){
      Token tOld = { "old", 3 };  /* Literal "old" token */
      Token tNew = { "new", 3 };  /* Literal "new" token */
      Token tFromCol;             /* Name of column in child table */
      Token tToCol;               /* Name of column in parent table */
      int iFromCol;               /* Idx of column in child table */
      Expr *pEq;                  /* tFromCol = OLD.tToCol */

      iFromCol = aiCol ? aiCol[i] : pFKey->aCol[0].iFrom;
      assert( iFromCol>=0 );
      assert( pIdx!=0 || (pTab->iPKey>=0 && pTab->iPKey<pTab->nCol) );
      assert( pIdx==0 || pIdx->aiColumn[i]>=0 );
      sqlite3TokenInit(&tToCol,
                   pTab->aCol[pIdx ? pIdx->aiColumn[i] : pTab->iPKey].zName);
      sqlite3TokenInit(&tFromCol, pFKey->pFrom->aCol[iFromCol].zName);

      /* Create the expression "OLD.zToCol = zFromCol". It is important
      ** that the "OLD.zToCol" term is on the LHS of the = operator, so
      ** that the affinity and collation sequence associated with the
      ** parent table are used for the comparison. */
      pEq = sqlite3PExpr(pParse, TK_EQ,
          sqlite3PExpr(pParse, TK_DOT, 
            sqlite3ExprAlloc(db, TK_ID, &tOld, 0),
            sqlite3ExprAlloc(db, TK_ID, &tToCol, 0)),
          sqlite3ExprAlloc(db, TK_ID, &tFromCol, 0)
      );
      pWhere = sqlite3ExprAnd(db, pWhere, pEq);

      /* For ON UPDATE, construct the next term of the WHEN clause.
      ** The final WHEN clause will be like this:
      **
      **    WHEN NOT(old.col1 IS new.col1 AND ... AND old.colN IS new.colN)
      */
      if( pChanges ){
        pEq = sqlite3PExpr(pParse, TK_IS,
            sqlite3PExpr(pParse, TK_DOT, 
              sqlite3ExprAlloc(db, TK_ID, &tOld, 0),
              sqlite3ExprAlloc(db, TK_ID, &tToCol, 0)),
            sqlite3PExpr(pParse, TK_DOT, 
              sqlite3ExprAlloc(db, TK_ID, &tNew, 0),
              sqlite3ExprAlloc(db, TK_ID, &tToCol, 0))
            );
        pWhen = sqlite3ExprAnd(db, pWhen, pEq);
      }
  
      if( action!=OE_Restrict && (action!=OE_Cascade || pChanges) ){
        Expr *pNew;
        if( action==OE_Cascade ){
          pNew = sqlite3PExpr(pParse, TK_DOT, 
            sqlite3ExprAlloc(db, TK_ID, &tNew, 0),
            sqlite3ExprAlloc(db, TK_ID, &tToCol, 0));
        }else if( action==OE_SetDflt ){
          Expr *pDflt = pFKey->pFrom->aCol[iFromCol].pDflt;
          if( pDflt ){
            pNew = sqlite3ExprDup(db, pDflt, 0);
          }else{
            pNew = sqlite3ExprAlloc(db, TK_NULL, 0, 0);
          }
        }else{
          pNew = sqlite3ExprAlloc(db, TK_NULL, 0, 0);
        }
        pList = sqlite3ExprListAppend(pParse, pList, pNew);
        sqlite3ExprListSetName(pParse, pList, &tFromCol, 0);
      }
    }
    sqlite3DbFree(db, aiCol);

    zFrom = pFKey->pFrom->zName;
    nFrom = sqlite3Strlen30(zFrom);

    if( action==OE_Restrict ){
      Token tFrom;
      Expr *pRaise; 

      tFrom.z = zFrom;
      tFrom.n = nFrom;
      pRaise = sqlite3Expr(db, TK_RAISE, "FOREIGN KEY constraint failed");
      if( pRaise ){
        pRaise->affinity = OE_Abort;
      }
      pSelect = sqlite3SelectNew(pParse, 
          sqlite3ExprListAppend(pParse, 0, pRaise),
          sqlite3SrcListAppend(db, 0, &tFrom, 0),
          pWhere,
          0, 0, 0, 0, 0
      );
      pWhere = 0;
    }

    /* Disable lookaside memory allocation */
    db->lookaside.bDisable++;

    pTrigger = (Trigger *)sqlite3DbMallocZero(db, 
        sizeof(Trigger) +         /* struct Trigger */
        sizeof(TriggerStep) +     /* Single step in trigger program */
        nFrom + 1                 /* Space for pStep->zTarget */
    );
    if( pTrigger ){
      pStep = pTrigger->step_list = (TriggerStep *)&pTrigger[1];
      pStep->zTarget = (char *)&pStep[1];
      memcpy((char *)pStep->zTarget, zFrom, nFrom);
  
      pStep->pWhere = sqlite3ExprDup(db, pWhere, EXPRDUP_REDUCE);
      pStep->pExprList = sqlite3ExprListDup(db, pList, EXPRDUP_REDUCE);
      pStep->pSelect = sqlite3SelectDup(db, pSelect, EXPRDUP_REDUCE);
      if( pWhen ){
        pWhen = sqlite3PExpr(pParse, TK_NOT, pWhen, 0);
        pTrigger->pWhen = sqlite3ExprDup(db, pWhen, EXPRDUP_REDUCE);
      }
    }

    /* Re-enable the lookaside buffer, if it was disabled earlier. */
    db->lookaside.bDisable--;

    sqlite3ExprDelete(db, pWhere);
    sqlite3ExprDelete(db, pWhen);
    sqlite3ExprListDelete(db, pList);
    sqlite3SelectDelete(db, pSelect);
    if( db->mallocFailed==1 ){
      fkTriggerDelete(db, pTrigger);
      return 0;
    }
    assert( pStep!=0 );

    switch( action ){
      case OE_Restrict:
        pStep->op = TK_SELECT; 
        break;
      case OE_Cascade: 
        if( !pChanges ){ 
          pStep->op = TK_DELETE; 
          break; 
        }
      default:
        pStep->op = TK_UPDATE;
    }
    pStep->pTrig = pTrigger;
    pTrigger->pSchema = pTab->pSchema;
    pTrigger->pTabSchema = pTab->pSchema;
    pFKey->apTrigger[iAction] = pTrigger;
    pTrigger->op = (pChanges ? TK_UPDATE : TK_DELETE);
  }

  return pTrigger;
}