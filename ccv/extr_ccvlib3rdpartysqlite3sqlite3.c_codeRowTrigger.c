#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
struct TYPE_33__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  int /*<<< orphan*/  sNC ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_34__ {int orconf; int* aColmask; TYPE_3__* pTrigger; TYPE_5__* pProgram; struct TYPE_34__* pNext; } ;
typedef  TYPE_2__ TriggerPrg ;
struct TYPE_35__ {scalar_t__ op; scalar_t__ tr_tm; int /*<<< orphan*/  zName; int /*<<< orphan*/  step_list; int /*<<< orphan*/  pWhen; } ;
typedef  TYPE_3__ Trigger ;
struct TYPE_36__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_4__ Table ;
struct TYPE_39__ {TYPE_6__* pParse; } ;
struct TYPE_38__ {int pVdbe; scalar_t__ eTriggerOp; scalar_t__ nErr; int oldmask; int newmask; int /*<<< orphan*/  nMaxArg; TYPE_2__* pTriggerPrg; int /*<<< orphan*/  pZombieTab; int /*<<< orphan*/  pAinc; int /*<<< orphan*/  nTab; int /*<<< orphan*/  nMem; int /*<<< orphan*/  nQueryLoop; int /*<<< orphan*/  zAuthContext; struct TYPE_38__* pToplevel; TYPE_4__* pTriggerTab; TYPE_1__* db; } ;
struct TYPE_37__ {void* token; int /*<<< orphan*/  nCsr; int /*<<< orphan*/  nMem; int /*<<< orphan*/  nOp; int /*<<< orphan*/  aOp; } ;
typedef  TYPE_5__ SubProgram ;
typedef  TYPE_6__ Parse ;
typedef  TYPE_7__ NameContext ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Halt ; 
 int /*<<< orphan*/  P4_DYNAMIC ; 
 int /*<<< orphan*/  SQLITE_JUMPIFNULL ; 
 scalar_t__ SQLITE_OK ; 
 scalar_t__ TK_DELETE ; 
 scalar_t__ TK_INSERT ; 
 scalar_t__ TK_UPDATE ; 
 scalar_t__ TRIGGER_BEFORE ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  codeTriggerProgram (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  onErrorText (int) ; 
 void* sqlite3DbMallocZero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3ExprDup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprIfFalse (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3MPrintf (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_6__* sqlite3ParseToplevel (TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3ParserReset (TYPE_6__*) ; 
 scalar_t__ sqlite3ResolveExprNames (TYPE_7__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* sqlite3StackAllocZero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqlite3StackFree (TYPE_1__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeLinkSubProgram (int,TYPE_5__*) ; 
 int sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeTakeOpArray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* tableOfTrigger (TYPE_3__*) ; 
 int /*<<< orphan*/  transferParseError (TYPE_6__*,TYPE_6__*) ; 

__attribute__((used)) static TriggerPrg *codeRowTrigger(
  Parse *pParse,       /* Current parse context */
  Trigger *pTrigger,   /* Trigger to code */
  Table *pTab,         /* The table pTrigger is attached to */
  int orconf           /* ON CONFLICT policy to code trigger program with */
){
  Parse *pTop = sqlite3ParseToplevel(pParse);
  sqlite3 *db = pParse->db;   /* Database handle */
  TriggerPrg *pPrg;           /* Value to return */
  Expr *pWhen = 0;            /* Duplicate of trigger WHEN expression */
  Vdbe *v;                    /* Temporary VM */
  NameContext sNC;            /* Name context for sub-vdbe */
  SubProgram *pProgram = 0;   /* Sub-vdbe for trigger program */
  Parse *pSubParse;           /* Parse context for sub-vdbe */
  int iEndTrigger = 0;        /* Label to jump to if WHEN is false */

  assert( pTrigger->zName==0 || pTab==tableOfTrigger(pTrigger) );
  assert( pTop->pVdbe );

  /* Allocate the TriggerPrg and SubProgram objects. To ensure that they
  ** are freed if an error occurs, link them into the Parse.pTriggerPrg 
  ** list of the top-level Parse object sooner rather than later.  */
  pPrg = sqlite3DbMallocZero(db, sizeof(TriggerPrg));
  if( !pPrg ) return 0;
  pPrg->pNext = pTop->pTriggerPrg;
  pTop->pTriggerPrg = pPrg;
  pPrg->pProgram = pProgram = sqlite3DbMallocZero(db, sizeof(SubProgram));
  if( !pProgram ) return 0;
  sqlite3VdbeLinkSubProgram(pTop->pVdbe, pProgram);
  pPrg->pTrigger = pTrigger;
  pPrg->orconf = orconf;
  pPrg->aColmask[0] = 0xffffffff;
  pPrg->aColmask[1] = 0xffffffff;

  /* Allocate and populate a new Parse context to use for coding the 
  ** trigger sub-program.  */
  pSubParse = sqlite3StackAllocZero(db, sizeof(Parse));
  if( !pSubParse ) return 0;
  memset(&sNC, 0, sizeof(sNC));
  sNC.pParse = pSubParse;
  pSubParse->db = db;
  pSubParse->pTriggerTab = pTab;
  pSubParse->pToplevel = pTop;
  pSubParse->zAuthContext = pTrigger->zName;
  pSubParse->eTriggerOp = pTrigger->op;
  pSubParse->nQueryLoop = pParse->nQueryLoop;

  v = sqlite3GetVdbe(pSubParse);
  if( v ){
    VdbeComment((v, "Start: %s.%s (%s %s%s%s ON %s)", 
      pTrigger->zName, onErrorText(orconf),
      (pTrigger->tr_tm==TRIGGER_BEFORE ? "BEFORE" : "AFTER"),
        (pTrigger->op==TK_UPDATE ? "UPDATE" : ""),
        (pTrigger->op==TK_INSERT ? "INSERT" : ""),
        (pTrigger->op==TK_DELETE ? "DELETE" : ""),
      pTab->zName
    ));
#ifndef SQLITE_OMIT_TRACE
    if( pTrigger->zName ){
      sqlite3VdbeChangeP4(v, -1, 
        sqlite3MPrintf(db, "-- TRIGGER %s", pTrigger->zName), P4_DYNAMIC
      );
    }
#endif

    /* If one was specified, code the WHEN clause. If it evaluates to false
    ** (or NULL) the sub-vdbe is immediately halted by jumping to the 
    ** OP_Halt inserted at the end of the program.  */
    if( pTrigger->pWhen ){
      pWhen = sqlite3ExprDup(db, pTrigger->pWhen, 0);
      if( SQLITE_OK==sqlite3ResolveExprNames(&sNC, pWhen) 
       && db->mallocFailed==0 
      ){
        iEndTrigger = sqlite3VdbeMakeLabel(v);
        sqlite3ExprIfFalse(pSubParse, pWhen, iEndTrigger, SQLITE_JUMPIFNULL);
      }
      sqlite3ExprDelete(db, pWhen);
    }

    /* Code the trigger program into the sub-vdbe. */
    codeTriggerProgram(pSubParse, pTrigger->step_list, orconf);

    /* Insert an OP_Halt at the end of the sub-program. */
    if( iEndTrigger ){
      sqlite3VdbeResolveLabel(v, iEndTrigger);
    }
    sqlite3VdbeAddOp0(v, OP_Halt);
    VdbeComment((v, "End: %s.%s", pTrigger->zName, onErrorText(orconf)));

    transferParseError(pParse, pSubParse);
    if( db->mallocFailed==0 && pParse->nErr==0 ){
      pProgram->aOp = sqlite3VdbeTakeOpArray(v, &pProgram->nOp, &pTop->nMaxArg);
    }
    pProgram->nMem = pSubParse->nMem;
    pProgram->nCsr = pSubParse->nTab;
    pProgram->token = (void *)pTrigger;
    pPrg->aColmask[0] = pSubParse->oldmask;
    pPrg->aColmask[1] = pSubParse->newmask;
    sqlite3VdbeDelete(v);
  }

  assert( !pSubParse->pAinc       && !pSubParse->pZombieTab );
  assert( !pSubParse->pTriggerPrg && !pSubParse->nMaxArg );
  sqlite3ParserReset(pSubParse);
  sqlite3StackFree(db, pSubParse);

  return pPrg;
}