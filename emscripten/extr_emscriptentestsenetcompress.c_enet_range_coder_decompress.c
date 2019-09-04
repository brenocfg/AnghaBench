#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  enet_uint8 ;
typedef  int /*<<< orphan*/  enet_uint32 ;
typedef  size_t enet_uint16 ;
struct TYPE_12__ {TYPE_1__* symbols; } ;
struct TYPE_11__ {size_t parent; scalar_t__ escapes; size_t total; } ;
typedef  TYPE_1__ ENetSymbol ;
typedef  TYPE_2__ ENetRangeCoder ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_CONTEXT_CREATE (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENET_CONTEXT_ENCODE (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,size_t,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENET_CONTEXT_ESCAPE_MINIMUM ; 
 int /*<<< orphan*/  ENET_CONTEXT_NOT_EXCLUDED ; 
 int /*<<< orphan*/  ENET_CONTEXT_RESCALE (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ENET_CONTEXT_ROOT_DECODE (TYPE_1__*,TYPE_1__*,size_t,int /*<<< orphan*/ ,size_t,size_t,int,int,int /*<<< orphan*/ ) ; 
 int ENET_CONTEXT_SYMBOL_DELTA ; 
 int ENET_CONTEXT_SYMBOL_MINIMUM ; 
 int /*<<< orphan*/  ENET_CONTEXT_TRY_DECODE (TYPE_1__*,TYPE_1__*,size_t,int /*<<< orphan*/ ,size_t,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENET_RANGE_CODER_BOTTOM ; 
 int /*<<< orphan*/  ENET_RANGE_CODER_DECODE (size_t,size_t,size_t) ; 
 int /*<<< orphan*/  ENET_RANGE_CODER_FREE_SYMBOLS ; 
 int /*<<< orphan*/  ENET_RANGE_CODER_OUTPUT (int /*<<< orphan*/ ) ; 
 size_t ENET_RANGE_CODER_READ (size_t) ; 
 int /*<<< orphan*/  ENET_RANGE_CODER_SEED ; 
 int ENET_SUBCONTEXT_ESCAPE_DELTA ; 
 size_t ENET_SUBCONTEXT_ORDER ; 
 int ENET_SUBCONTEXT_SYMBOL_DELTA ; 

size_t
enet_range_coder_decompress (void * context, const enet_uint8 * inData, size_t inLimit, enet_uint8 * outData, size_t outLimit)
{
    ENetRangeCoder * rangeCoder = (ENetRangeCoder *) context;
    enet_uint8 * outStart = outData, * outEnd = & outData [outLimit];
    const enet_uint8 * inEnd = & inData [inLimit];
    enet_uint32 decodeLow = 0, decodeCode = 0, decodeRange = ~0;
    ENetSymbol * root;
    enet_uint16 predicted = 0;
    size_t order = 0, nextSymbol = 0;
#ifdef ENET_CONTEXT_EXCLUSION
    ENetExclude excludes [256];
    ENetExclude * nextExclude = excludes;
#endif
  
    if (rangeCoder == NULL || inLimit <= 0)
      return 0;

    ENET_CONTEXT_CREATE (root, ENET_CONTEXT_ESCAPE_MINIMUM, ENET_CONTEXT_SYMBOL_MINIMUM);

    ENET_RANGE_CODER_SEED;

    for (;;)
    {
        ENetSymbol * subcontext, * symbol, * patch;
#ifdef ENET_CONTEXT_EXCLUSION
        const ENetSymbol * childContext = & emptyContext;
#endif
        enet_uint8 value = 0;
        enet_uint16 code, under, count, bottom, * parent = & predicted, total;

        for (subcontext = & rangeCoder -> symbols [predicted];
             subcontext != root;
#ifdef ENET_CONTEXT_EXCLUSION
             childContext = subcontext, 
#endif
                subcontext = & rangeCoder -> symbols [subcontext -> parent])
        {
            if (subcontext -> escapes <= 0)
              continue;
            total = subcontext -> total;
#ifdef ENET_CONTEXT_EXCLUSION
            if (childContext -> total > 0) 
              ENET_CONTEXT_DECODE_EXCLUDE (childContext, total, 0); 
#endif
            if (subcontext -> escapes >= total)
              continue;
            code = ENET_RANGE_CODER_READ (total);
            if (code < subcontext -> escapes) 
            {
                ENET_RANGE_CODER_DECODE (0, subcontext -> escapes, total); 
                continue;
            }
            code -= subcontext -> escapes;
#ifdef ENET_CONTEXT_EXCLUSION
            if (childContext -> total > 0)
            {
                ENET_CONTEXT_TRY_DECODE (subcontext, symbol, code, value, under, count, ENET_SUBCONTEXT_SYMBOL_DELTA, 0, ENET_CONTEXT_EXCLUDED); 
            }
            else
#endif
            {
                ENET_CONTEXT_TRY_DECODE (subcontext, symbol, code, value, under, count, ENET_SUBCONTEXT_SYMBOL_DELTA, 0, ENET_CONTEXT_NOT_EXCLUDED); 
            }
            bottom = symbol - rangeCoder -> symbols;
            ENET_RANGE_CODER_DECODE (subcontext -> escapes + under, count, total);
            subcontext -> total += ENET_SUBCONTEXT_SYMBOL_DELTA;
            if (count > 0xFF - 2*ENET_SUBCONTEXT_SYMBOL_DELTA || subcontext -> total > ENET_RANGE_CODER_BOTTOM - 0x100)
              ENET_CONTEXT_RESCALE (subcontext, 0);
            goto patchContexts;
        }

        total = root -> total;
#ifdef ENET_CONTEXT_EXCLUSION
        if (childContext -> total > 0)
          ENET_CONTEXT_DECODE_EXCLUDE (childContext, total, ENET_CONTEXT_SYMBOL_MINIMUM);  
#endif
        code = ENET_RANGE_CODER_READ (total);
        if (code < root -> escapes)
        {
            ENET_RANGE_CODER_DECODE (0, root -> escapes, total);
            break;
        }
        code -= root -> escapes;
#ifdef ENET_CONTEXT_EXCLUSION
        if (childContext -> total > 0)
        {
            ENET_CONTEXT_ROOT_DECODE (root, symbol, code, value, under, count, ENET_CONTEXT_SYMBOL_DELTA, ENET_CONTEXT_SYMBOL_MINIMUM, ENET_CONTEXT_EXCLUDED); 
        }
        else
#endif
        {
            ENET_CONTEXT_ROOT_DECODE (root, symbol, code, value, under, count, ENET_CONTEXT_SYMBOL_DELTA, ENET_CONTEXT_SYMBOL_MINIMUM, ENET_CONTEXT_NOT_EXCLUDED); 
        }
        bottom = symbol - rangeCoder -> symbols;
        ENET_RANGE_CODER_DECODE (root -> escapes + under, count, total);
        root -> total += ENET_CONTEXT_SYMBOL_DELTA;
        if (count > 0xFF - 2*ENET_CONTEXT_SYMBOL_DELTA + ENET_CONTEXT_SYMBOL_MINIMUM || root -> total > ENET_RANGE_CODER_BOTTOM - 0x100)
          ENET_CONTEXT_RESCALE (root, ENET_CONTEXT_SYMBOL_MINIMUM);

    patchContexts:
        for (patch = & rangeCoder -> symbols [predicted];
             patch != subcontext;
             patch = & rangeCoder -> symbols [patch -> parent])
        {
            ENET_CONTEXT_ENCODE (patch, symbol, value, under, count, ENET_SUBCONTEXT_SYMBOL_DELTA, 0);
            * parent = symbol - rangeCoder -> symbols;
            parent = & symbol -> parent;
            if (count <= 0)
            {
                patch -> escapes += ENET_SUBCONTEXT_ESCAPE_DELTA;
                patch -> total += ENET_SUBCONTEXT_ESCAPE_DELTA;
            }
            patch -> total += ENET_SUBCONTEXT_SYMBOL_DELTA; 
            if (count > 0xFF - 2*ENET_SUBCONTEXT_SYMBOL_DELTA || patch -> total > ENET_RANGE_CODER_BOTTOM - 0x100)
              ENET_CONTEXT_RESCALE (patch, 0);
        }
        * parent = bottom;

        ENET_RANGE_CODER_OUTPUT (value);

        if (order >= ENET_SUBCONTEXT_ORDER)
          predicted = rangeCoder -> symbols [predicted].parent;
        else
          order ++;
        ENET_RANGE_CODER_FREE_SYMBOLS;
    }
                        
    return (size_t) (outData - outStart);
}