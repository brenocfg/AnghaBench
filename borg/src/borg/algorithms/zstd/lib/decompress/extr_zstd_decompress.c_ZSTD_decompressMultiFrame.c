#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_DDict ;
struct TYPE_7__ {scalar_t__ staticSize; } ;
typedef  TYPE_1__ ZSTD_DCtx ;
typedef  int U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int MEM_readLE32 (void const*) ; 
 void* ZSTD_DDict_dictContent (int /*<<< orphan*/  const*) ; 
 size_t ZSTD_DDict_dictSize (int /*<<< orphan*/  const*) ; 
 size_t ZSTD_FRAMEHEADERSIZE_PREFIX ; 
 int /*<<< orphan*/  ZSTD_MAGICNUMBER ; 
 int const ZSTD_MAGIC_SKIPPABLE_MASK ; 
 int const ZSTD_MAGIC_SKIPPABLE_START ; 
 int /*<<< orphan*/  ZSTD_checkContinuity (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  ZSTD_decompressBegin_usingDDict (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ZSTD_decompressBegin_usingDict (TYPE_1__*,void const*,size_t) ; 
 size_t ZSTD_decompressFrame (TYPE_1__*,void*,size_t,void const**,size_t*) ; 
 size_t ZSTD_decompressLegacy (void*,size_t,void const*,size_t const,void const*,size_t) ; 
 scalar_t__ ZSTD_error_prefix_unknown ; 
 size_t ZSTD_findFrameCompressedSizeLegacy (void const*,size_t) ; 
 scalar_t__ ZSTD_getErrorCode (size_t const) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 scalar_t__ ZSTD_isLegacy (void const*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memory_allocation ; 
 size_t readSkippableFrameSize (void const*,size_t) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTD_decompressMultiFrame(ZSTD_DCtx* dctx,
                                        void* dst, size_t dstCapacity,
                                  const void* src, size_t srcSize,
                                  const void* dict, size_t dictSize,
                                  const ZSTD_DDict* ddict)
{
    void* const dststart = dst;
    int moreThan1Frame = 0;

    DEBUGLOG(5, "ZSTD_decompressMultiFrame");
    assert(dict==NULL || ddict==NULL);  /* either dict or ddict set, not both */

    if (ddict) {
        dict = ZSTD_DDict_dictContent(ddict);
        dictSize = ZSTD_DDict_dictSize(ddict);
    }

    while (srcSize >= ZSTD_FRAMEHEADERSIZE_PREFIX) {

#if defined(ZSTD_LEGACY_SUPPORT) && (ZSTD_LEGACY_SUPPORT >= 1)
        if (ZSTD_isLegacy(src, srcSize)) {
            size_t decodedSize;
            size_t const frameSize = ZSTD_findFrameCompressedSizeLegacy(src, srcSize);
            if (ZSTD_isError(frameSize)) return frameSize;
            /* legacy support is not compatible with static dctx */
            if (dctx->staticSize) return ERROR(memory_allocation);

            decodedSize = ZSTD_decompressLegacy(dst, dstCapacity, src, frameSize, dict, dictSize);
            if (ZSTD_isError(decodedSize)) return decodedSize;

            assert(decodedSize <=- dstCapacity);
            dst = (BYTE*)dst + decodedSize;
            dstCapacity -= decodedSize;

            src = (const BYTE*)src + frameSize;
            srcSize -= frameSize;

            continue;
        }
#endif

        {   U32 const magicNumber = MEM_readLE32(src);
            DEBUGLOG(4, "reading magic number %08X (expecting %08X)",
                        (unsigned)magicNumber, ZSTD_MAGICNUMBER);
            if ((magicNumber & ZSTD_MAGIC_SKIPPABLE_MASK) == ZSTD_MAGIC_SKIPPABLE_START) {
                size_t const skippableSize = readSkippableFrameSize(src, srcSize);
                if (ZSTD_isError(skippableSize))
                    return skippableSize;
                if (srcSize < skippableSize) return ERROR(srcSize_wrong);

                src = (const BYTE *)src + skippableSize;
                srcSize -= skippableSize;
                continue;
        }   }

        if (ddict) {
            /* we were called from ZSTD_decompress_usingDDict */
            CHECK_F(ZSTD_decompressBegin_usingDDict(dctx, ddict));
        } else {
            /* this will initialize correctly with no dict if dict == NULL, so
             * use this in all cases but ddict */
            CHECK_F(ZSTD_decompressBegin_usingDict(dctx, dict, dictSize));
        }
        ZSTD_checkContinuity(dctx, dst);

        {   const size_t res = ZSTD_decompressFrame(dctx, dst, dstCapacity,
                                                    &src, &srcSize);
            if ( (ZSTD_getErrorCode(res) == ZSTD_error_prefix_unknown)
              && (moreThan1Frame==1) ) {
                /* at least one frame successfully completed,
                 * but following bytes are garbage :
                 * it's more likely to be a srcSize error,
                 * specifying more bytes than compressed size of frame(s).
                 * This error message replaces ERROR(prefix_unknown),
                 * which would be confusing, as the first header is actually correct.
                 * Note that one could be unlucky, it might be a corruption error instead,
                 * happening right at the place where we expect zstd magic bytes.
                 * But this is _much_ less likely than a srcSize field error. */
                return ERROR(srcSize_wrong);
            }
            if (ZSTD_isError(res)) return res;
            assert(res <= dstCapacity);
            dst = (BYTE*)dst + res;
            dstCapacity -= res;
        }
        moreThan1Frame = 1;
    }  /* while (srcSize >= ZSTD_frameHeaderSize_prefix) */

    if (srcSize) return ERROR(srcSize_wrong); /* input not entirely consumed */

    return (BYTE*)dst - (BYTE*)dststart;
}