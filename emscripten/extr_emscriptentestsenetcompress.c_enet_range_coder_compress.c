#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  enet_uint8 ;
typedef  int /*<<< orphan*/  enet_uint32 ;
typedef  size_t enet_uint16 ;
struct TYPE_11__ {size_t dataLength; scalar_t__ data; } ;
struct TYPE_10__ {TYPE_1__* symbols; } ;
struct TYPE_9__ {size_t parent; size_t total; size_t escapes; } ;
typedef  TYPE_1__ ENetSymbol ;
typedef  TYPE_2__ ENetRangeCoder ;
typedef  TYPE_3__ ENetBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_CONTEXT_CREATE (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENET_CONTEXT_ENCODE (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,size_t,size_t,int,int) ; 
 int /*<<< orphan*/  ENET_CONTEXT_ESCAPE_MINIMUM ; 
 int /*<<< orphan*/  ENET_CONTEXT_RESCALE (TYPE_1__*,int) ; 
 int ENET_CONTEXT_SYMBOL_DELTA ; 
 int ENET_CONTEXT_SYMBOL_MINIMUM ; 
 int ENET_RANGE_CODER_BOTTOM ; 
 int /*<<< orphan*/  ENET_RANGE_CODER_ENCODE (size_t,size_t,size_t) ; 
 int /*<<< orphan*/  ENET_RANGE_CODER_FLUSH ; 
 int /*<<< orphan*/  ENET_RANGE_CODER_FREE_SYMBOLS ; 
 size_t ENET_SUBCONTEXT_ESCAPE_DELTA ; 
 size_t ENET_SUBCONTEXT_ORDER ; 
 int ENET_SUBCONTEXT_SYMBOL_DELTA ; 

size_t
enet_range_coder_compress (void * context, const ENetBuffer * inBuffers, size_t inBufferCount, size_t inLimit, enet_uint8 * outData, size_t outLimit)
{
    ENetRangeCoder * rangeCoder = (ENetRangeCoder *) context;
    enet_uint8 * outStart = outData, * outEnd = & outData [outLimit];
    const enet_uint8 * inData, * inEnd;
    enet_uint32 encodeLow = 0, encodeRange = ~0;
    ENetSymbol * root;
    enet_uint16 predicted = 0;
    size_t order = 0, nextSymbol = 0;

    if (rangeCoder == NULL || inBufferCount <= 0 || inLimit <= 0)
      return 0;

    inData = (const enet_uint8 *) inBuffers -> data;
    inEnd = & inData [inBuffers -> dataLength];
    inBuffers ++;
    inBufferCount --;

    ENET_CONTEXT_CREATE (root, ENET_CONTEXT_ESCAPE_MINIMUM, ENET_CONTEXT_SYMBOL_MINIMUM);

    for (;;)
    {
        ENetSymbol * subcontext, * symbol;
#ifdef ENET_CONTEXT_EXCLUSION
        const ENetSymbol * childContext = & emptyContext;
#endif
        enet_uint8 value;
        enet_uint16 count, under, * parent = & predicted, total;
        if (inData >= inEnd)
        {
            if (inBufferCount <= 0)
              break;
            inData = (const enet_uint8 *) inBuffers -> data;
            inEnd = & inData [inBuffers -> dataLength];
            inBuffers ++;
            inBufferCount --;
        }
        value = * inData ++;
    
        for (subcontext = & rangeCoder -> symbols [predicted]; 
             subcontext != root; 
#ifdef ENET_CONTEXT_EXCLUSION
             childContext = subcontext, 
#endif
                subcontext = & rangeCoder -> symbols [subcontext -> parent])
        {
            ENET_CONTEXT_ENCODE (subcontext, symbol, value, under, count, ENET_SUBCONTEXT_SYMBOL_DELTA, 0);
            * parent = symbol - rangeCoder -> symbols;
            parent = & symbol -> parent;
            total = subcontext -> total;
#ifdef ENET_CONTEXT_EXCLUSION
            if (childContext -> total > ENET_SUBCONTEXT_SYMBOL_DELTA + ENET_SUBCONTEXT_ESCAPE_DELTA)
              ENET_CONTEXT_ENCODE_EXCLUDE (childContext, value, under, total, 0);
#endif
            if (count > 0)
            {
                ENET_RANGE_CODER_ENCODE (subcontext -> escapes + under, count, total);
            }
            else
            {
                if (subcontext -> escapes > 0 && subcontext -> escapes < total) 
                    ENET_RANGE_CODER_ENCODE (0, subcontext -> escapes, total); 
                subcontext -> escapes += ENET_SUBCONTEXT_ESCAPE_DELTA;
                subcontext -> total += ENET_SUBCONTEXT_ESCAPE_DELTA;
            }
            subcontext -> total += ENET_SUBCONTEXT_SYMBOL_DELTA;
            if (count > 0xFF - 2*ENET_SUBCONTEXT_SYMBOL_DELTA || subcontext -> total > ENET_RANGE_CODER_BOTTOM - 0x100)
              ENET_CONTEXT_RESCALE (subcontext, 0);
            if (count > 0) goto nextInput;
        }

        ENET_CONTEXT_ENCODE (root, symbol, value, under, count, ENET_CONTEXT_SYMBOL_DELTA, ENET_CONTEXT_SYMBOL_MINIMUM);
        * parent = symbol - rangeCoder -> symbols;
        parent = & symbol -> parent;
        total = root -> total;
#ifdef ENET_CONTEXT_EXCLUSION
        if (childContext -> total > ENET_SUBCONTEXT_SYMBOL_DELTA + ENET_SUBCONTEXT_ESCAPE_DELTA)
          ENET_CONTEXT_ENCODE_EXCLUDE (childContext, value, under, total, ENET_CONTEXT_SYMBOL_MINIMUM); 
#endif
        ENET_RANGE_CODER_ENCODE (root -> escapes + under, count, total);
        root -> total += ENET_CONTEXT_SYMBOL_DELTA; 
        if (count > 0xFF - 2*ENET_CONTEXT_SYMBOL_DELTA + ENET_CONTEXT_SYMBOL_MINIMUM || root -> total > ENET_RANGE_CODER_BOTTOM - 0x100)
          ENET_CONTEXT_RESCALE (root, ENET_CONTEXT_SYMBOL_MINIMUM);

    nextInput:
        if (order >= ENET_SUBCONTEXT_ORDER) 
          predicted = rangeCoder -> symbols [predicted].parent;
        else 
          order ++;
        ENET_RANGE_CODER_FREE_SYMBOLS;
    }

    ENET_RANGE_CODER_FLUSH;

    return (size_t) (outData - outStart);
}