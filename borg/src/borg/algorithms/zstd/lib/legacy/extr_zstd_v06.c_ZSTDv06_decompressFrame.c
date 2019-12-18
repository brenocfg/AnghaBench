#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int member_0; int blockType; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ blockProperties_t ;
typedef  int /*<<< orphan*/  ZSTDv06_DCtx ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 size_t ZSTDv06_blockHeaderSize ; 
 size_t ZSTDv06_copyRawBlock (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,size_t const) ; 
 scalar_t__ ZSTDv06_decodeFrameHeader (int /*<<< orphan*/ *,void const*,size_t const) ; 
 size_t ZSTDv06_decompressBlock_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,size_t const) ; 
 size_t ZSTDv06_frameHeaderSize (void const*,size_t) ; 
 size_t ZSTDv06_frameHeaderSize_min ; 
 size_t ZSTDv06_getcBlockSize (int /*<<< orphan*/  const*,int,TYPE_1__*) ; 
 scalar_t__ ZSTDv06_isError (size_t const) ; 
#define  bt_compressed 131 
#define  bt_end 130 
#define  bt_raw 129 
#define  bt_rle 128 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTDv06_decompressFrame(ZSTDv06_DCtx* dctx,
                                 void* dst, size_t dstCapacity,
                                 const void* src, size_t srcSize)
{
    const BYTE* ip = (const BYTE*)src;
    const BYTE* const iend = ip + srcSize;
    BYTE* const ostart = (BYTE* const)dst;
    BYTE* op = ostart;
    BYTE* const oend = ostart + dstCapacity;
    size_t remainingSize = srcSize;
    blockProperties_t blockProperties = { bt_compressed, 0 };

    /* check */
    if (srcSize < ZSTDv06_frameHeaderSize_min+ZSTDv06_blockHeaderSize) return ERROR(srcSize_wrong);

    /* Frame Header */
    {   size_t const frameHeaderSize = ZSTDv06_frameHeaderSize(src, ZSTDv06_frameHeaderSize_min);
        if (ZSTDv06_isError(frameHeaderSize)) return frameHeaderSize;
        if (srcSize < frameHeaderSize+ZSTDv06_blockHeaderSize) return ERROR(srcSize_wrong);
        if (ZSTDv06_decodeFrameHeader(dctx, src, frameHeaderSize)) return ERROR(corruption_detected);
        ip += frameHeaderSize; remainingSize -= frameHeaderSize;
    }

    /* Loop on each block */
    while (1) {
        size_t decodedSize=0;
        size_t const cBlockSize = ZSTDv06_getcBlockSize(ip, iend-ip, &blockProperties);
        if (ZSTDv06_isError(cBlockSize)) return cBlockSize;

        ip += ZSTDv06_blockHeaderSize;
        remainingSize -= ZSTDv06_blockHeaderSize;
        if (cBlockSize > remainingSize) return ERROR(srcSize_wrong);

        switch(blockProperties.blockType)
        {
        case bt_compressed:
            decodedSize = ZSTDv06_decompressBlock_internal(dctx, op, oend-op, ip, cBlockSize);
            break;
        case bt_raw :
            decodedSize = ZSTDv06_copyRawBlock(op, oend-op, ip, cBlockSize);
            break;
        case bt_rle :
            return ERROR(GENERIC);   /* not yet supported */
            break;
        case bt_end :
            /* end of frame */
            if (remainingSize) return ERROR(srcSize_wrong);
            break;
        default:
            return ERROR(GENERIC);   /* impossible */
        }
        if (cBlockSize == 0) break;   /* bt_end */

        if (ZSTDv06_isError(decodedSize)) return decodedSize;
        op += decodedSize;
        ip += cBlockSize;
        remainingSize -= cBlockSize;
    }

    return op-ostart;
}