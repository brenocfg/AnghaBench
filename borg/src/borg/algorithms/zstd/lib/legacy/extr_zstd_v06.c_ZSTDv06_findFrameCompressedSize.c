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
struct TYPE_3__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ blockProperties_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_readLE32 (void const*) ; 
 scalar_t__ ZSTDv06_MAGICNUMBER ; 
 size_t const ZSTDv06_blockHeaderSize ; 
 size_t ZSTDv06_frameHeaderSize (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDv06_frameHeaderSize_min ; 
 size_t ZSTDv06_getcBlockSize (int /*<<< orphan*/  const*,size_t,TYPE_1__*) ; 
 scalar_t__ ZSTDv06_isError (size_t const) ; 
 int /*<<< orphan*/  bt_compressed ; 
 int /*<<< orphan*/  prefix_unknown ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t ZSTDv06_findFrameCompressedSize(const void* src, size_t srcSize)
{
    const BYTE* ip = (const BYTE*)src;
    size_t remainingSize = srcSize;
    blockProperties_t blockProperties = { bt_compressed, 0 };

    /* Frame Header */
    {   size_t const frameHeaderSize = ZSTDv06_frameHeaderSize(src, ZSTDv06_frameHeaderSize_min);
        if (ZSTDv06_isError(frameHeaderSize)) return frameHeaderSize;
        if (MEM_readLE32(src) != ZSTDv06_MAGICNUMBER) return ERROR(prefix_unknown);
        if (srcSize < frameHeaderSize+ZSTDv06_blockHeaderSize) return ERROR(srcSize_wrong);
        ip += frameHeaderSize; remainingSize -= frameHeaderSize;
    }

    /* Loop on each block */
    while (1) {
        size_t const cBlockSize = ZSTDv06_getcBlockSize(ip, remainingSize, &blockProperties);
        if (ZSTDv06_isError(cBlockSize)) return cBlockSize;

        ip += ZSTDv06_blockHeaderSize;
        remainingSize -= ZSTDv06_blockHeaderSize;
        if (cBlockSize > remainingSize) return ERROR(srcSize_wrong);

        if (cBlockSize == 0) break;   /* bt_end */

        ip += cBlockSize;
        remainingSize -= cBlockSize;
    }

    return ip - (const BYTE*)src;
}