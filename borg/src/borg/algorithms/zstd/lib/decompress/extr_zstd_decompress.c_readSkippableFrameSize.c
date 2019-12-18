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
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_readLE32 (int /*<<< orphan*/  const*) ; 
 int ZSTD_FRAMEIDSIZE ; 
 size_t ZSTD_SKIPPABLEHEADERSIZE ; 
 int /*<<< orphan*/  frameParameter_unsupported ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t readSkippableFrameSize(void const* src, size_t srcSize)
{
    size_t const skippableHeaderSize = ZSTD_SKIPPABLEHEADERSIZE;
    U32 sizeU32;

    if (srcSize < ZSTD_SKIPPABLEHEADERSIZE)
        return ERROR(srcSize_wrong);

    sizeU32 = MEM_readLE32((BYTE const*)src + ZSTD_FRAMEIDSIZE);
    if ((U32)(sizeU32 + ZSTD_SKIPPABLEHEADERSIZE) < sizeU32)
        return ERROR(frameParameter_unsupported);

    return skippableHeaderSize + sizeU32;
}