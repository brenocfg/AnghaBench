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
typedef  scalar_t__ blockType_e ;
struct TYPE_3__ {int lastBlock; scalar_t__ blockType; int origSize; } ;
typedef  TYPE_1__ blockProperties_t ;
typedef  int U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int MEM_readLE24 (void const*) ; 
 size_t ZSTD_blockHeaderSize ; 
 scalar_t__ bt_reserved ; 
 scalar_t__ bt_rle ; 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t ZSTD_getcBlockSize(const void* src, size_t srcSize,
                          blockProperties_t* bpPtr)
{
    if (srcSize < ZSTD_blockHeaderSize) return ERROR(srcSize_wrong);
    {   U32 const cBlockHeader = MEM_readLE24(src);
        U32 const cSize = cBlockHeader >> 3;
        bpPtr->lastBlock = cBlockHeader & 1;
        bpPtr->blockType = (blockType_e)((cBlockHeader >> 1) & 3);
        bpPtr->origSize = cSize;   /* only useful for RLE */
        if (bpPtr->blockType == bt_rle) return 1;
        if (bpPtr->blockType == bt_reserved) return ERROR(corruption_detected);
        return cSize;
    }
}