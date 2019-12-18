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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int MEM_readLE32 (void const*) ; 
 unsigned long long ZSTD_CONTENTSIZE_ERROR ; 
 size_t ZSTD_FRAMEHEADERSIZE_PREFIX ; 
 int const ZSTD_MAGIC_SKIPPABLE_MASK ; 
 int const ZSTD_MAGIC_SKIPPABLE_START ; 
 size_t ZSTD_findFrameCompressedSize (void const*,size_t) ; 
 unsigned long long ZSTD_getFrameContentSize (void const*,size_t) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 size_t readSkippableFrameSize (void const*,size_t) ; 

unsigned long long ZSTD_findDecompressedSize(const void* src, size_t srcSize)
{
    unsigned long long totalDstSize = 0;

    while (srcSize >= ZSTD_FRAMEHEADERSIZE_PREFIX) {
        U32 const magicNumber = MEM_readLE32(src);

        if ((magicNumber & ZSTD_MAGIC_SKIPPABLE_MASK) == ZSTD_MAGIC_SKIPPABLE_START) {
            size_t const skippableSize = readSkippableFrameSize(src, srcSize);
            if (ZSTD_isError(skippableSize))
                return skippableSize;
            if (srcSize < skippableSize) {
                return ZSTD_CONTENTSIZE_ERROR;
            }

            src = (const BYTE *)src + skippableSize;
            srcSize -= skippableSize;
            continue;
        }

        {   unsigned long long const ret = ZSTD_getFrameContentSize(src, srcSize);
            if (ret >= ZSTD_CONTENTSIZE_ERROR) return ret;

            /* check for overflow */
            if (totalDstSize + ret < totalDstSize) return ZSTD_CONTENTSIZE_ERROR;
            totalDstSize += ret;
        }
        {   size_t const frameSrcSize = ZSTD_findFrameCompressedSize(src, srcSize);
            if (ZSTD_isError(frameSrcSize)) {
                return ZSTD_CONTENTSIZE_ERROR;
            }

            src = (const BYTE *)src + frameSrcSize;
            srcSize -= frameSrcSize;
        }
    }  /* while (srcSize >= ZSTD_frameHeaderSize_prefix) */

    if (srcSize) return ZSTD_CONTENTSIZE_ERROR;

    return totalDstSize;
}