#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_69__   TYPE_9__ ;
typedef  struct TYPE_68__   TYPE_8__ ;
typedef  struct TYPE_67__   TYPE_7__ ;
typedef  struct TYPE_66__   TYPE_6__ ;
typedef  struct TYPE_65__   TYPE_5__ ;
typedef  struct TYPE_64__   TYPE_4__ ;
typedef  struct TYPE_63__   TYPE_3__ ;
typedef  struct TYPE_62__   TYPE_2__ ;
typedef  struct TYPE_61__   TYPE_1__ ;
typedef  struct TYPE_60__   TYPE_15__ ;
typedef  struct TYPE_59__   TYPE_14__ ;
typedef  struct TYPE_58__   TYPE_13__ ;
typedef  struct TYPE_57__   TYPE_12__ ;
typedef  struct TYPE_56__   TYPE_11__ ;
typedef  struct TYPE_55__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_62__ {int /*<<< orphan*/  bEnabled; } ;
struct TYPE_67__ {int mallocFailed; TYPE_2__ lookaside; } ;
typedef  TYPE_7__ sqlite3 ;
struct TYPE_61__ {char* z; int n; } ;
struct TYPE_68__ {TYPE_9__* pTrig; void* op; int /*<<< orphan*/  pSelect; int /*<<< orphan*/  pExprList; void* pWhere; TYPE_1__ target; } ;
typedef  TYPE_8__ TriggerStep ;
struct TYPE_69__ {void* op; int /*<<< orphan*/  pTabSchema; int /*<<< orphan*/  pSchema; void* pWhen; TYPE_8__* step_list; } ;
typedef  TYPE_9__ Trigger ;
struct TYPE_55__ {char* member_0; int member_1; char* z; int n; } ;
typedef  TYPE_10__ Token ;
struct TYPE_56__ {int /*<<< orphan*/  pSchema; TYPE_4__* aCol; } ;
typedef  TYPE_11__ Table ;
struct TYPE_66__ {char* zName; TYPE_5__* aCol; } ;
struct TYPE_65__ {char* zName; TYPE_15__* pDflt; } ;
struct TYPE_64__ {char* zName; } ;
struct TYPE_63__ {int iFrom; } ;
struct TYPE_60__ {int /*<<< orphan*/  affinity; } ;
struct TYPE_59__ {int* aAction; int nCol; TYPE_9__** apTrigger; TYPE_6__* pFrom; TYPE_3__* aCol; } ;
struct TYPE_58__ {size_t* aiColumn; } ;
struct TYPE_57__ {TYPE_7__* db; } ;
typedef  int /*<<< orphan*/  Select ;
typedef  TYPE_12__ Parse ;
typedef  TYPE_13__ Index ;
typedef  TYPE_14__ FKey ;
typedef  int /*<<< orphan*/  ExprList ;
typedef  TYPE_15__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPRDUP_REDUCE ; 
 int /*<<< orphan*/  OE_Abort ; 
#define  OE_Cascade 129 
 int OE_None ; 
