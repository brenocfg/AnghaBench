#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t offset; size_t litLength; size_t matchLength; } ;
typedef  TYPE_1__ seq_t ;
struct TYPE_6__ {size_t prevOffset; int /*<<< orphan*/  const* dumps; int /*<<< orphan*/  DStream; int /*<<< orphan*/  stateML; int /*<<< orphan*/  stateOffb; int /*<<< orphan*/  stateLL; int /*<<< orphan*/  const* dumpsEnd; } ;
typedef  TYPE_2__ seqState_t ;
typedef  int /*<<< orphan*/  offset ;
typedef  int U32 ;
typedef  int /*<<< orphan*/  const BYTE ;

/* Variables and functions */
 void* FSE_decodeSymbol (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t FSE_readBits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FSE_reloadDStream (int /*<<< orphan*/ *) ; 
 scalar_t__ MINMATCH ; 
 size_t MaxLL ; 
 size_t MaxML ; 
 scalar_t__ ZSTD_32bits () ; 
 int ZSTD_readLE32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void ZSTD_decodeSequence(seq_t* seq, seqState_t* seqState)
{
    size_t litLength;
    size_t prevOffset;
    size_t offset;
    size_t matchLength;
    const BYTE* dumps = seqState->dumps;
    const BYTE* const de = seqState->dumpsEnd;

    /* Literal length */
    litLength = FSE_decodeSymbol(&(seqState->stateLL), &(seqState->DStream));
    prevOffset = litLength ? seq->offset : seqState->prevOffset;
    seqState->prevOffset = seq->offset;
    if (litLength == MaxLL)
    {
        U32 add = dumps<de ? *dumps++ : 0;
        if (add < 255) litLength += add;
        else
        {
            if (dumps<=(de-3))
            {
                litLength = ZSTD_readLE32(dumps) & 0xFFFFFF;  /* no pb : dumps is always followed by seq tables > 1 byte */
                dumps += 3;
            }
        }
    }

    /* Offset */
    {
        U32 offsetCode, nbBits;
        offsetCode = FSE_decodeSymbol(&(seqState->stateOffb), &(seqState->DStream));
        if (ZSTD_32bits()) FSE_reloadDStream(&(seqState->DStream));
        nbBits = offsetCode - 1;
        if (offsetCode==0) nbBits = 0;   /* cmove */
        offset = ((size_t)1 << (nbBits & ((sizeof(offset)*8)-1))) + FSE_readBits(&(seqState->DStream), nbBits);
        if (ZSTD_32bits()) FSE_reloadDStream(&(seqState->DStream));
        if (offsetCode==0) offset = prevOffset;
    }

    /* MatchLength */
    matchLength = FSE_decodeSymbol(&(seqState->stateML), &(seqState->DStream));
    if (matchLength == MaxML)
    {
        U32 add = dumps<de ? *dumps++ : 0;
        if (add < 255) matchLength += add;
        else
        {
            if (dumps<=(de-3))
            {
                matchLength = ZSTD_readLE32(dumps) & 0xFFFFFF;  /* no pb : dumps is always followed by seq tables > 1 byte */
                dumps += 3;
            }
        }
    }
    matchLength += MINMATCH;

    /* save result */
    seq->litLength = litLength;
    seq->offset = offset;
    seq->matchLength = matchLength;
    seqState->dumps = dumps;
}