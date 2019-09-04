#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_9__ ;
typedef  struct TYPE_42__   TYPE_8__ ;
typedef  struct TYPE_41__   TYPE_7__ ;
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_12__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
struct SrcList_item {int iCursor; int jointype; scalar_t__ notIndexed; int colUsed; TYPE_8__* pIndex; TYPE_3__* pTab; } ;
struct TYPE_41__ {int eOperator; int prereqRight; int wtFlags; int prereqAll; TYPE_12__* pExpr; } ;
typedef  TYPE_7__ WhereTerm ;
struct TYPE_39__ {TYPE_8__* pIdx; } ;
struct TYPE_40__ {double nRow; int wsFlags; int nEq; TYPE_5__ u; } ;
struct TYPE_42__ {double rCost; int nColumn; int* aiColumn; unsigned int* aiRowEst; scalar_t__ onError; scalar_t__ bUnordered; char* zName; int used; TYPE_6__ plan; struct TYPE_42__* pNext; TYPE_3__* pTable; } ;
typedef  TYPE_8__ WhereCost ;
struct TYPE_43__ {int nTerm; TYPE_7__* a; int /*<<< orphan*/  pMaskSet; } ;
typedef  TYPE_9__ WhereClause ;
struct TYPE_38__ {int flags; } ;
struct TYPE_37__ {unsigned int nRowEst; int /*<<< orphan*/  zName; TYPE_8__* pIndex; } ;
struct TYPE_36__ {TYPE_1__* pList; } ;
struct TYPE_35__ {int nExpr; } ;
struct TYPE_34__ {TYPE_2__ x; } ;
struct TYPE_33__ {TYPE_4__* db; } ;
typedef  TYPE_10__ Parse ;
typedef  TYPE_8__ Index ;
typedef  int /*<<< orphan*/  ExprList ;
typedef  TYPE_12__ Expr ;
typedef  int Bitmask ;

