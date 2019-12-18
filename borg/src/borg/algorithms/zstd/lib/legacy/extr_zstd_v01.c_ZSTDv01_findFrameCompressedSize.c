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
typedef  int /*<<< orphan*/  blockProperties_t ;
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTD_blockHeaderSize ; 
 size_t ZSTD_frameHeaderSize ; 
 scalar_t__ ZSTD_magicNumber ; 
 scalar_t__ ZSTD_readBE32 (void const*) ; 
 size_t ZSTDv01_getcBlockSize (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTDv01_isError (size_t) ; 
 int /*<<< orphan*/  prefix_unknown ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t ZSTDv01_findFrameCompressedSize(const void* src, size_t srcSize)
{
    const BYTE* ip = (const BYTE*)src;
    size_t remainingSize = srcSize;
    U32 magicNumber;
    blockProperties_t blockProperties;

    /* Frame Header */
    if (srcSize < ZSTD_frameHeaderSize+ZSTD_blockHeaderSize) return ERROR(srcSize_wrong);
    magicNumber = ZSTD_readBE32(src);
    if (magicNumber != ZSTD_magicNumber) return ERROR(prefix_unknown);
    ip += ZSTD_frameHeaderSize; remainingSize -= ZSTD_frameHeaderSize;

    /* Loop on each block */
    while (1)
    {
        size_t blockSize = ZSTDv01_getcBlockSize(ip, remainingSize, &blockProperties);
        if (ZSTDv01_isError(blockSize)) return blockSize;

        ip += ZSTD_blockHeaderSize;
        remainingSize -= ZSTD_blockHeaderSize;
        if (blockSize > remainingSize) return ERROR(srcSize_wrong);

        if (blockSize == 0) break;   /* bt_end */

        ip += blockSize;
        remainingSize -= blockSize;
    }

    return ip - (const BYTE*)src;
}