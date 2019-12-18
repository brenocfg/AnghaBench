#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolEncodingType_e ;
struct TYPE_4__ {int /*<<< orphan*/  MLTable; int /*<<< orphan*/  OFTable; int /*<<< orphan*/  LLTable; } ;
struct TYPE_5__ {int /*<<< orphan*/  ddictIsCold; int /*<<< orphan*/  fseEntropy; int /*<<< orphan*/  MLTptr; TYPE_1__ entropy; int /*<<< orphan*/  OFTptr; int /*<<< orphan*/  LLTptr; } ;
typedef  TYPE_2__ ZSTD_DCtx ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLFSELog ; 
 int /*<<< orphan*/  LL_base ; 
 int /*<<< orphan*/  LL_bits ; 
 int /*<<< orphan*/  LL_defaultDTable ; 
 int LONGNBSEQ ; 
 int MEM_readLE16 (int const*) ; 
 size_t MIN_SEQUENCES_SIZE ; 
 int /*<<< orphan*/  MLFSELog ; 
 int /*<<< orphan*/  ML_base ; 
 int /*<<< orphan*/  ML_bits ; 
 int /*<<< orphan*/  ML_defaultDTable ; 
 int /*<<< orphan*/  MaxLL ; 
 int /*<<< orphan*/  MaxML ; 
 int /*<<< orphan*/  MaxOff ; 
 int /*<<< orphan*/  OF_base ; 
 int /*<<< orphan*/  OF_bits ; 
 int /*<<< orphan*/  OF_defaultDTable ; 
 int /*<<< orphan*/  OffFSELog ; 
 size_t ZSTD_buildSeqTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t ZSTD_decodeSeqHeaders(ZSTD_DCtx* dctx, int* nbSeqPtr,
                             const void* src, size_t srcSize)
{
    const BYTE* const istart = (const BYTE* const)src;
    const BYTE* const iend = istart + srcSize;
    const BYTE* ip = istart;
    int nbSeq;
    DEBUGLOG(5, "ZSTD_decodeSeqHeaders");

    /* check */
    if (srcSize < MIN_SEQUENCES_SIZE) return ERROR(srcSize_wrong);

    /* SeqHead */
    nbSeq = *ip++;
    if (!nbSeq) {
        *nbSeqPtr=0;
        if (srcSize != 1) return ERROR(srcSize_wrong);
        return 1;
    }
    if (nbSeq > 0x7F) {
        if (nbSeq == 0xFF) {
            if (ip+2 > iend) return ERROR(srcSize_wrong);
            nbSeq = MEM_readLE16(ip) + LONGNBSEQ, ip+=2;
        } else {
            if (ip >= iend) return ERROR(srcSize_wrong);
            nbSeq = ((nbSeq-0x80)<<8) + *ip++;
        }
    }
    *nbSeqPtr = nbSeq;

    /* FSE table descriptors */
    if (ip+4 > iend) return ERROR(srcSize_wrong); /* minimum possible size */
    {   symbolEncodingType_e const LLtype = (symbolEncodingType_e)(*ip >> 6);
        symbolEncodingType_e const OFtype = (symbolEncodingType_e)((*ip >> 4) & 3);
        symbolEncodingType_e const MLtype = (symbolEncodingType_e)((*ip >> 2) & 3);
        ip++;

        /* Build DTables */
        {   size_t const llhSize = ZSTD_buildSeqTable(dctx->entropy.LLTable, &dctx->LLTptr,
                                                      LLtype, MaxLL, LLFSELog,
                                                      ip, iend-ip,
                                                      LL_base, LL_bits,
                                                      LL_defaultDTable, dctx->fseEntropy,
                                                      dctx->ddictIsCold, nbSeq);
            if (ZSTD_isError(llhSize)) return ERROR(corruption_detected);
            ip += llhSize;
        }

        {   size_t const ofhSize = ZSTD_buildSeqTable(dctx->entropy.OFTable, &dctx->OFTptr,
                                                      OFtype, MaxOff, OffFSELog,
                                                      ip, iend-ip,
                                                      OF_base, OF_bits,
                                                      OF_defaultDTable, dctx->fseEntropy,
                                                      dctx->ddictIsCold, nbSeq);
            if (ZSTD_isError(ofhSize)) return ERROR(corruption_detected);
            ip += ofhSize;
        }

        {   size_t const mlhSize = ZSTD_buildSeqTable(dctx->entropy.MLTable, &dctx->MLTptr,
                                                      MLtype, MaxML, MLFSELog,
                                                      ip, iend-ip,
                                                      ML_base, ML_bits,
                                                      ML_defaultDTable, dctx->fseEntropy,
                                                      dctx->ddictIsCold, nbSeq);
            if (ZSTD_isError(mlhSize)) return ERROR(corruption_detected);
            ip += mlhSize;
        }
    }

    return ip-istart;
}