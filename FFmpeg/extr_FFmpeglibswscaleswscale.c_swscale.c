#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yuv2planarX_fn ;
typedef  int /*<<< orphan*/  yuv2planar1_fn ;
typedef  int /*<<< orphan*/  yuv2packedX_fn ;
typedef  int /*<<< orphan*/  yuv2packed2_fn ;
typedef  int /*<<< orphan*/  yuv2packed1_fn ;
typedef  int /*<<< orphan*/  yuv2interleavedX_fn ;
typedef  int /*<<< orphan*/  yuv2anyX_fn ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_25__ {TYPE_2__* comp; } ;
struct TYPE_24__ {int dstW; int dstH; int dstFormat; int flags; int* vLumFilterPos; int* vChrFilterPos; int vLumFilterSize; int vChrFilterSize; int chrSrcVSubSample; int const srcFormat; int dstY; int lumBufIndex; int chrBufIndex; int lastInLumBuf; int lastInChrBuf; int* descIndex; int numDesc; int numSlice; int needAlpha; int vChrDrop; int use_mmx_vfilter; int srcW; int chrDstVSubSample; int const srcH; int const chrSrcH; void* lumDither8; void* chrDither8; TYPE_4__* desc; TYPE_3__* slice; int /*<<< orphan*/  yuv2anyX; int /*<<< orphan*/  yuv2packedX; int /*<<< orphan*/  yuv2packed2; int /*<<< orphan*/  yuv2packed1; int /*<<< orphan*/  yuv2nv12cX; int /*<<< orphan*/  yuv2planeX; int /*<<< orphan*/  yuv2plane1; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* process ) (TYPE_5__*,TYPE_4__*,int,int) ;} ;
struct TYPE_22__ {int width; TYPE_1__* plane; } ;
struct TYPE_21__ {int /*<<< orphan*/  depth; } ;
struct TYPE_20__ {int sliceY; int sliceH; int available_lines; } ;
typedef  TYPE_3__ SwsSlice ;
typedef  TYPE_4__ SwsFilterDescriptor ;
typedef  TYPE_5__ SwsContext ;
typedef  TYPE_6__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int const,int) ; 
 int AV_CPU_FLAG_SSE2 ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  DEBUG_BUFFERS (char*,int const,...) ; 
 void* FFMAX (int const,int) ; 
 int FFMIN (int const,int const) ; 
 scalar_t__ HAVE_MMXEXT ; 
 int const SWS_PRINT_INFO ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int av_get_cpu_flags () ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_6__* av_pix_fmt_desc_get (int const) ; 
 int /*<<< orphan*/  emms_c () ; 
 void** ff_dither_8x8_128 ; 
 int /*<<< orphan*/  ff_init_slice_from_src (TYPE_3__*,int /*<<< orphan*/ **,int*,int,int,int const,int const,int const,int) ; 
 int /*<<< orphan*/  ff_init_vscale_pfn (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_rotate_slice (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  ff_sws_init_output_funcs (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fillPlane (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  fillPlane16 (int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is16BPS (int const) ; 
 scalar_t__ isALPHA (int const) ; 
 int /*<<< orphan*/  isBE (int const) ; 
 scalar_t__ isNBPS (int const) ; 
 scalar_t__ isPacked (int const) ; 
 scalar_t__ isPlanar (int const) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,TYPE_4__*,int,int) ; 
 void* sws_pb_64 ; 

__attribute__((used)) static int swscale(SwsContext *c, const uint8_t *src[],
                   int srcStride[], int srcSliceY,
                   int srcSliceH, uint8_t *dst[], int dstStride[])
{
    /* load a few things into local vars to make the code more readable?
     * and faster */
    const int dstW                   = c->dstW;
    const int dstH                   = c->dstH;

    const enum AVPixelFormat dstFormat = c->dstFormat;
    const int flags                  = c->flags;
    int32_t *vLumFilterPos           = c->vLumFilterPos;
    int32_t *vChrFilterPos           = c->vChrFilterPos;

    const int vLumFilterSize         = c->vLumFilterSize;
    const int vChrFilterSize         = c->vChrFilterSize;

    yuv2planar1_fn yuv2plane1        = c->yuv2plane1;
    yuv2planarX_fn yuv2planeX        = c->yuv2planeX;
    yuv2interleavedX_fn yuv2nv12cX   = c->yuv2nv12cX;
    yuv2packed1_fn yuv2packed1       = c->yuv2packed1;
    yuv2packed2_fn yuv2packed2       = c->yuv2packed2;
    yuv2packedX_fn yuv2packedX       = c->yuv2packedX;
    yuv2anyX_fn yuv2anyX             = c->yuv2anyX;
    const int chrSrcSliceY           =                srcSliceY >> c->chrSrcVSubSample;
    const int chrSrcSliceH           = AV_CEIL_RSHIFT(srcSliceH,   c->chrSrcVSubSample);
    int should_dither                = isNBPS(c->srcFormat) ||
                                       is16BPS(c->srcFormat);
    int lastDstY;

    /* vars which will change and which we need to store back in the context */
    int dstY         = c->dstY;
    int lumBufIndex  = c->lumBufIndex;
    int chrBufIndex  = c->chrBufIndex;
    int lastInLumBuf = c->lastInLumBuf;
    int lastInChrBuf = c->lastInChrBuf;


    int lumStart = 0;
    int lumEnd = c->descIndex[0];
    int chrStart = lumEnd;
    int chrEnd = c->descIndex[1];
    int vStart = chrEnd;
    int vEnd = c->numDesc;
    SwsSlice *src_slice = &c->slice[lumStart];
    SwsSlice *hout_slice = &c->slice[c->numSlice-2];
    SwsSlice *vout_slice = &c->slice[c->numSlice-1];
    SwsFilterDescriptor *desc = c->desc;


    int needAlpha = c->needAlpha;

    int hasLumHoles = 1;
    int hasChrHoles = 1;


    if (isPacked(c->srcFormat)) {
        src[0] =
        src[1] =
        src[2] =
        src[3] = src[0];
        srcStride[0] =
        srcStride[1] =
        srcStride[2] =
        srcStride[3] = srcStride[0];
    }
    srcStride[1] <<= c->vChrDrop;
    srcStride[2] <<= c->vChrDrop;

    DEBUG_BUFFERS("swscale() %p[%d] %p[%d] %p[%d] %p[%d] -> %p[%d] %p[%d] %p[%d] %p[%d]\n",
                  src[0], srcStride[0], src[1], srcStride[1],
                  src[2], srcStride[2], src[3], srcStride[3],
                  dst[0], dstStride[0], dst[1], dstStride[1],
                  dst[2], dstStride[2], dst[3], dstStride[3]);
    DEBUG_BUFFERS("srcSliceY: %d srcSliceH: %d dstY: %d dstH: %d\n",
                  srcSliceY, srcSliceH, dstY, dstH);
    DEBUG_BUFFERS("vLumFilterSize: %d vChrFilterSize: %d\n",
                  vLumFilterSize, vChrFilterSize);

    if (dstStride[0]&15 || dstStride[1]&15 ||
        dstStride[2]&15 || dstStride[3]&15) {
        static int warnedAlready = 0; // FIXME maybe move this into the context
        if (flags & SWS_PRINT_INFO && !warnedAlready) {
            av_log(c, AV_LOG_WARNING,
                   "Warning: dstStride is not aligned!\n"
                   "         ->cannot do aligned memory accesses anymore\n");
            warnedAlready = 1;
        }
    }

    if (   (uintptr_t)dst[0]&15 || (uintptr_t)dst[1]&15 || (uintptr_t)dst[2]&15
        || (uintptr_t)src[0]&15 || (uintptr_t)src[1]&15 || (uintptr_t)src[2]&15
        || dstStride[0]&15 || dstStride[1]&15 || dstStride[2]&15 || dstStride[3]&15
        || srcStride[0]&15 || srcStride[1]&15 || srcStride[2]&15 || srcStride[3]&15
    ) {
        static int warnedAlready=0;
        int cpu_flags = av_get_cpu_flags();
        if (HAVE_MMXEXT && (cpu_flags & AV_CPU_FLAG_SSE2) && !warnedAlready){
            av_log(c, AV_LOG_WARNING, "Warning: data is not aligned! This can lead to a speed loss\n");
            warnedAlready=1;
        }
    }

    /* Note the user might start scaling the picture in the middle so this
     * will not get executed. This is not really intended but works
     * currently, so people might do it. */
    if (srcSliceY == 0) {
        lumBufIndex  = -1;
        chrBufIndex  = -1;
        dstY         = 0;
        lastInLumBuf = -1;
        lastInChrBuf = -1;
    }

    if (!should_dither) {
        c->chrDither8 = c->lumDither8 = sws_pb_64;
    }
    lastDstY = dstY;

    ff_init_vscale_pfn(c, yuv2plane1, yuv2planeX, yuv2nv12cX,
                   yuv2packed1, yuv2packed2, yuv2packedX, yuv2anyX, c->use_mmx_vfilter);

    ff_init_slice_from_src(src_slice, (uint8_t**)src, srcStride, c->srcW,
            srcSliceY, srcSliceH, chrSrcSliceY, chrSrcSliceH, 1);

    ff_init_slice_from_src(vout_slice, (uint8_t**)dst, dstStride, c->dstW,
            dstY, dstH, dstY >> c->chrDstVSubSample,
            AV_CEIL_RSHIFT(dstH, c->chrDstVSubSample), 0);
    if (srcSliceY == 0) {
        hout_slice->plane[0].sliceY = lastInLumBuf + 1;
        hout_slice->plane[1].sliceY = lastInChrBuf + 1;
        hout_slice->plane[2].sliceY = lastInChrBuf + 1;
        hout_slice->plane[3].sliceY = lastInLumBuf + 1;

        hout_slice->plane[0].sliceH =
        hout_slice->plane[1].sliceH =
        hout_slice->plane[2].sliceH =
        hout_slice->plane[3].sliceH = 0;
        hout_slice->width = dstW;
    }

    for (; dstY < dstH; dstY++) {
        const int chrDstY = dstY >> c->chrDstVSubSample;
        int use_mmx_vfilter= c->use_mmx_vfilter;

        // First line needed as input
        const int firstLumSrcY  = FFMAX(1 - vLumFilterSize, vLumFilterPos[dstY]);
        const int firstLumSrcY2 = FFMAX(1 - vLumFilterSize, vLumFilterPos[FFMIN(dstY | ((1 << c->chrDstVSubSample) - 1), dstH - 1)]);
        // First line needed as input
        const int firstChrSrcY  = FFMAX(1 - vChrFilterSize, vChrFilterPos[chrDstY]);

        // Last line needed as input
        int lastLumSrcY  = FFMIN(c->srcH,    firstLumSrcY  + vLumFilterSize) - 1;
        int lastLumSrcY2 = FFMIN(c->srcH,    firstLumSrcY2 + vLumFilterSize) - 1;
        int lastChrSrcY  = FFMIN(c->chrSrcH, firstChrSrcY  + vChrFilterSize) - 1;
        int enough_lines;

        int i;
        int posY, cPosY, firstPosY, lastPosY, firstCPosY, lastCPosY;

        // handle holes (FAST_BILINEAR & weird filters)
        if (firstLumSrcY > lastInLumBuf) {

            hasLumHoles = lastInLumBuf != firstLumSrcY - 1;
            if (hasLumHoles) {
                hout_slice->plane[0].sliceY = firstLumSrcY;
                hout_slice->plane[3].sliceY = firstLumSrcY;
                hout_slice->plane[0].sliceH =
                hout_slice->plane[3].sliceH = 0;
            }

            lastInLumBuf = firstLumSrcY - 1;
        }
        if (firstChrSrcY > lastInChrBuf) {

            hasChrHoles = lastInChrBuf != firstChrSrcY - 1;
            if (hasChrHoles) {
                hout_slice->plane[1].sliceY = firstChrSrcY;
                hout_slice->plane[2].sliceY = firstChrSrcY;
                hout_slice->plane[1].sliceH =
                hout_slice->plane[2].sliceH = 0;
            }

            lastInChrBuf = firstChrSrcY - 1;
        }

        DEBUG_BUFFERS("dstY: %d\n", dstY);
        DEBUG_BUFFERS("\tfirstLumSrcY: %d lastLumSrcY: %d lastInLumBuf: %d\n",
                      firstLumSrcY, lastLumSrcY, lastInLumBuf);
        DEBUG_BUFFERS("\tfirstChrSrcY: %d lastChrSrcY: %d lastInChrBuf: %d\n",
                      firstChrSrcY, lastChrSrcY, lastInChrBuf);

        // Do we have enough lines in this slice to output the dstY line
        enough_lines = lastLumSrcY2 < srcSliceY + srcSliceH &&
                       lastChrSrcY < AV_CEIL_RSHIFT(srcSliceY + srcSliceH, c->chrSrcVSubSample);

        if (!enough_lines) {
            lastLumSrcY = srcSliceY + srcSliceH - 1;
            lastChrSrcY = chrSrcSliceY + chrSrcSliceH - 1;
            DEBUG_BUFFERS("buffering slice: lastLumSrcY %d lastChrSrcY %d\n",
                          lastLumSrcY, lastChrSrcY);
        }

        av_assert0((lastLumSrcY - firstLumSrcY + 1) <= hout_slice->plane[0].available_lines);
        av_assert0((lastChrSrcY - firstChrSrcY + 1) <= hout_slice->plane[1].available_lines);


        posY = hout_slice->plane[0].sliceY + hout_slice->plane[0].sliceH;
        if (posY <= lastLumSrcY && !hasLumHoles) {
            firstPosY = FFMAX(firstLumSrcY, posY);
            lastPosY = FFMIN(firstLumSrcY + hout_slice->plane[0].available_lines - 1, srcSliceY + srcSliceH - 1);
        } else {
            firstPosY = posY;
            lastPosY = lastLumSrcY;
        }

        cPosY = hout_slice->plane[1].sliceY + hout_slice->plane[1].sliceH;
        if (cPosY <= lastChrSrcY && !hasChrHoles) {
            firstCPosY = FFMAX(firstChrSrcY, cPosY);
            lastCPosY = FFMIN(firstChrSrcY + hout_slice->plane[1].available_lines - 1, AV_CEIL_RSHIFT(srcSliceY + srcSliceH, c->chrSrcVSubSample) - 1);
        } else {
            firstCPosY = cPosY;
            lastCPosY = lastChrSrcY;
        }

        ff_rotate_slice(hout_slice, lastPosY, lastCPosY);

        if (posY < lastLumSrcY + 1) {
            for (i = lumStart; i < lumEnd; ++i)
                desc[i].process(c, &desc[i], firstPosY, lastPosY - firstPosY + 1);
        }

        lumBufIndex += lastLumSrcY - lastInLumBuf;
        lastInLumBuf = lastLumSrcY;

        if (cPosY < lastChrSrcY + 1) {
            for (i = chrStart; i < chrEnd; ++i)
                desc[i].process(c, &desc[i], firstCPosY, lastCPosY - firstCPosY + 1);
        }

        chrBufIndex += lastChrSrcY - lastInChrBuf;
        lastInChrBuf = lastChrSrcY;

        // wrap buf index around to stay inside the ring buffer
        if (lumBufIndex >= vLumFilterSize)
            lumBufIndex -= vLumFilterSize;
        if (chrBufIndex >= vChrFilterSize)
            chrBufIndex -= vChrFilterSize;
        if (!enough_lines)
            break;  // we can't output a dstY line so let's try with the next slice

#if HAVE_MMX_INLINE
        ff_updateMMXDitherTables(c, dstY, lumBufIndex, chrBufIndex,
                              lastInLumBuf, lastInChrBuf);
#endif
        if (should_dither) {
            c->chrDither8 = ff_dither_8x8_128[chrDstY & 7];
            c->lumDither8 = ff_dither_8x8_128[dstY    & 7];
        }
        if (dstY >= dstH - 2) {
            /* hmm looks like we can't use MMX here without overwriting
             * this array's tail */
            ff_sws_init_output_funcs(c, &yuv2plane1, &yuv2planeX, &yuv2nv12cX,
                                     &yuv2packed1, &yuv2packed2, &yuv2packedX, &yuv2anyX);
            use_mmx_vfilter= 0;
            ff_init_vscale_pfn(c, yuv2plane1, yuv2planeX, yuv2nv12cX,
                           yuv2packed1, yuv2packed2, yuv2packedX, yuv2anyX, use_mmx_vfilter);
        }

        {
            for (i = vStart; i < vEnd; ++i)
                desc[i].process(c, &desc[i], dstY, 1);
        }
    }
    if (isPlanar(dstFormat) && isALPHA(dstFormat) && !needAlpha) {
        int length = dstW;
        int height = dstY - lastDstY;

        if (is16BPS(dstFormat) || isNBPS(dstFormat)) {
            const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(dstFormat);
            fillPlane16(dst[3], dstStride[3], length, height, lastDstY,
                    1, desc->comp[3].depth,
                    isBE(dstFormat));
        } else
            fillPlane(dst[3], dstStride[3], length, height, lastDstY, 255);
    }

#if HAVE_MMXEXT_INLINE
    if (av_get_cpu_flags() & AV_CPU_FLAG_MMXEXT)
        __asm__ volatile ("sfence" ::: "memory");
#endif
    emms_c();

    /* store changed local vars back in the context */
    c->dstY         = dstY;
    c->lumBufIndex  = lumBufIndex;
    c->chrBufIndex  = chrBufIndex;
    c->lastInLumBuf = lastInLumBuf;
    c->lastInChrBuf = lastInChrBuf;

    return dstY - lastDstY;
}