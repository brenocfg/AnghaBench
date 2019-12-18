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
typedef  int /*<<< orphan*/  S16 ;
typedef  int /*<<< orphan*/  FSE_DTable ;
typedef  int BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSE_buildDTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  FSE_buildDTable_raw (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FSE_buildDTable_rle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSE_isError (size_t) ; 
 size_t FSE_readNCount (int /*<<< orphan*/ *,int*,int*,int const*,int) ; 
 int /*<<< orphan*/  GENERIC ; 
 int LLFSELog ; 
 int LLbits ; 
 int MLFSELog ; 
 int MLbits ; 
 int MaxLL ; 
 int MaxML ; 
 int MaxOff ; 
 int OffFSELog ; 
 int Offbits ; 
 int ZSTD_readLE16 (int const*) ; 
#define  bt_raw 129 
#define  bt_rle 128 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTDv01_decodeSeqHeaders(int* nbSeq, const BYTE** dumpsPtr, size_t* dumpsLengthPtr,
                         FSE_DTable* DTableLL, FSE_DTable* DTableML, FSE_DTable* DTableOffb,
                         const void* src, size_t srcSize)
{
    const BYTE* const istart = (const BYTE* const)src;
    const BYTE* ip = istart;
    const BYTE* const iend = istart + srcSize;
    U32 LLtype, Offtype, MLtype;
    U32 LLlog, Offlog, MLlog;
    size_t dumpsLength;

    /* check */
    if (srcSize < 5) return ERROR(srcSize_wrong);

    /* SeqHead */
    *nbSeq = ZSTD_readLE16(ip); ip+=2;
    LLtype  = *ip >> 6;
    Offtype = (*ip >> 4) & 3;
    MLtype  = (*ip >> 2) & 3;
    if (*ip & 2)
    {
        dumpsLength  = ip[2];
        dumpsLength += ip[1] << 8;
        ip += 3;
    }
    else
    {
        dumpsLength  = ip[1];
        dumpsLength += (ip[0] & 1) << 8;
        ip += 2;
    }
    *dumpsPtr = ip;
    ip += dumpsLength;
    *dumpsLengthPtr = dumpsLength;

    /* check */
    if (ip > iend-3) return ERROR(srcSize_wrong); /* min : all 3 are "raw", hence no header, but at least xxLog bits per type */

    /* sequences */
    {
        S16 norm[MaxML+1];    /* assumption : MaxML >= MaxLL and MaxOff */
        size_t headerSize;

        /* Build DTables */
        switch(LLtype)
        {
        case bt_rle :
            LLlog = 0;
            FSE_buildDTable_rle(DTableLL, *ip++); break;
        case bt_raw :
            LLlog = LLbits;
            FSE_buildDTable_raw(DTableLL, LLbits); break;
        default :
            {   U32 max = MaxLL;
                headerSize = FSE_readNCount(norm, &max, &LLlog, ip, iend-ip);
                if (FSE_isError(headerSize)) return ERROR(GENERIC);
                if (LLlog > LLFSELog) return ERROR(corruption_detected);
                ip += headerSize;
                FSE_buildDTable(DTableLL, norm, max, LLlog);
        }   }

        switch(Offtype)
        {
        case bt_rle :
            Offlog = 0;
            if (ip > iend-2) return ERROR(srcSize_wrong); /* min : "raw", hence no header, but at least xxLog bits */
            FSE_buildDTable_rle(DTableOffb, *ip++); break;
        case bt_raw :
            Offlog = Offbits;
            FSE_buildDTable_raw(DTableOffb, Offbits); break;
        default :
            {   U32 max = MaxOff;
                headerSize = FSE_readNCount(norm, &max, &Offlog, ip, iend-ip);
                if (FSE_isError(headerSize)) return ERROR(GENERIC);
                if (Offlog > OffFSELog) return ERROR(corruption_detected);
                ip += headerSize;
                FSE_buildDTable(DTableOffb, norm, max, Offlog);
        }   }

        switch(MLtype)
        {
        case bt_rle :
            MLlog = 0;
            if (ip > iend-2) return ERROR(srcSize_wrong); /* min : "raw", hence no header, but at least xxLog bits */
            FSE_buildDTable_rle(DTableML, *ip++); break;
        case bt_raw :
            MLlog = MLbits;
            FSE_buildDTable_raw(DTableML, MLbits); break;
        default :
            {   U32 max = MaxML;
                headerSize = FSE_readNCount(norm, &max, &MLlog, ip, iend-ip);
                if (FSE_isError(headerSize)) return ERROR(GENERIC);
                if (MLlog > MLFSELog) return ERROR(corruption_detected);
                ip += headerSize;
                FSE_buildDTable(DTableML, norm, max, MLlog);
    }   }   }

    return ip-istart;
}