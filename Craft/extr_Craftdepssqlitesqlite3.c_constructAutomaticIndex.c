#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct SrcList_item {int colUsed; TYPE_7__* pTab; } ;
struct TYPE_31__ {int leftColumn; } ;
struct TYPE_32__ {TYPE_3__ u; TYPE_10__* pExpr; } ;
typedef  TYPE_4__ WhereTerm ;
struct TYPE_29__ {TYPE_9__* pIdx; } ;
struct TYPE_30__ {int nEq; int wsFlags; TYPE_1__ u; } ;
struct TYPE_33__ {scalar_t__ iIdxCur; scalar_t__ iTabCur; TYPE_2__ plan; } ;
typedef  TYPE_5__ WhereLevel ;
struct TYPE_34__ {size_t nTerm; TYPE_4__* a; } ;
typedef  TYPE_6__ WhereClause ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_35__ {int nCol; int /*<<< orphan*/  zName; } ;
typedef  TYPE_7__ Table ;
struct TYPE_37__ {char** azColl; int* aiColumn; char* zName; int nColumn; TYPE_7__* pTable; int /*<<< orphan*/ * aSortOrder; } ;
struct TYPE_36__ {int /*<<< orphan*/  db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_28__ {char* zName; } ;
struct TYPE_27__ {int /*<<< orphan*/  pRight; int /*<<< orphan*/  pLeft; } ;
typedef  TYPE_8__ Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;
typedef  TYPE_9__ Index ;
typedef  TYPE_10__ Expr ;
typedef  TYPE_11__ CollSeq ;
typedef  int Bitmask ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_11__*) ; 
 int BMS ; 
 int /*<<< orphan*/  OPFLAG_USESEEKRESULT ; 
 int /*<<< orphan*/  OP_IdxInsert ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_OpenAutoindex ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  P4_KEYINFO_HANDOFF ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_AUTOINDEX ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int WHERE_COLUMN_EQ ; 
 int WHERE_IDX_ONLY ; 
 int WO_EQ ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_11__* sqlite3BinaryCompareCollSeq (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3CodeOnce (TYPE_8__*) ; 
 TYPE_9__* sqlite3DbMallocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3GenerateIndexKey (TYPE_8__*,TYPE_9__*,scalar_t__,int,int) ; 
 int sqlite3GetTempReg (TYPE_8__*) ; 
 int /*<<< orphan*/ * sqlite3IndexKeyinfo (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_8__*,int) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 scalar_t__ termCanDriveIndex (TYPE_4__*,struct SrcList_item*,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void constructAutomaticIndex(
  Parse *pParse,              /* The parsing context */
  WhereClause *pWC,           /* The WHERE clause */
  struct SrcList_item *pSrc,  /* The FROM clause term to get the next index */
  Bitmask notReady,           /* Mask of cursors that are not available */
  WhereLevel *pLevel          /* Write new index here */
){
  int nColumn;                /* Number of columns in the constructed index */
  WhereTerm *pTerm;           /* A single term of the WHERE clause */
  WhereTerm *pWCEnd;          /* End of pWC->a[] */
  int nByte;                  /* Byte of memory needed for pIdx */
  Index *pIdx;                /* Object describing the transient index */
  Vdbe *v;                    /* Prepared statement under construction */
  int addrInit;               /* Address of the initialization bypass jump */
  Table *pTable;              /* The table being indexed */
  KeyInfo *pKeyinfo;          /* Key information for the index */   
  int addrTop;                /* Top of the index fill loop */
  int regRecord;              /* Register holding an index record */
  int n;                      /* Column counter */
  int i;                      /* Loop counter */
  int mxBitCol;               /* Maximum column in pSrc->colUsed */
  CollSeq *pColl;             /* Collating sequence to on a column */
  Bitmask idxCols;            /* Bitmap of columns used for indexing */
  Bitmask extraCols;          /* Bitmap of additional columns */

  /* Generate code to skip over the creation and initialization of the
  ** transient index on 2nd and subsequent iterations of the loop. */
  v = pParse->pVdbe;
  assert( v!=0 );
  addrInit = sqlite3CodeOnce(pParse);

  /* Count the number of columns that will be added to the index
  ** and used to match WHERE clause constraints */
  nColumn = 0;
  pTable = pSrc->pTab;
  pWCEnd = &pWC->a[pWC->nTerm];
  idxCols = 0;
  for(pTerm=pWC->a; pTerm<pWCEnd; pTerm++){
    if( termCanDriveIndex(pTerm, pSrc, notReady) ){
      int iCol = pTerm->u.leftColumn;
      Bitmask cMask = iCol>=BMS ? ((Bitmask)1)<<(BMS-1) : ((Bitmask)1)<<iCol;
      testcase( iCol==BMS );
      testcase( iCol==BMS-1 );
      if( (idxCols & cMask)==0 ){
        nColumn++;
        idxCols |= cMask;
      }
    }
  }
  assert( nColumn>0 );
  pLevel->plan.nEq = nColumn;

  /* Count the number of additional columns needed to create a
  ** covering index.  A "covering index" is an index that contains all
  ** columns that are needed by the query.  With a covering index, the
  ** original table never needs to be accessed.  Automatic indices must
  ** be a covering index because the index will not be updated if the
  ** original table changes and the index and table cannot both be used
  ** if they go out of sync.
  */
  extraCols = pSrc->colUsed & (~idxCols | (((Bitmask)1)<<(BMS-1)));
  mxBitCol = (pTable->nCol >= BMS-1) ? BMS-1 : pTable->nCol;
  testcase( pTable->nCol==BMS-1 );
  testcase( pTable->nCol==BMS-2 );
  for(i=0; i<mxBitCol; i++){
    if( extraCols & (((Bitmask)1)<<i) ) nColumn++;
  }
  if( pSrc->colUsed & (((Bitmask)1)<<(BMS-1)) ){
    nColumn += pTable->nCol - BMS + 1;
  }
  pLevel->plan.wsFlags |= WHERE_COLUMN_EQ | WHERE_IDX_ONLY | WO_EQ;

  /* Construct the Index object to describe this index */
  nByte = sizeof(Index);
  nByte += nColumn*sizeof(int);     /* Index.aiColumn */
  nByte += nColumn*sizeof(char*);   /* Index.azColl */
  nByte += nColumn;                 /* Index.aSortOrder */
  pIdx = sqlite3DbMallocZero(pParse->db, nByte);
  if( pIdx==0 ) return;
  pLevel->plan.u.pIdx = pIdx;
  pIdx->azColl = (char**)&pIdx[1];
  pIdx->aiColumn = (int*)&pIdx->azColl[nColumn];
  pIdx->aSortOrder = (u8*)&pIdx->aiColumn[nColumn];
  pIdx->zName = "auto-index";
  pIdx->nColumn = nColumn;
  pIdx->pTable = pTable;
  n = 0;
  idxCols = 0;
  for(pTerm=pWC->a; pTerm<pWCEnd; pTerm++){
    if( termCanDriveIndex(pTerm, pSrc, notReady) ){
      int iCol = pTerm->u.leftColumn;
      Bitmask cMask = iCol>=BMS ? ((Bitmask)1)<<(BMS-1) : ((Bitmask)1)<<iCol;
      if( (idxCols & cMask)==0 ){
        Expr *pX = pTerm->pExpr;
        idxCols |= cMask;
        pIdx->aiColumn[n] = pTerm->u.leftColumn;
        pColl = sqlite3BinaryCompareCollSeq(pParse, pX->pLeft, pX->pRight);
        pIdx->azColl[n] = ALWAYS(pColl) ? pColl->zName : "BINARY";
        n++;
      }
    }
  }
  assert( (u32)n==pLevel->plan.nEq );

  /* Add additional columns needed to make the automatic index into
  ** a covering index */
  for(i=0; i<mxBitCol; i++){
    if( extraCols & (((Bitmask)1)<<i) ){
      pIdx->aiColumn[n] = i;
      pIdx->azColl[n] = "BINARY";
      n++;
    }
  }
  if( pSrc->colUsed & (((Bitmask)1)<<(BMS-1)) ){
    for(i=BMS-1; i<pTable->nCol; i++){
      pIdx->aiColumn[n] = i;
      pIdx->azColl[n] = "BINARY";
      n++;
    }
  }
  assert( n==nColumn );

  /* Create the automatic index */
  pKeyinfo = sqlite3IndexKeyinfo(pParse, pIdx);
  assert( pLevel->iIdxCur>=0 );
  sqlite3VdbeAddOp4(v, OP_OpenAutoindex, pLevel->iIdxCur, nColumn+1, 0,
                    (char*)pKeyinfo, P4_KEYINFO_HANDOFF);
  VdbeComment((v, "for %s", pTable->zName));

  /* Fill the automatic index with content */
  addrTop = sqlite3VdbeAddOp1(v, OP_Rewind, pLevel->iTabCur);
  regRecord = sqlite3GetTempReg(pParse);
  sqlite3GenerateIndexKey(pParse, pIdx, pLevel->iTabCur, regRecord, 1);
  sqlite3VdbeAddOp2(v, OP_IdxInsert, pLevel->iIdxCur, regRecord);
  sqlite3VdbeChangeP5(v, OPFLAG_USESEEKRESULT);
  sqlite3VdbeAddOp2(v, OP_Next, pLevel->iTabCur, addrTop+1);
  sqlite3VdbeChangeP5(v, SQLITE_STMTSTATUS_AUTOINDEX);
  sqlite3VdbeJumpHere(v, addrTop);
  sqlite3ReleaseTempReg(pParse, regRecord);
  
  /* Jump here when skipping the initialization */
  sqlite3VdbeJumpHere(v, addrInit);
}