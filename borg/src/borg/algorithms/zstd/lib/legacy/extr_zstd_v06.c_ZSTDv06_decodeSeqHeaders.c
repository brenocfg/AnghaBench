#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int U32 ;
typedef  int /*<<< orphan*/  FSEv06_DTable ;
typedef  int BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLFSELog ; 
 int /*<<< orphan*/  LL_defaultNorm ; 
 int /*<<< orphan*/  LL_defaultNormLog ; 
 int LONGNBSEQ ; 
 int MEM_readLE16 (int const*) ; 
 size_t MIN_SEQUENCES_SIZE ; 
 int /*<<< orphan*/  MLFSELog ; 
 int /*<<< orphan*/  ML_defaultNorm ; 
 int /*<<< orphan*/  ML_defaultNormLog ; 
 int /*<<< orphan*/  MaxLL ; 
 int /*<<< orphan*/  MaxML ; 
 int /*<<< orphan*/  MaxOff ; 
 int /*<<< orphan*/  OF_defaultNorm ; 
 int /*<<< orphan*/  OF_defaultNormLog ; 
 int /*<<< orphan*/  OffFSELog ; 
 size_t ZSTDv06_buildSeqTable (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ZSTDv06_isError (size_t const) ; 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTDv06_decodeSeqHeaders(int* nbSeqPtr,
                             FSEv06_DTable* DTableLL, FSEv06_DTable* DTableML, FSEv06_DTable* DTableOffb, U32 flagRepeatTable,
                             const void* src, size_t srcSize)
{
    const BYTE* const istart = (const BYTE* const)src;
    const BYTE* const iend = istart + srcSize;
    const BYTE* ip = istart;

    /* check */
    if (srcSize < MIN_SEQUENCES_SIZE) return ERROR(srcSize_wrong);

    /* SeqHead */
    {   int nbSeq = *ip++;
        if (!nbSeq) { *nbSeqPtr=0; return 1; }
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
    }

    /* FSE table descriptors */
    {   U32 const LLtype  = *ip >> 6;
        U32 const Offtype = (*ip >> 4) & 3;
        U32 const MLtype  = (*ip >> 2) & 3;
        ip++;

        /* check */
        if (ip > iend-3) return ERROR(srcSize_wrong); /* min : all 3 are "raw", hence no header, but at least xxLog bits per type */

        /* Build DTables */
        {   size_t const bhSize = ZSTDv06_buildSeqTable(DTableLL, LLtype, MaxLL, LLFSELog, ip, iend-ip, LL_defaultNorm, LL_defaultNormLog, flagRepeatTable);
            if (ZSTDv06_isError(bhSize)) return ERROR(corruption_detected);
            ip += bhSize;
        }
        {   size_t const bhSize = ZSTDv06_buildSeqTable(DTableOffb, Offtype, MaxOff, OffFSELog, ip, iend-ip, OF_defaultNorm, OF_defaultNormLog, flagRepeatTable);
            if (ZSTDv06_isError(bhSize)) return ERROR(corruption_detected);
            ip += bhSize;
        }
        {   size_t const bhSize = ZSTDv06_buildSeqTable(DTableML, MLtype, MaxML, MLFSELog, ip, iend-ip, ML_defaultNorm, ML_defaultNormLog, flagRepeatTable);
            if (ZSTDv06_isError(bhSize)) return ERROR(corruption_detected);
            ip += bhSize;
    }   }

    return ip-istart;
}