#define  OE_Restrict 128 
 int OE_SetDflt ; 
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
 int /*<<< orphan*/  fkTriggerDelete (TYPE_7__*,TYPE_9__*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_7__*,int*) ; 
 scalar_t__ sqlite3DbMallocZero (TYPE_7__*,int) ; 
 TYPE_15__* sqlite3Expr (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_15__* sqlite3ExprAnd (TYPE_7__*,TYPE_15__*,TYPE_15__*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_7__*,TYPE_15__*) ; 
 void* sqlite3ExprDup (TYPE_7__*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3ExprListAppend (TYPE_12__*,int /*<<< orphan*/ *,TYPE_15__*) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ExprListDup (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListSetName (TYPE_12__*,int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3FkLocateIndex (TYPE_12__*,TYPE_11__*,TYPE_14__*,TYPE_13__**,int**) ; 
 TYPE_15__* sqlite3PExpr (TYPE_12__*,int /*<<< orphan*/ ,TYPE_15__*,TYPE_15__*,TYPE_10__*) ; 
 int /*<<< orphan*/  sqlite3SelectDelete (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3SelectDup (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3SelectNew (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListAppend (TYPE_7__*,int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ) ; 
 void* sqlite3Strlen30 (char const*) ; 

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
  pTrigger = pFKey->apTrigger[iAction];

  if( action!=OE_None && !pTrigger ){
    u8 enableLookaside;           /* Copy of db->lookaside.bEnabled */
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
      tToCol.z = pIdx ? pTab->aCol[pIdx->aiColumn[i]].zName : "oid";
      tFromCol.z = pFKey->pFrom->aCol[iFromCol].zName;

      tToCol.n = sqlite3Strlen30(tToCol.z);
      tFromCol.n = sqlite3Strlen30(tFromCol.z);

      /* Create the expression "OLD.zToCol = zFromCol". It is important
      ** that the "OLD.zToCol" term is on the LHS of the = operator, so
      ** that the affinity and collation sequence associated with the
      ** parent table are used for the comparison. */
      pEq = sqlite3PExpr(pParse, TK_EQ,
          sqlite3PExpr(pParse, TK_DOT, 
            sqlite3PExpr(pParse, TK_ID, 0, 0, &tOld),
            sqlite3PExpr(pParse, TK_ID, 0, 0, &tToCol)
          , 0),
          sqlite3PExpr(pParse, TK_ID, 0, 0, &tFromCol)
      , 0);
      pWhere = sqlite3ExprAnd(db, pWhere, pEq);

      /* For ON UPDATE, construct the next term of the WHEN clause.
      ** The final WHEN clause will be like this:
      **
      **    WHEN NOT(old.col1 IS new.col1 AND ... AND old.colN IS new.colN)
      */
      if( pChanges ){
        pEq = sqlite3PExpr(pParse, TK_IS,
            sqlite3PExpr(pParse, TK_DOT, 
              sqlite3PExpr(pParse, TK_ID, 0, 0, &tOld),
              sqlite3PExpr(pParse, TK_ID, 0, 0, &tToCol),
              0),
            sqlite3PExpr(pParse, TK_DOT, 
              sqlite3PExpr(pParse, TK_ID, 0, 0, &tNew),
              sqlite3PExpr(pParse, TK_ID, 0, 0, &tToCol),
              0),
            0);
        pWhen = sqlite3ExprAnd(db, pWhen, pEq);
      }
  
      if( action!=OE_Restrict && (action!=OE_Cascade || pChanges) ){
        Expr *pNew;
        if( action==OE_Cascade ){
          pNew = sqlite3PExpr(pParse, TK_DOT, 
            sqlite3PExpr(pParse, TK_ID, 0, 0, &tNew),
            sqlite3PExpr(pParse, TK_ID, 0, 0, &tToCol)
          , 0);
        }else if( action==OE_SetDflt ){
          Expr *pDflt = pFKey->pFrom->aCol[iFromCol].pDflt;
          if( pDflt ){
            pNew = sqlite3ExprDup(db, pDflt, 0);
          }else{
            pNew = sqlite3PExpr(pParse, TK_NULL, 0, 0, 0);
          }
        }else{
          pNew = sqlite3PExpr(pParse, TK_NULL, 0, 0, 0);
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
      pRaise = sqlite3Expr(db, TK_RAISE, "foreign key constraint failed");
      if( pRaise ){
        pRaise->affinity = OE_Abort;
      }
      pSelect = sqlite3SelectNew(pParse, 
          sqlite3ExprListAppend(pParse, 0, pRaise),
          sqlite3SrcListAppend(db, 0, &tFrom, 0),
          pWhere,
          0, 0, 0, 0, 0, 0
      );
      pWhere = 0;
    }

    /* Disable lookaside memory allocation */
    enableLookaside = db->lookaside.bEnabled;
    db->lookaside.bEnabled = 0;

    pTrigger = (Trigger *)sqlite3DbMallocZero(db, 
        sizeof(Trigger) +         /* struct Trigger */
        sizeof(TriggerStep) +     /* Single step in trigger program */
        nFrom + 1                 /* Space for pStep->target.z */
    );
    if( pTrigger ){
      pStep = pTrigger->step_list = (TriggerStep *)&pTrigger[1];
      pStep->target.z = (char *)&pStep[1];
      pStep->target.n = nFrom;
      memcpy((char *)pStep->target.z, zFrom, nFrom);
  
      pStep->pWhere = sqlite3ExprDup(db, pWhere, EXPRDUP_REDUCE);
      pStep->pExprList = sqlite3ExprListDup(db, pList, EXPRDUP_REDUCE);
      pStep->pSelect = sqlite3SelectDup(db, pSelect, EXPRDUP_REDUCE);
      if( pWhen ){
        pWhen = sqlite3PExpr(pParse, TK_NOT, pWhen, 0, 0);
        pTrigger->pWhen = sqlite3ExprDup(db, pWhen, EXPRDUP_REDUCE);
      }
    }

    /* Re-enable the lookaside buffer, if it was disabled earlier. */
    db->lookaside.bEnabled = enableLookaside;

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