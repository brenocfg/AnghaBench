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
struct TYPE_21__ {TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_22__ {int tnum; char* zName; TYPE_5__* pIndex; int /*<<< orphan*/  pSchema; } ;
typedef  TYPE_3__ Table ;
struct TYPE_24__ {char* zName; int nColumn; int tnum; scalar_t__* azColl; int /*<<< orphan*/  pSchema; struct TYPE_24__* pNext; } ;
struct TYPE_23__ {int nMem; int /*<<< orphan*/  nTab; TYPE_2__* db; } ;
struct TYPE_20__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_4__ Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;
typedef  TYPE_5__ Index ;
typedef  int /*<<< orphan*/  CollSeq ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  OPFLAG_APPEND ; 
 int /*<<< orphan*/  OP_Add ; 
 int /*<<< orphan*/  OP_AddImm ; 
 int /*<<< orphan*/  OP_Close ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_Concat ; 
 int /*<<< orphan*/  OP_Count ; 
 int /*<<< orphan*/  OP_Divide ; 
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_IfNot ; 
 int /*<<< orphan*/  OP_Insert ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_Ne ; 
 int /*<<< orphan*/  OP_NewRowid ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_Null ; 
 int /*<<< orphan*/  OP_OpenRead ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  OP_SCopy ; 
 int /*<<< orphan*/  OP_String8 ; 
 int /*<<< orphan*/  OP_ToInt ; 
 int /*<<< orphan*/  P4_COLLSEQ ; 
 int /*<<< orphan*/  P4_KEYINFO_HANDOFF ; 
 int /*<<< orphan*/  SQLITE_ANALYZE ; 
 int /*<<< orphan*/  SQLITE_NULLEQ ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeNoopComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3AuthCheck (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3BtreeHoldsAllMutexes (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_2__*,int*) ; 
 int* sqlite3DbMallocRaw (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_4__*) ; 
 int /*<<< orphan*/ * sqlite3IndexKeyinfo (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * sqlite3LocateCollSeq (TYPE_4__*,scalar_t__) ; 
 int sqlite3SchemaMutexHeld (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int sqlite3SchemaToIndex (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3TableLock (TYPE_4__*,int,int,int /*<<< orphan*/ ,char*) ; 
 int sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_strnicmp (char*,char*,int) ; 

__attribute__((used)) static void analyzeOneTable(
  Parse *pParse,   /* Parser context */
  Table *pTab,     /* Table whose indices are to be analyzed */
  Index *pOnlyIdx, /* If not NULL, only analyze this one index */
  int iStatCur,    /* Index of VdbeCursor that writes the sqlite_stat1 table */
  int iMem         /* Available memory locations begin here */
){
  sqlite3 *db = pParse->db;    /* Database handle */
  Index *pIdx;                 /* An index to being analyzed */
  int iIdxCur;                 /* Cursor open on index being analyzed */
  Vdbe *v;                     /* The virtual machine being built up */
  int i;                       /* Loop counter */
  int topOfLoop;               /* The top of the loop */
  int endOfLoop;               /* The end of the loop */
  int jZeroRows = -1;          /* Jump from here if number of rows is zero */
  int iDb;                     /* Index of database containing pTab */
  int regTabname = iMem++;     /* Register containing table name */
  int regIdxname = iMem++;     /* Register containing index name */
  int regStat1 = iMem++;       /* The stat column of sqlite_stat1 */
#ifdef SQLITE_ENABLE_STAT3
  int regNumEq = regStat1;     /* Number of instances.  Same as regStat1 */
  int regNumLt = iMem++;       /* Number of keys less than regSample */
  int regNumDLt = iMem++;      /* Number of distinct keys less than regSample */
  int regSample = iMem++;      /* The next sample value */
  int regRowid = regSample;    /* Rowid of a sample */
  int regAccum = iMem++;       /* Register to hold Stat3Accum object */
  int regLoop = iMem++;        /* Loop counter */
  int regCount = iMem++;       /* Number of rows in the table or index */
  int regTemp1 = iMem++;       /* Intermediate register */
  int regTemp2 = iMem++;       /* Intermediate register */
  int once = 1;                /* One-time initialization */
  int shortJump = 0;           /* Instruction address */
  int iTabCur = pParse->nTab++; /* Table cursor */
#endif
  int regCol = iMem++;         /* Content of a column in analyzed table */
  int regRec = iMem++;         /* Register holding completed record */
  int regTemp = iMem++;        /* Temporary use register */
  int regNewRowid = iMem++;    /* Rowid for the inserted record */


  v = sqlite3GetVdbe(pParse);
  if( v==0 || NEVER(pTab==0) ){
    return;
  }
  if( pTab->tnum==0 ){
    /* Do not gather statistics on views or virtual tables */
    return;
  }
  if( sqlite3_strnicmp(pTab->zName, "sqlite_", 7)==0 ){
    /* Do not gather statistics on system tables */
    return;
  }
  assert( sqlite3BtreeHoldsAllMutexes(db) );
  iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
  assert( iDb>=0 );
  assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
#ifndef SQLITE_OMIT_AUTHORIZATION
  if( sqlite3AuthCheck(pParse, SQLITE_ANALYZE, pTab->zName, 0,
      db->aDb[iDb].zName ) ){
    return;
  }
#endif

  /* Establish a read-lock on the table at the shared-cache level. */
  sqlite3TableLock(pParse, iDb, pTab->tnum, 0, pTab->zName);

  iIdxCur = pParse->nTab++;
  sqlite3VdbeAddOp4(v, OP_String8, 0, regTabname, 0, pTab->zName, 0);
  for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
    int nCol;
    KeyInfo *pKey;
    int addrIfNot = 0;           /* address of OP_IfNot */
    int *aChngAddr;              /* Array of jump instruction addresses */

    if( pOnlyIdx && pOnlyIdx!=pIdx ) continue;
    VdbeNoopComment((v, "Begin analysis of %s", pIdx->zName));
    nCol = pIdx->nColumn;
    aChngAddr = sqlite3DbMallocRaw(db, sizeof(int)*nCol);
    if( aChngAddr==0 ) continue;
    pKey = sqlite3IndexKeyinfo(pParse, pIdx);
    if( iMem+1+(nCol*2)>pParse->nMem ){
      pParse->nMem = iMem+1+(nCol*2);
    }

    /* Open a cursor to the index to be analyzed. */
    assert( iDb==sqlite3SchemaToIndex(db, pIdx->pSchema) );
    sqlite3VdbeAddOp4(v, OP_OpenRead, iIdxCur, pIdx->tnum, iDb,
        (char *)pKey, P4_KEYINFO_HANDOFF);
    VdbeComment((v, "%s", pIdx->zName));

    /* Populate the register containing the index name. */
    sqlite3VdbeAddOp4(v, OP_String8, 0, regIdxname, 0, pIdx->zName, 0);

#ifdef SQLITE_ENABLE_STAT3
    if( once ){
      once = 0;
      sqlite3OpenTable(pParse, iTabCur, iDb, pTab, OP_OpenRead);
    }
    sqlite3VdbeAddOp2(v, OP_Count, iIdxCur, regCount);
    sqlite3VdbeAddOp2(v, OP_Integer, SQLITE_STAT3_SAMPLES, regTemp1);
    sqlite3VdbeAddOp2(v, OP_Integer, 0, regNumEq);
    sqlite3VdbeAddOp2(v, OP_Integer, 0, regNumLt);
    sqlite3VdbeAddOp2(v, OP_Integer, -1, regNumDLt);
    sqlite3VdbeAddOp3(v, OP_Null, 0, regSample, regAccum);
    sqlite3VdbeAddOp4(v, OP_Function, 1, regCount, regAccum,
                      (char*)&stat3InitFuncdef, P4_FUNCDEF);
    sqlite3VdbeChangeP5(v, 2);
#endif /* SQLITE_ENABLE_STAT3 */

    /* The block of memory cells initialized here is used as follows.
    **
    **    iMem:                
    **        The total number of rows in the table.
    **
    **    iMem+1 .. iMem+nCol: 
    **        Number of distinct entries in index considering the 
    **        left-most N columns only, where N is between 1 and nCol, 
    **        inclusive.
    **
    **    iMem+nCol+1 .. Mem+2*nCol:  
    **        Previous value of indexed columns, from left to right.
    **
    ** Cells iMem through iMem+nCol are initialized to 0. The others are 
    ** initialized to contain an SQL NULL.
    */
    for(i=0; i<=nCol; i++){
      sqlite3VdbeAddOp2(v, OP_Integer, 0, iMem+i);
    }
    for(i=0; i<nCol; i++){
      sqlite3VdbeAddOp2(v, OP_Null, 0, iMem+nCol+i+1);
    }

    /* Start the analysis loop. This loop runs through all the entries in
    ** the index b-tree.  */
    endOfLoop = sqlite3VdbeMakeLabel(v);
    sqlite3VdbeAddOp2(v, OP_Rewind, iIdxCur, endOfLoop);
    topOfLoop = sqlite3VdbeCurrentAddr(v);
    sqlite3VdbeAddOp2(v, OP_AddImm, iMem, 1);  /* Increment row counter */

    for(i=0; i<nCol; i++){
      CollSeq *pColl;
      sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, i, regCol);
      if( i==0 ){
        /* Always record the very first row */
        addrIfNot = sqlite3VdbeAddOp1(v, OP_IfNot, iMem+1);
      }
      assert( pIdx->azColl!=0 );
      assert( pIdx->azColl[i]!=0 );
      pColl = sqlite3LocateCollSeq(pParse, pIdx->azColl[i]);
      aChngAddr[i] = sqlite3VdbeAddOp4(v, OP_Ne, regCol, 0, iMem+nCol+i+1,
                                      (char*)pColl, P4_COLLSEQ);
      sqlite3VdbeChangeP5(v, SQLITE_NULLEQ);
      VdbeComment((v, "jump if column %d changed", i));
#ifdef SQLITE_ENABLE_STAT3
      if( i==0 ){
        sqlite3VdbeAddOp2(v, OP_AddImm, regNumEq, 1);
        VdbeComment((v, "incr repeat count"));
      }
#endif
    }
    sqlite3VdbeAddOp2(v, OP_Goto, 0, endOfLoop);
    for(i=0; i<nCol; i++){
      sqlite3VdbeJumpHere(v, aChngAddr[i]);  /* Set jump dest for the OP_Ne */
      if( i==0 ){
        sqlite3VdbeJumpHere(v, addrIfNot);   /* Jump dest for OP_IfNot */
#ifdef SQLITE_ENABLE_STAT3
        sqlite3VdbeAddOp4(v, OP_Function, 1, regNumEq, regTemp2,
                          (char*)&stat3PushFuncdef, P4_FUNCDEF);
        sqlite3VdbeChangeP5(v, 5);
        sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, pIdx->nColumn, regRowid);
        sqlite3VdbeAddOp3(v, OP_Add, regNumEq, regNumLt, regNumLt);
        sqlite3VdbeAddOp2(v, OP_AddImm, regNumDLt, 1);
        sqlite3VdbeAddOp2(v, OP_Integer, 1, regNumEq);
#endif        
      }
      sqlite3VdbeAddOp2(v, OP_AddImm, iMem+i+1, 1);
      sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, i, iMem+nCol+i+1);
    }
    sqlite3DbFree(db, aChngAddr);

    /* Always jump here after updating the iMem+1...iMem+1+nCol counters */
    sqlite3VdbeResolveLabel(v, endOfLoop);

    sqlite3VdbeAddOp2(v, OP_Next, iIdxCur, topOfLoop);
    sqlite3VdbeAddOp1(v, OP_Close, iIdxCur);
#ifdef SQLITE_ENABLE_STAT3
    sqlite3VdbeAddOp4(v, OP_Function, 1, regNumEq, regTemp2,
                      (char*)&stat3PushFuncdef, P4_FUNCDEF);
    sqlite3VdbeChangeP5(v, 5);
    sqlite3VdbeAddOp2(v, OP_Integer, -1, regLoop);
    shortJump = 
    sqlite3VdbeAddOp2(v, OP_AddImm, regLoop, 1);
    sqlite3VdbeAddOp4(v, OP_Function, 1, regAccum, regTemp1,
                      (char*)&stat3GetFuncdef, P4_FUNCDEF);
    sqlite3VdbeChangeP5(v, 2);
    sqlite3VdbeAddOp1(v, OP_IsNull, regTemp1);
    sqlite3VdbeAddOp3(v, OP_NotExists, iTabCur, shortJump, regTemp1);
    sqlite3VdbeAddOp3(v, OP_Column, iTabCur, pIdx->aiColumn[0], regSample);
    sqlite3ColumnDefault(v, pTab, pIdx->aiColumn[0], regSample);
    sqlite3VdbeAddOp4(v, OP_Function, 1, regAccum, regNumEq,
                      (char*)&stat3GetFuncdef, P4_FUNCDEF);
    sqlite3VdbeChangeP5(v, 3);
    sqlite3VdbeAddOp4(v, OP_Function, 1, regAccum, regNumLt,
                      (char*)&stat3GetFuncdef, P4_FUNCDEF);
    sqlite3VdbeChangeP5(v, 4);
    sqlite3VdbeAddOp4(v, OP_Function, 1, regAccum, regNumDLt,
                      (char*)&stat3GetFuncdef, P4_FUNCDEF);
    sqlite3VdbeChangeP5(v, 5);
    sqlite3VdbeAddOp4(v, OP_MakeRecord, regTabname, 6, regRec, "bbbbbb", 0);
    sqlite3VdbeAddOp2(v, OP_NewRowid, iStatCur+1, regNewRowid);
    sqlite3VdbeAddOp3(v, OP_Insert, iStatCur+1, regRec, regNewRowid);
    sqlite3VdbeAddOp2(v, OP_Goto, 0, shortJump);
    sqlite3VdbeJumpHere(v, shortJump+2);
#endif        

    /* Store the results in sqlite_stat1.
    **
    ** The result is a single row of the sqlite_stat1 table.  The first
    ** two columns are the names of the table and index.  The third column
    ** is a string composed of a list of integer statistics about the
    ** index.  The first integer in the list is the total number of entries
    ** in the index.  There is one additional integer in the list for each
    ** column of the table.  This additional integer is a guess of how many
    ** rows of the table the index will select.  If D is the count of distinct
    ** values and K is the total number of rows, then the integer is computed
    ** as:
    **
    **        I = (K+D-1)/D
    **
    ** If K==0 then no entry is made into the sqlite_stat1 table.  
    ** If K>0 then it is always the case the D>0 so division by zero
    ** is never possible.
    */
    sqlite3VdbeAddOp2(v, OP_SCopy, iMem, regStat1);
    if( jZeroRows<0 ){
      jZeroRows = sqlite3VdbeAddOp1(v, OP_IfNot, iMem);
    }
    for(i=0; i<nCol; i++){
      sqlite3VdbeAddOp4(v, OP_String8, 0, regTemp, 0, " ", 0);
      sqlite3VdbeAddOp3(v, OP_Concat, regTemp, regStat1, regStat1);
      sqlite3VdbeAddOp3(v, OP_Add, iMem, iMem+i+1, regTemp);
      sqlite3VdbeAddOp2(v, OP_AddImm, regTemp, -1);
      sqlite3VdbeAddOp3(v, OP_Divide, iMem+i+1, regTemp, regTemp);
      sqlite3VdbeAddOp1(v, OP_ToInt, regTemp);
      sqlite3VdbeAddOp3(v, OP_Concat, regTemp, regStat1, regStat1);
    }
    sqlite3VdbeAddOp4(v, OP_MakeRecord, regTabname, 3, regRec, "aaa", 0);
    sqlite3VdbeAddOp2(v, OP_NewRowid, iStatCur, regNewRowid);
    sqlite3VdbeAddOp3(v, OP_Insert, iStatCur, regRec, regNewRowid);
    sqlite3VdbeChangeP5(v, OPFLAG_APPEND);
  }

  /* If the table has no indices, create a single sqlite_stat1 entry
  ** containing NULL as the index name and the row count as the content.
  */
  if( pTab->pIndex==0 ){
    sqlite3VdbeAddOp3(v, OP_OpenRead, iIdxCur, pTab->tnum, iDb);
    VdbeComment((v, "%s", pTab->zName));
    sqlite3VdbeAddOp2(v, OP_Count, iIdxCur, regStat1);
    sqlite3VdbeAddOp1(v, OP_Close, iIdxCur);
    jZeroRows = sqlite3VdbeAddOp1(v, OP_IfNot, regStat1);
  }else{
    sqlite3VdbeJumpHere(v, jZeroRows);
    jZeroRows = sqlite3VdbeAddOp0(v, OP_Goto);
  }
  sqlite3VdbeAddOp2(v, OP_Null, 0, regIdxname);
  sqlite3VdbeAddOp4(v, OP_MakeRecord, regTabname, 3, regRec, "aaa", 0);
  sqlite3VdbeAddOp2(v, OP_NewRowid, iStatCur, regNewRowid);
  sqlite3VdbeAddOp3(v, OP_Insert, iStatCur, regRec, regNewRowid);
  sqlite3VdbeChangeP5(v, OPFLAG_APPEND);
  if( pParse->nMem<regRec ) pParse->nMem = regRec;
  sqlite3VdbeJumpHere(v, jZeroRows);
}