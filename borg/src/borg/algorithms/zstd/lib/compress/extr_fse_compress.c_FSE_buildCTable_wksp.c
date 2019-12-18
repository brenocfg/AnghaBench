#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
typedef  scalar_t__ U16 ;
struct TYPE_4__ {unsigned int deltaNbBits; unsigned int deltaFindState; } ;
typedef  TYPE_1__ FSE_symbolCompressionTransform ;
typedef  size_t FSE_FUNCTION_TYPE ;
typedef  int /*<<< orphan*/  FSE_CTable ;

/* Variables and functions */
 unsigned int BIT_highbit32 (short const) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSE_MAX_SYMBOL_VALUE ; 
 int FSE_TABLESTEP (int const) ; 
 scalar_t__ FSE_bitCost (TYPE_1__* const,unsigned int,int,int) ; 
 int /*<<< orphan*/  FSE_getMaxNbBits (TYPE_1__* const,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (size_t* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tableLog_tooLarge ; 

size_t FSE_buildCTable_wksp(FSE_CTable* ct,
                      const short* normalizedCounter, unsigned maxSymbolValue, unsigned tableLog,
                            void* workSpace, size_t wkspSize)
{
    U32 const tableSize = 1 << tableLog;
    U32 const tableMask = tableSize - 1;
    void* const ptr = ct;
    U16* const tableU16 = ( (U16*) ptr) + 2;
    void* const FSCT = ((U32*)ptr) + 1 /* header */ + (tableLog ? tableSize>>1 : 1) ;
    FSE_symbolCompressionTransform* const symbolTT = (FSE_symbolCompressionTransform*) (FSCT);
    U32 const step = FSE_TABLESTEP(tableSize);
    U32 cumul[FSE_MAX_SYMBOL_VALUE+2];

    FSE_FUNCTION_TYPE* const tableSymbol = (FSE_FUNCTION_TYPE*)workSpace;
    U32 highThreshold = tableSize-1;

    /* CTable header */
    if (((size_t)1 << tableLog) * sizeof(FSE_FUNCTION_TYPE) > wkspSize) return ERROR(tableLog_tooLarge);
    tableU16[-2] = (U16) tableLog;
    tableU16[-1] = (U16) maxSymbolValue;
    assert(tableLog < 16);   /* required for threshold strategy to work */

    /* For explanations on how to distribute symbol values over the table :
     * http://fastcompression.blogspot.fr/2014/02/fse-distributing-symbol-values.html */

     #ifdef __clang_analyzer__
     memset(tableSymbol, 0, sizeof(*tableSymbol) * tableSize);   /* useless initialization, just to keep scan-build happy */
     #endif

    /* symbol start positions */
    {   U32 u;
        cumul[0] = 0;
        for (u=1; u <= maxSymbolValue+1; u++) {
            if (normalizedCounter[u-1]==-1) {  /* Low proba symbol */
                cumul[u] = cumul[u-1] + 1;
                tableSymbol[highThreshold--] = (FSE_FUNCTION_TYPE)(u-1);
            } else {
                cumul[u] = cumul[u-1] + normalizedCounter[u-1];
        }   }
        cumul[maxSymbolValue+1] = tableSize+1;
    }

    /* Spread symbols */
    {   U32 position = 0;
        U32 symbol;
        for (symbol=0; symbol<=maxSymbolValue; symbol++) {
            int nbOccurences;
            int const freq = normalizedCounter[symbol];
            for (nbOccurences=0; nbOccurences<freq; nbOccurences++) {
                tableSymbol[position] = (FSE_FUNCTION_TYPE)symbol;
                position = (position + step) & tableMask;
                while (position > highThreshold)
                    position = (position + step) & tableMask;   /* Low proba area */
        }   }

        assert(position==0);  /* Must have initialized all positions */
    }

    /* Build table */
    {   U32 u; for (u=0; u<tableSize; u++) {
        FSE_FUNCTION_TYPE s = tableSymbol[u];   /* note : static analyzer may not understand tableSymbol is properly initialized */
        tableU16[cumul[s]++] = (U16) (tableSize+u);   /* TableU16 : sorted by symbol order; gives next state value */
    }   }

    /* Build Symbol Transformation Table */
    {   unsigned total = 0;
        unsigned s;
        for (s=0; s<=maxSymbolValue; s++) {
            switch (normalizedCounter[s])
            {
            case  0:
                /* filling nonetheless, for compatibility with FSE_getMaxNbBits() */
                symbolTT[s].deltaNbBits = ((tableLog+1) << 16) - (1<<tableLog);
                break;

            case -1:
            case  1:
                symbolTT[s].deltaNbBits = (tableLog << 16) - (1<<tableLog);
                symbolTT[s].deltaFindState = total - 1;
                total ++;
                break;
            default :
                {
                    U32 const maxBitsOut = tableLog - BIT_highbit32 (normalizedCounter[s]-1);
                    U32 const minStatePlus = normalizedCounter[s] << maxBitsOut;
                    symbolTT[s].deltaNbBits = (maxBitsOut << 16) - minStatePlus;
                    symbolTT[s].deltaFindState = total - normalizedCounter[s];
                    total +=  normalizedCounter[s];
    }   }   }   }

#if 0  /* debug : symbol costs */
    DEBUGLOG(5, "\n --- table statistics : ");
    {   U32 symbol;
        for (symbol=0; symbol<=maxSymbolValue; symbol++) {
            DEBUGLOG(5, "%3u: w=%3i,   maxBits=%u, fracBits=%.2f",
                symbol, normalizedCounter[symbol],
                FSE_getMaxNbBits(symbolTT, symbol),
                (double)FSE_bitCost(symbolTT, tableLog, symbol, 8) / 256);
        }
    }
#endif

    return 0;
}