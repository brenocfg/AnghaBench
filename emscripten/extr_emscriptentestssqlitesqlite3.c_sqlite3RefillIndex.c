#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_23__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  tnum; } ;
typedef  TYPE_3__ Table ;
struct TYPE_25__ {int tnum; scalar_t__ onError; int nColumn; int /*<<< orphan*/  zName; int /*<<< orphan*/  pSchema; TYPE_3__* pTable; } ;
struct TYPE_24__ {TYPE_2__* db; int /*<<< orphan*/  nTab; } ;
struct TYPE_21__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_4__ Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;
typedef  TYPE_5__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  OE_Abort ; 
 scalar_t__ OE_None ; 
 int OPFLAG_USESEEKRESULT ; 
 int /*<<< orphan*/  OP_Clear ; 
 int /*<<< orphan*/  OP_Close ; 
 int /*<<< orphan*/  OP_IdxInsert ; 
 int /*<<< orphan*/  OP_IsUnique ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_OpenRead ; 
 int /*<<< orphan*/  OP_OpenWrite ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  P4_INT32 ; 
 int /*<<< orphan*/  P4_KEYINFO_HANDOFF ; 
 int /*<<< orphan*/  P4_STATIC ; 
 void* SQLITE_INT_TO_PTR (int) ; 
 int /*<<< orphan*/  SQLITE_REINDEX ; 
 scalar_t__ sqlite3AuthCheck (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3GenerateIndexKey (TYPE_4__*,TYPE_5__*,int,int,int) ; 
 int sqlite3GetTempReg (TYPE_4__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3HaltConstraint (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3IndexKeyinfo (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3OpenTable (TYPE_4__*,int,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_4__*,int) ; 
 int sqlite3SchemaToIndex (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3TableLock (TYPE_4__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int const,int const,void* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sqlite3RefillIndex(Parse *pParse, Index *pIndex, int memRootPage){
  Table *pTab = pIndex->pTable;  /* The table that is indexed */
  int iTab = pParse->nTab++;     /* Btree cursor used for pTab */
  int iIdx = pParse->nTab++;     /* Btree cursor used for pIndex */
  int addr1;                     /* Address of top of loop */
  int tnum;                      /* Root page of index */
  Vdbe *v;                       /* Generate code into this virtual machine */
  KeyInfo *pKey;                 /* KeyInfo for index */
  int regIdxKey;                 /* Registers containing the index key */
  int regRecord;                 /* Register holding assemblied index record */
  sqlite3 *db = pParse->db;      /* The database connection */
  int iDb = sqlite3SchemaToIndex(db, pIndex->pSchema);

#ifndef SQLITE_OMIT_AUTHORIZATION
  if( sqlite3AuthCheck(pParse, SQLITE_REINDEX, pIndex->zName, 0,
      db->aDb[iDb].zName ) ){
    return;
  }
#endif

  /* Require a write-lock on the table to perform this operation */
  sqlite3TableLock(pParse, iDb, pTab->tnum, 1, pTab->zName);

  v = sqlite3GetVdbe(pParse);
  if( v==0 ) return;
  if( memRootPage>=0 ){
    tnum = memRootPage;
  }else{
    tnum = pIndex->tnum;
    sqlite3VdbeAddOp2(v, OP_Clear, tnum, iDb);
  }
  pKey = sqlite3IndexKeyinfo(pParse, pIndex);
  sqlite3VdbeAddOp4(v, OP_OpenWrite, iIdx, tnum, iDb, 
                    (char *)pKey, P4_KEYINFO_HANDOFF);
  if( memRootPage>=0 ){
    sqlite3VdbeChangeP5(v, 1);
  }
  sqlite3OpenTable(pParse, iTab, iDb, pTab, OP_OpenRead);
  addr1 = sqlite3VdbeAddOp2(v, OP_Rewind, iTab, 0);
  regRecord = sqlite3GetTempReg(pParse);
  regIdxKey = sqlite3GenerateIndexKey(pParse, pIndex, iTab, regRecord, 1);
  if( pIndex->onError!=OE_None ){
    const int regRowid = regIdxKey + pIndex->nColumn;
    const int j2 = sqlite3VdbeCurrentAddr(v) + 2;
    void * const pRegKey = SQLITE_INT_TO_PTR(regIdxKey);

    /* The registers accessed by the OP_IsUnique opcode were allocated
    ** using sqlite3GetTempRange() inside of the sqlite3GenerateIndexKey()
    ** call above. Just before that function was freed they were released
    ** (made available to the compiler for reuse) using 
    ** sqlite3ReleaseTempRange(). So in some ways having the OP_IsUnique
    ** opcode use the values stored within seems dangerous. However, since
    ** we can be sure that no other temp registers have been allocated
    ** since sqlite3ReleaseTempRange() was called, it is safe to do so.
    */
    sqlite3VdbeAddOp4(v, OP_IsUnique, iIdx, j2, regRowid, pRegKey, P4_INT32);
    sqlite3HaltConstraint(
        pParse, OE_Abort, "indexed columns are not unique", P4_STATIC);
  }
  sqlite3VdbeAddOp2(v, OP_IdxInsert, iIdx, regRecord);
  sqlite3VdbeChangeP5(v, OPFLAG_USESEEKRESULT);
  sqlite3ReleaseTempReg(pParse, regRecord);
  sqlite3VdbeAddOp2(v, OP_Next, iTab, addr1+1);
  sqlite3VdbeJumpHere(v, addr1);
  sqlite3VdbeAddOp1(v, OP_Close, iTab);
  sqlite3VdbeAddOp1(v, OP_Close, iIdx);
}