/* Variables and functions */
 scalar_t__ ALWAYS (int /*<<< orphan*/ ) ; 
 int BMS ; 
 int /*<<< orphan*/  EP_xIsSelect ; 
 scalar_t__ ExprHasProperty (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int JT_LEFT ; 
 scalar_t__ OE_None ; 
 scalar_t__ OE_Replace ; 
 double SQLITE_BIG_DBL ; 
 int SQLITE_ReverseOrder ; 
 int TERM_VIRTUAL ; 
 int /*<<< orphan*/  WHERETRACE (char*) ; 
 int WHERE_BTM_LIMIT ; 
 int WHERE_COLUMN_EQ ; 
 int WHERE_COLUMN_IN ; 
 int WHERE_COLUMN_NULL ; 
 int WHERE_COLUMN_RANGE ; 
 int WHERE_IDX_ONLY ; 
 int WHERE_NOT_FULLSCAN ; 
 int WHERE_ORDERBY ; 
 int WHERE_REVERSE ; 
 int WHERE_ROWID_EQ ; 
 int WHERE_ROWID_RANGE ; 
 int WHERE_TOP_LIMIT ; 
 int WHERE_UNIQUE ; 
 int WO_EQ ; 
 int WO_GE ; 
 int WO_GT ; 
 int WO_IN ; 
 int WO_ISNULL ; 
 int WO_LE ; 
 int WO_LT ; 
 int WO_NOOP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bestAutomaticIndex (TYPE_10__*,TYPE_9__*,struct SrcList_item*,int,TYPE_8__*) ; 
 int /*<<< orphan*/  bestOrClauseIndex (TYPE_10__*,TYPE_9__*,struct SrcList_item*,int,int,int /*<<< orphan*/ *,TYPE_8__*) ; 
 double estLog (unsigned int const) ; 
 TYPE_7__* findTerm (TYPE_9__*,int,int,int,int,TYPE_8__*) ; 
 int getMask (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isSortingIndex (TYPE_10__*,int /*<<< orphan*/ ,TYPE_8__*,int,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  testcase (int) ; 
 int /*<<< orphan*/  whereRangeScanEst (TYPE_10__*,TYPE_8__*,int,TYPE_7__*,TYPE_7__*,int*) ; 

__attribute__((used)) static void bestBtreeIndex(
  Parse *pParse,              /* The parsing context */
  WhereClause *pWC,           /* The WHERE clause */
  struct SrcList_item *pSrc,  /* The FROM clause term to search */
  Bitmask notReady,           /* Mask of cursors not available for indexing */
  Bitmask notValid,           /* Cursors not available for any purpose */
  ExprList *pOrderBy,         /* The ORDER BY clause */
  WhereCost *pCost            /* Lowest cost query plan */
){
  int iCur = pSrc->iCursor;   /* The cursor of the table to be accessed */
  Index *pProbe;              /* An index we are evaluating */
  Index *pIdx;                /* Copy of pProbe, or zero for IPK index */
  int eqTermMask;             /* Current mask of valid equality operators */
  int idxEqTermMask;          /* Index mask of valid equality operators */
  Index sPk;                  /* A fake index object for the primary key */
  unsigned int aiRowEstPk[2]; /* The aiRowEst[] value for the sPk index */
  int aiColumnPk = -1;        /* The aColumn[] value for the sPk index */
  int wsFlagMask;             /* Allowed flags in pCost->plan.wsFlag */

  /* Initialize the cost to a worst-case value */
  memset(pCost, 0, sizeof(*pCost));
  pCost->rCost = SQLITE_BIG_DBL;

  /* If the pSrc table is the right table of a LEFT JOIN then we may not
  ** use an index to satisfy IS NULL constraints on that table.  This is
  ** because columns might end up being NULL if the table does not match -
  ** a circumstance which the index cannot help us discover.  Ticket #2177.
  */
  if( pSrc->jointype & JT_LEFT ){
    idxEqTermMask = WO_EQ|WO_IN;
  }else{
    idxEqTermMask = WO_EQ|WO_IN|WO_ISNULL;
  }

  if( pSrc->pIndex ){
    /* An INDEXED BY clause specifies a particular index to use */
    pIdx = pProbe = pSrc->pIndex;
    wsFlagMask = ~(WHERE_ROWID_EQ|WHERE_ROWID_RANGE);
    eqTermMask = idxEqTermMask;
  }else{
    /* There is no INDEXED BY clause.  Create a fake Index object in local
    ** variable sPk to represent the rowid primary key index.  Make this
    ** fake index the first in a chain of Index objects with all of the real
    ** indices to follow */
    Index *pFirst;                  /* First of real indices on the table */
    memset(&sPk, 0, sizeof(Index));
    sPk.nColumn = 1;
    sPk.aiColumn = &aiColumnPk;
    sPk.aiRowEst = aiRowEstPk;
    sPk.onError = OE_Replace;
    sPk.pTable = pSrc->pTab;
    aiRowEstPk[0] = pSrc->pTab->nRowEst;
    aiRowEstPk[1] = 1;
    pFirst = pSrc->pTab->pIndex;
    if( pSrc->notIndexed==0 ){
      /* The real indices of the table are only considered if the
      ** NOT INDEXED qualifier is omitted from the FROM clause */
      sPk.pNext = pFirst;
    }
    pProbe = &sPk;
    wsFlagMask = ~(
        WHERE_COLUMN_IN|WHERE_COLUMN_EQ|WHERE_COLUMN_NULL|WHERE_COLUMN_RANGE
    );
    eqTermMask = WO_EQ|WO_IN;
    pIdx = 0;
  }

  /* Loop over all indices looking for the best one to use
  */
  for(; pProbe; pIdx=pProbe=pProbe->pNext){
    const unsigned int * const aiRowEst = pProbe->aiRowEst;
    double cost;                /* Cost of using pProbe */
    double nRow;                /* Estimated number of rows in result set */
    double log10N;              /* base-10 logarithm of nRow (inexact) */
    int rev;                    /* True to scan in reverse order */
    int wsFlags = 0;
    Bitmask used = 0;

    /* The following variables are populated based on the properties of
    ** index being evaluated. They are then used to determine the expected
    ** cost and number of rows returned.
    **
    **  nEq: 
    **    Number of equality terms that can be implemented using the index.
    **    In other words, the number of initial fields in the index that
    **    are used in == or IN or NOT NULL constraints of the WHERE clause.
    **
    **  nInMul:  
    **    The "in-multiplier". This is an estimate of how many seek operations 
    **    SQLite must perform on the index in question. For example, if the 
    **    WHERE clause is:
    **
    **      WHERE a IN (1, 2, 3) AND b IN (4, 5, 6)
    **
    **    SQLite must perform 9 lookups on an index on (a, b), so nInMul is 
    **    set to 9. Given the same schema and either of the following WHERE 
    **    clauses:
    **
    **      WHERE a =  1
    **      WHERE a >= 2
    **
    **    nInMul is set to 1.
    **
    **    If there exists a WHERE term of the form "x IN (SELECT ...)", then 
    **    the sub-select is assumed to return 25 rows for the purposes of 
    **    determining nInMul.
    **
    **  bInEst:  
    **    Set to true if there was at least one "x IN (SELECT ...)" term used 
    **    in determining the value of nInMul.  Note that the RHS of the
    **    IN operator must be a SELECT, not a value list, for this variable
    **    to be true.
    **
    **  estBound:
    **    An estimate on the amount of the table that must be searched.  A
    **    value of 100 means the entire table is searched.  Range constraints
    **    might reduce this to a value less than 100 to indicate that only
    **    a fraction of the table needs searching.  In the absence of
    **    sqlite_stat2 ANALYZE data, a single inequality reduces the search
    **    space to 1/4rd its original size.  So an x>? constraint reduces
    **    estBound to 25.  Two constraints (x>? AND x<?) reduce estBound to 6.
    **
    **  bSort:   
    **    Boolean. True if there is an ORDER BY clause that will require an 
    **    external sort (i.e. scanning the index being evaluated will not 
    **    correctly order records).
    **
    **  bLookup: 
    **    Boolean. True if a table lookup is required for each index entry
    **    visited.  In other words, true if this is not a covering index.
    **    This is always false for the rowid primary key index of a table.
    **    For other indexes, it is true unless all the columns of the table
    **    used by the SELECT statement are present in the index (such an
    **    index is sometimes described as a covering index).
    **    For example, given the index on (a, b), the second of the following 
    **    two queries requires table b-tree lookups in order to find the value
    **    of column c, but the first does not because columns a and b are
    **    both available in the index.
    **
    **             SELECT a, b    FROM tbl WHERE a = 1;
    **             SELECT a, b, c FROM tbl WHERE a = 1;
    */
    int nEq;                      /* Number of == or IN terms matching index */
    int bInEst = 0;               /* True if "x IN (SELECT...)" seen */
    int nInMul = 1;               /* Number of distinct equalities to lookup */
    int estBound = 100;           /* Estimated reduction in search space */
    int nBound = 0;               /* Number of range constraints seen */
    int bSort = 0;                /* True if external sort required */
    int bLookup = 0;              /* True if not a covering index */
    WhereTerm *pTerm;             /* A single term of the WHERE clause */
#ifdef SQLITE_ENABLE_STAT2
    WhereTerm *pFirstTerm = 0;    /* First term matching the index */
#endif

    /* Determine the values of nEq and nInMul */
    for(nEq=0; nEq<pProbe->nColumn; nEq++){
      int j = pProbe->aiColumn[nEq];
      pTerm = findTerm(pWC, iCur, j, notReady, eqTermMask, pIdx);
      if( pTerm==0 ) break;
      wsFlags |= (WHERE_COLUMN_EQ|WHERE_ROWID_EQ);
      if( pTerm->eOperator & WO_IN ){
        Expr *pExpr = pTerm->pExpr;
        wsFlags |= WHERE_COLUMN_IN;
        if( ExprHasProperty(pExpr, EP_xIsSelect) ){
          /* "x IN (SELECT ...)":  Assume the SELECT returns 25 rows */
          nInMul *= 25;
          bInEst = 1;
        }else if( ALWAYS(pExpr->x.pList && pExpr->x.pList->nExpr) ){
          /* "x IN (value, value, ...)" */
          nInMul *= pExpr->x.pList->nExpr;
        }
      }else if( pTerm->eOperator & WO_ISNULL ){
        wsFlags |= WHERE_COLUMN_NULL;
      }
#ifdef SQLITE_ENABLE_STAT2
      if( nEq==0 && pProbe->aSample ) pFirstTerm = pTerm;
#endif
      used |= pTerm->prereqRight;
    }

    /* Determine the value of estBound. */
    if( nEq<pProbe->nColumn && pProbe->bUnordered==0 ){
      int j = pProbe->aiColumn[nEq];
      if( findTerm(pWC, iCur, j, notReady, WO_LT|WO_LE|WO_GT|WO_GE, pIdx) ){
        WhereTerm *pTop = findTerm(pWC, iCur, j, notReady, WO_LT|WO_LE, pIdx);
        WhereTerm *pBtm = findTerm(pWC, iCur, j, notReady, WO_GT|WO_GE, pIdx);
        whereRangeScanEst(pParse, pProbe, nEq, pBtm, pTop, &estBound);
        if( pTop ){
          nBound = 1;
          wsFlags |= WHERE_TOP_LIMIT;
          used |= pTop->prereqRight;
        }
        if( pBtm ){
          nBound++;
          wsFlags |= WHERE_BTM_LIMIT;
          used |= pBtm->prereqRight;
        }
        wsFlags |= (WHERE_COLUMN_RANGE|WHERE_ROWID_RANGE);
      }
    }else if( pProbe->onError!=OE_None ){
      testcase( wsFlags & WHERE_COLUMN_IN );
      testcase( wsFlags & WHERE_COLUMN_NULL );
      if( (wsFlags & (WHERE_COLUMN_IN|WHERE_COLUMN_NULL))==0 ){
        wsFlags |= WHERE_UNIQUE;
      }
    }

    /* If there is an ORDER BY clause and the index being considered will
    ** naturally scan rows in the required order, set the appropriate flags
    ** in wsFlags. Otherwise, if there is an ORDER BY clause but the index
    ** will scan rows in a different order, set the bSort variable.  */
    if( pOrderBy ){
      if( (wsFlags & WHERE_COLUMN_IN)==0
        && pProbe->bUnordered==0
        && isSortingIndex(pParse, pWC->pMaskSet, pProbe, iCur, pOrderBy,
                          nEq, wsFlags, &rev)
      ){
        wsFlags |= WHERE_ROWID_RANGE|WHERE_COLUMN_RANGE|WHERE_ORDERBY;
        wsFlags |= (rev ? WHERE_REVERSE : 0);
      }else{
        bSort = 1;
      }
    }

    /* If currently calculating the cost of using an index (not the IPK
    ** index), determine if all required column data may be obtained without 
    ** using the main table (i.e. if the index is a covering
    ** index for this query). If it is, set the WHERE_IDX_ONLY flag in
    ** wsFlags. Otherwise, set the bLookup variable to true.  */
    if( pIdx && wsFlags ){
      Bitmask m = pSrc->colUsed;
      int j;
      for(j=0; j<pIdx->nColumn; j++){
        int x = pIdx->aiColumn[j];
        if( x<BMS-1 ){
          m &= ~(((Bitmask)1)<<x);
        }
      }
      if( m==0 ){
        wsFlags |= WHERE_IDX_ONLY;
      }else{
        bLookup = 1;
      }
    }

    /*
    ** Estimate the number of rows of output.  For an "x IN (SELECT...)"
    ** constraint, do not let the estimate exceed half the rows in the table.
    */
    nRow = (double)(aiRowEst[nEq] * nInMul);
    if( bInEst && nRow*2>aiRowEst[0] ){
      nRow = aiRowEst[0]/2;
      nInMul = (int)(nRow / aiRowEst[nEq]);
    }

#ifdef SQLITE_ENABLE_STAT2
    /* If the constraint is of the form x=VALUE and histogram
    ** data is available for column x, then it might be possible
    ** to get a better estimate on the number of rows based on
    ** VALUE and how common that value is according to the histogram.
    */
    if( nRow>(double)1 && nEq==1 && pFirstTerm!=0 ){
      if( pFirstTerm->eOperator & (WO_EQ|WO_ISNULL) ){
        testcase( pFirstTerm->eOperator==WO_EQ );
        testcase( pFirstTerm->eOperator==WO_ISNULL );
        whereEqualScanEst(pParse, pProbe, pFirstTerm->pExpr->pRight, &nRow);
      }else if( pFirstTerm->eOperator==WO_IN && bInEst==0 ){
        whereInScanEst(pParse, pProbe, pFirstTerm->pExpr->x.pList, &nRow);
      }
    }
#endif /* SQLITE_ENABLE_STAT2 */

    /* Adjust the number of output rows and downward to reflect rows
    ** that are excluded by range constraints.
    */
    nRow = (nRow * (double)estBound) / (double)100;
    if( nRow<1 ) nRow = 1;

    /* Experiments run on real SQLite databases show that the time needed
    ** to do a binary search to locate a row in a table or index is roughly
    ** log10(N) times the time to move from one row to the next row within
    ** a table or index.  The actual times can vary, with the size of
    ** records being an important factor.  Both moves and searches are
    ** slower with larger records, presumably because fewer records fit
    ** on one page and hence more pages have to be fetched.
    **
    ** The ANALYZE command and the sqlite_stat1 and sqlite_stat2 tables do
    ** not give us data on the relative sizes of table and index records.
    ** So this computation assumes table records are about twice as big
    ** as index records
    */
    if( (wsFlags & WHERE_NOT_FULLSCAN)==0 ){
      /* The cost of a full table scan is a number of move operations equal
      ** to the number of rows in the table.
      **
      ** We add an additional 4x penalty to full table scans.  This causes
      ** the cost function to err on the side of choosing an index over
      ** choosing a full scan.  This 4x full-scan penalty is an arguable
      ** decision and one which we expect to revisit in the future.  But
      ** it seems to be working well enough at the moment.
      */
      cost = aiRowEst[0]*4;
    }else{
      log10N = estLog(aiRowEst[0]);
      cost = nRow;
      if( pIdx ){
        if( bLookup ){
          /* For an index lookup followed by a table lookup:
          **    nInMul index searches to find the start of each index range
          **  + nRow steps through the index
          **  + nRow table searches to lookup the table entry using the rowid
          */
          cost += (nInMul + nRow)*log10N;
        }else{
          /* For a covering index:
          **     nInMul index searches to find the initial entry 
          **   + nRow steps through the index
          */
          cost += nInMul*log10N;
        }
      }else{
        /* For a rowid primary key lookup:
        **    nInMult table searches to find the initial entry for each range
        **  + nRow steps through the table
        */
        cost += nInMul*log10N;
      }
    }

    /* Add in the estimated cost of sorting the result.  Actual experimental
    ** measurements of sorting performance in SQLite show that sorting time
    ** adds C*N*log10(N) to the cost, where N is the number of rows to be 
    ** sorted and C is a factor between 1.95 and 4.3.  We will split the
    ** difference and select C of 3.0.
    */
    if( bSort ){
      cost += nRow*estLog(nRow)*3;
    }

    /**** Cost of using this index has now been computed ****/

    /* If there are additional constraints on this table that cannot
    ** be used with the current index, but which might lower the number
    ** of output rows, adjust the nRow value accordingly.  This only 
    ** matters if the current index is the least costly, so do not bother
    ** with this step if we already know this index will not be chosen.
    ** Also, never reduce the output row count below 2 using this step.
    **
    ** It is critical that the notValid mask be used here instead of
    ** the notReady mask.  When computing an "optimal" index, the notReady
    ** mask will only have one bit set - the bit for the current table.
    ** The notValid mask, on the other hand, always has all bits set for
    ** tables that are not in outer loops.  If notReady is used here instead
    ** of notValid, then a optimal index that depends on inner joins loops
    ** might be selected even when there exists an optimal index that has
    ** no such dependency.
    */
    if( nRow>2 && cost<=pCost->rCost ){
      int k;                       /* Loop counter */
      int nSkipEq = nEq;           /* Number of == constraints to skip */
      int nSkipRange = nBound;     /* Number of < constraints to skip */
      Bitmask thisTab;             /* Bitmap for pSrc */

      thisTab = getMask(pWC->pMaskSet, iCur);
      for(pTerm=pWC->a, k=pWC->nTerm; nRow>2 && k; k--, pTerm++){
        if( pTerm->wtFlags & TERM_VIRTUAL ) continue;
        if( (pTerm->prereqAll & notValid)!=thisTab ) continue;
        if( pTerm->eOperator & (WO_EQ|WO_IN|WO_ISNULL) ){
          if( nSkipEq ){
            /* Ignore the first nEq equality matches since the index
            ** has already accounted for these */
            nSkipEq--;
          }else{
            /* Assume each additional equality match reduces the result
            ** set size by a factor of 10 */
            nRow /= 10;
          }
        }else if( pTerm->eOperator & (WO_LT|WO_LE|WO_GT|WO_GE) ){
          if( nSkipRange ){
            /* Ignore the first nSkipRange range constraints since the index
            ** has already accounted for these */
            nSkipRange--;
          }else{
            /* Assume each additional range constraint reduces the result
            ** set size by a factor of 3.  Indexed range constraints reduce
            ** the search space by a larger factor: 4.  We make indexed range
            ** more selective intentionally because of the subjective 
            ** observation that indexed range constraints really are more
            ** selective in practice, on average. */
            nRow /= 3;
          }
        }else if( pTerm->eOperator!=WO_NOOP ){
          /* Any other expression lowers the output row count by half */
          nRow /= 2;
        }
      }
      if( nRow<2 ) nRow = 2;
    }


    WHERETRACE((
      "%s(%s): nEq=%d nInMul=%d estBound=%d bSort=%d bLookup=%d wsFlags=0x%x\n"
      "         notReady=0x%llx log10N=%.1f nRow=%.1f cost=%.1f used=0x%llx\n",
      pSrc->pTab->zName, (pIdx ? pIdx->zName : "ipk"), 
      nEq, nInMul, estBound, bSort, bLookup, wsFlags,
      notReady, log10N, nRow, cost, used
    ));

    /* If this index is the best we have seen so far, then record this
    ** index and its cost in the pCost structure.
    */
    if( (!pIdx || wsFlags)
     && (cost<pCost->rCost || (cost<=pCost->rCost && nRow<pCost->plan.nRow))
    ){
      pCost->rCost = cost;
      pCost->used = used;
      pCost->plan.nRow = nRow;
      pCost->plan.wsFlags = (wsFlags&wsFlagMask);
      pCost->plan.nEq = nEq;
      pCost->plan.u.pIdx = pIdx;
    }

    /* If there was an INDEXED BY clause, then only that one index is
    ** considered. */
    if( pSrc->pIndex ) break;

    /* Reset masks for the next index in the loop */
    wsFlagMask = ~(WHERE_ROWID_EQ|WHERE_ROWID_RANGE);
    eqTermMask = idxEqTermMask;
  }

  /* If there is no ORDER BY clause and the SQLITE_ReverseOrder flag
  ** is set, then reverse the order that the index will be scanned
  ** in. This is used for application testing, to help find cases
  ** where application behaviour depends on the (undefined) order that
  ** SQLite outputs rows in in the absence of an ORDER BY clause.  */
  if( !pOrderBy && pParse->db->flags & SQLITE_ReverseOrder ){
    pCost->plan.wsFlags |= WHERE_REVERSE;
  }

  assert( pOrderBy || (pCost->plan.wsFlags&WHERE_ORDERBY)==0 );
  assert( pCost->plan.u.pIdx==0 || (pCost->plan.wsFlags&WHERE_ROWID_EQ)==0 );
  assert( pSrc->pIndex==0 
       || pCost->plan.u.pIdx==0 
       || pCost->plan.u.pIdx==pSrc->pIndex 
  );

  WHERETRACE(("best index is: %s\n", 
    ((pCost->plan.wsFlags & WHERE_NOT_FULLSCAN)==0 ? "none" : 
         pCost->plan.u.pIdx ? pCost->plan.u.pIdx->zName : "ipk")
  ));
  
  bestOrClauseIndex(pParse, pWC, pSrc, notReady, notValid, pOrderBy, pCost);
  bestAutomaticIndex(pParse, pWC, pSrc, notReady, pCost);
  pCost->plan.wsFlags |= eqTermMask;
}