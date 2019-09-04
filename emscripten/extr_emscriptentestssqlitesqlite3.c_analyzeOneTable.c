#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ mallocFailed; TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_20__ {int tnum; char* zName; TYPE_5__* pIndex; int /*<<< orphan*/  pSchema; } ;
typedef  TYPE_3__ Table ;
struct TYPE_22__ {int nColumn; int tnum; char* zName; scalar_t__* azColl; int /*<<< orphan*/  pSchema; struct TYPE_22__* pNext; } ;
struct TYPE_21__ {int nMem; int /*<<< orphan*/  nTab; TYPE_2__* db; } ;
struct TYPE_18__ {int /*<<< orphan*/  zName; } ;
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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ sqlite3AuthCheck (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3BtreeHoldsAllMutexes (TYPE_2__*) ; 
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
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 

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
  int regSampleno = iMem++;    /* Register containing next sample number */
  int regCol = iMem++;         /* Content of a column analyzed table */
  int regRec = iMem++;         /* Register holding completed record */
  int regTemp = iMem++;        /* Temporary use register */
  int regRowid = iMem++;       /* Rowid for the inserted record */

#ifdef SQLITE_ENABLE_STAT2
  int addr = 0;                /* Instruction address */
  int regTemp2 = iMem++;       /* Temporary use register */
  int regSamplerecno = iMem++; /* Index of next sample to record */
  int regRecno = iMem++;       /* Current sample index */
  int regLast = iMem++;        /* Index of last sample to record */
  int regFirst = iMem++;       /* Index of first sample to record */
#endif

  v = sqlite3GetVdbe(pParse);
  if( v==0 || NEVER(pTab==0) ){
    return;
  }
  if( pTab->tnum==0 ){
    /* Do not gather statistics on views or virtual tables */
    return;
  }
  if( memcmp(pTab->zName, "sqlite_", 7)==0 ){
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

    if( pOnlyIdx && pOnlyIdx!=pIdx ) continue;
    nCol = pIdx->nColumn;
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

#ifdef SQLITE_ENABLE_STAT2

    /* If this iteration of the loop is generating code to analyze the
    ** first index in the pTab->pIndex list, then register regLast has
    ** not been populated. In this case populate it now.  */
    if( pTab->pIndex==pIdx ){
      sqlite3VdbeAddOp2(v, OP_Integer, SQLITE_INDEX_SAMPLES, regSamplerecno);
      sqlite3VdbeAddOp2(v, OP_Integer, SQLITE_INDEX_SAMPLES*2-1, regTemp);
      sqlite3VdbeAddOp2(v, OP_Integer, SQLITE_INDEX_SAMPLES*2, regTemp2);

      sqlite3VdbeAddOp2(v, OP_Count, iIdxCur, regLast);
      sqlite3VdbeAddOp2(v, OP_Null, 0, regFirst);
      addr = sqlite3VdbeAddOp3(v, OP_Lt, regSamplerecno, 0, regLast);
      sqlite3VdbeAddOp3(v, OP_Divide, regTemp2, regLast, regFirst);
      sqlite3VdbeAddOp3(v, OP_Multiply, regLast, regTemp, regLast);
      sqlite3VdbeAddOp2(v, OP_AddImm, regLast, SQLITE_INDEX_SAMPLES*2-2);
      sqlite3VdbeAddOp3(v, OP_Divide,  regTemp2, regLast, regLast);
      sqlite3VdbeJumpHere(v, addr);
    }

    /* Zero the regSampleno and regRecno registers. */
    sqlite3VdbeAddOp2(v, OP_Integer, 0, regSampleno);
    sqlite3VdbeAddOp2(v, OP_Integer, 0, regRecno);
    sqlite3VdbeAddOp2(v, OP_Copy, regFirst, regSamplerecno);
#endif

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
    sqlite3VdbeAddOp2(v, OP_AddImm, iMem, 1);

    for(i=0; i<nCol; i++){
      CollSeq *pColl;
      sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, i, regCol);
      if( i==0 ){
#ifdef SQLITE_ENABLE_STAT2
        /* Check if the record that cursor iIdxCur points to contains a
        ** value that should be stored in the sqlite_stat2 table. If so,
        ** store it.  */
        int ne = sqlite3VdbeAddOp3(v, OP_Ne, regRecno, 0, regSamplerecno);
        assert( regTabname+1==regIdxname 
             && regTabname+2==regSampleno
             && regTabname+3==regCol
        );
        sqlite3VdbeChangeP5(v, SQLITE_JUMPIFNULL);
        sqlite3VdbeAddOp4(v, OP_MakeRecord, regTabname, 4, regRec, "aaab", 0);
        sqlite3VdbeAddOp2(v, OP_NewRowid, iStatCur+1, regRowid);
        sqlite3VdbeAddOp3(v, OP_Insert, iStatCur+1, regRec, regRowid);

        /* Calculate new values for regSamplerecno and regSampleno.
        **
        **   sampleno = sampleno + 1
        **   samplerecno = samplerecno+(remaining records)/(remaining samples)
        */
        sqlite3VdbeAddOp2(v, OP_AddImm, regSampleno, 1);
        sqlite3VdbeAddOp3(v, OP_Subtract, regRecno, regLast, regTemp);
        sqlite3VdbeAddOp2(v, OP_AddImm, regTemp, -1);
        sqlite3VdbeAddOp2(v, OP_Integer, SQLITE_INDEX_SAMPLES, regTemp2);
        sqlite3VdbeAddOp3(v, OP_Subtract, regSampleno, regTemp2, regTemp2);
        sqlite3VdbeAddOp3(v, OP_Divide, regTemp2, regTemp, regTemp);
        sqlite3VdbeAddOp3(v, OP_Add, regSamplerecno, regTemp, regSamplerecno);

        sqlite3VdbeJumpHere(v, ne);
        sqlite3VdbeAddOp2(v, OP_AddImm, regRecno, 1);
#endif

        /* Always record the very first row */
        sqlite3VdbeAddOp1(v, OP_IfNot, iMem+1);
      }
      assert( pIdx->azColl!=0 );
      assert( pIdx->azColl[i]!=0 );
      pColl = sqlite3LocateCollSeq(pParse, pIdx->azColl[i]);
      sqlite3VdbeAddOp4(v, OP_Ne, regCol, 0, iMem+nCol+i+1,
                       (char*)pColl, P4_COLLSEQ);
      sqlite3VdbeChangeP5(v, SQLITE_NULLEQ);
    }
    if( db->mallocFailed ){
      /* If a malloc failure has occurred, then the result of the expression 
      ** passed as the second argument to the call to sqlite3VdbeJumpHere() 
      ** below may be negative. Which causes an assert() to fail (or an
      ** out-of-bounds write if SQLITE_DEBUG is not defined).  */
      return;
    }
    sqlite3VdbeAddOp2(v, OP_Goto, 0, endOfLoop);
    for(i=0; i<nCol; i++){
      int addr2 = sqlite3VdbeCurrentAddr(v) - (nCol*2);
      if( i==0 ){
        sqlite3VdbeJumpHere(v, addr2-1);  /* Set jump dest for the OP_IfNot */
      }
      sqlite3VdbeJumpHere(v, addr2);      /* Set jump dest for the OP_Ne */
      sqlite3VdbeAddOp2(v, OP_AddImm, iMem+i+1, 1);
      sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, i, iMem+nCol+i+1);
    }

    /* End of the analysis loop. */
    sqlite3VdbeResolveLabel(v, endOfLoop);
    sqlite3VdbeAddOp2(v, OP_Next, iIdxCur, topOfLoop);
    sqlite3VdbeAddOp1(v, OP_Close, iIdxCur);

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
    sqlite3VdbeAddOp2(v, OP_SCopy, iMem, regSampleno);
    if( jZeroRows<0 ){
      jZeroRows = sqlite3VdbeAddOp1(v, OP_IfNot, iMem);
    }
    for(i=0; i<nCol; i++){
      sqlite3VdbeAddOp4(v, OP_String8, 0, regTemp, 0, " ", 0);
      sqlite3VdbeAddOp3(v, OP_Concat, regTemp, regSampleno, regSampleno);
      sqlite3VdbeAddOp3(v, OP_Add, iMem, iMem+i+1, regTemp);
      sqlite3VdbeAddOp2(v, OP_AddImm, regTemp, -1);
      sqlite3VdbeAddOp3(v, OP_Divide, iMem+i+1, regTemp, regTemp);
      sqlite3VdbeAddOp1(v, OP_ToInt, regTemp);
      sqlite3VdbeAddOp3(v, OP_Concat, regTemp, regSampleno, regSampleno);
    }
    sqlite3VdbeAddOp4(v, OP_MakeRecord, regTabname, 3, regRec, "aaa", 0);
    sqlite3VdbeAddOp2(v, OP_NewRowid, iStatCur, regRowid);
    sqlite3VdbeAddOp3(v, OP_Insert, iStatCur, regRec, regRowid);
    sqlite3VdbeChangeP5(v, OPFLAG_APPEND);
  }

  /* If the table has no indices, create a single sqlite_stat1 entry
  ** containing NULL as the index name and the row count as the content.
  */
  if( pTab->pIndex==0 ){
    sqlite3VdbeAddOp3(v, OP_OpenRead, iIdxCur, pTab->tnum, iDb);
    VdbeComment((v, "%s", pTab->zName));
    sqlite3VdbeAddOp2(v, OP_Count, iIdxCur, regSampleno);
    sqlite3VdbeAddOp1(v, OP_Close, iIdxCur);
    jZeroRows = sqlite3VdbeAddOp1(v, OP_IfNot, regSampleno);
  }else{
    sqlite3VdbeJumpHere(v, jZeroRows);
    jZeroRows = sqlite3VdbeAddOp0(v, OP_Goto);
  }
  sqlite3VdbeAddOp2(v, OP_Null, 0, regIdxname);
  sqlite3VdbeAddOp4(v, OP_MakeRecord, regTabname, 3, regRec, "aaa", 0);
  sqlite3VdbeAddOp2(v, OP_NewRowid, iStatCur, regRowid);
  sqlite3VdbeAddOp3(v, OP_Insert, iStatCur, regRec, regRowid);
  sqlite3VdbeChangeP5(v, OPFLAG_APPEND);
  if( pParse->nMem<regRec ) pParse->nMem = regRec;
  sqlite3VdbeJumpHere(v, jZeroRows);
}