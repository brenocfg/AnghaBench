#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_13__ {TYPE_1__* comp; } ;
struct TYPE_12__ {int srcFormat; int dstFormat; int flags; int dstH; int dstFormatBpp; int srcFormatBpp; scalar_t__ dither; scalar_t__ chrDstHSubSample; scalar_t__ chrSrcHSubSample; scalar_t__ chrDstVSubSample; scalar_t__ chrSrcVSubSample; int /*<<< orphan*/  swscale; } ;
struct TYPE_11__ {int depth; } ;
typedef  TYPE_2__ SwsContext ;

/* Variables and functions */
 scalar_t__ ARCH_AARCH64 ; 
 scalar_t__ ARCH_ARM ; 
 scalar_t__ ARCH_PPC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int const AV_PIX_FMT_AYUV64 ; 
 int const AV_PIX_FMT_BAYER_BGGR16 ; 
 int const AV_PIX_FMT_BAYER_GBRG16 ; 
 int const AV_PIX_FMT_BAYER_GRBG16 ; 
 int const AV_PIX_FMT_BAYER_RGGB16 ; 
 int const AV_PIX_FMT_BGR24 ; 
 int const AV_PIX_FMT_BGR32 ; 
 int const AV_PIX_FMT_BGR32_1 ; 
 int const AV_PIX_FMT_BGR444 ; 
 int const AV_PIX_FMT_BGR48 ; 
 int const AV_PIX_FMT_BGR48BE ; 
 int const AV_PIX_FMT_BGR48LE ; 
 int const AV_PIX_FMT_BGR555 ; 
 int const AV_PIX_FMT_BGR565 ; 
 int const AV_PIX_FMT_BGRA64 ; 
 int const AV_PIX_FMT_BGRA64BE ; 
 int const AV_PIX_FMT_BGRA64LE ; 
 int const AV_PIX_FMT_GBRAP ; 
 int const AV_PIX_FMT_GBRAP12 ; 
 int const AV_PIX_FMT_GBRAP12BE ; 
 int const AV_PIX_FMT_GBRAP12LE ; 
 int const AV_PIX_FMT_GBRAP16 ; 
 int const AV_PIX_FMT_GBRAP16BE ; 
 int const AV_PIX_FMT_GBRAP16LE ; 
 int const AV_PIX_FMT_GBRP ; 
 int const AV_PIX_FMT_GBRP10 ; 
 int const AV_PIX_FMT_GBRP10BE ; 
 int const AV_PIX_FMT_GBRP10LE ; 
 int const AV_PIX_FMT_GBRP12 ; 
 int const AV_PIX_FMT_GBRP12BE ; 
 int const AV_PIX_FMT_GBRP12LE ; 
 int const AV_PIX_FMT_GBRP14 ; 
 int const AV_PIX_FMT_GBRP14BE ; 
 int const AV_PIX_FMT_GBRP14LE ; 
 int const AV_PIX_FMT_GBRP16 ; 
 int const AV_PIX_FMT_GBRP16BE ; 
 int const AV_PIX_FMT_GBRP16LE ; 
 int const AV_PIX_FMT_GBRP9 ; 
 int const AV_PIX_FMT_GBRP9BE ; 
 int const AV_PIX_FMT_GBRP9LE ; 
 int const AV_PIX_FMT_GRAY10 ; 
 int const AV_PIX_FMT_GRAY12 ; 
 int const AV_PIX_FMT_GRAY14 ; 
 int const AV_PIX_FMT_GRAY16 ; 
 int const AV_PIX_FMT_GRAY8 ; 
 int const AV_PIX_FMT_GRAY9 ; 
 int const AV_PIX_FMT_GRAYF32 ; 
 int const AV_PIX_FMT_NV12 ; 
 int const AV_PIX_FMT_NV21 ; 
 int const AV_PIX_FMT_P010 ; 
 int const AV_PIX_FMT_P010LE ; 
 int const AV_PIX_FMT_P016 ; 
 int const AV_PIX_FMT_P016LE ; 
 int const AV_PIX_FMT_RGB24 ; 
 int const AV_PIX_FMT_RGB32 ; 
 int const AV_PIX_FMT_RGB32_1 ; 
 int const AV_PIX_FMT_RGB444 ; 
 int const AV_PIX_FMT_RGB48 ; 
 int const AV_PIX_FMT_RGB48BE ; 
 int const AV_PIX_FMT_RGB48LE ; 
 int const AV_PIX_FMT_RGB555 ; 
 int const AV_PIX_FMT_RGB565 ; 
 int const AV_PIX_FMT_RGBA64 ; 
 int const AV_PIX_FMT_RGBA64BE ; 
 int const AV_PIX_FMT_RGBA64LE ; 
 int const AV_PIX_FMT_UYVY422 ; 
 int const AV_PIX_FMT_XYZ12 ; 
 int const AV_PIX_FMT_YA16 ; 
 int const AV_PIX_FMT_YA16BE ; 
 int const AV_PIX_FMT_YA16LE ; 
 int const AV_PIX_FMT_YA8 ; 
 int const AV_PIX_FMT_YUV410P ; 
 int const AV_PIX_FMT_YUV420P ; 
 int const AV_PIX_FMT_YUV420P10 ; 
 int const AV_PIX_FMT_YUV420P12 ; 
 int const AV_PIX_FMT_YUV420P14 ; 
 int const AV_PIX_FMT_YUV420P16 ; 
 int const AV_PIX_FMT_YUV420P9 ; 
 int const AV_PIX_FMT_YUV422P ; 
 int const AV_PIX_FMT_YUV422P10 ; 
 int const AV_PIX_FMT_YUV422P12 ; 
 int const AV_PIX_FMT_YUV422P14 ; 
 int const AV_PIX_FMT_YUV422P16 ; 
 int const AV_PIX_FMT_YUV422P9 ; 
 int const AV_PIX_FMT_YUV440P10 ; 
 int const AV_PIX_FMT_YUV440P12 ; 
 int const AV_PIX_FMT_YUV444P10 ; 
 int const AV_PIX_FMT_YUV444P12 ; 
 int const AV_PIX_FMT_YUV444P14 ; 
 int const AV_PIX_FMT_YUV444P16 ; 
 int const AV_PIX_FMT_YUV444P9 ; 
 int const AV_PIX_FMT_YUVA420P ; 
 int const AV_PIX_FMT_YUVA420P10 ; 
 int const AV_PIX_FMT_YUVA420P16 ; 
 int const AV_PIX_FMT_YUYV422 ; 
 scalar_t__ IS_DIFFERENT_ENDIANESS (int const,int const,int const) ; 
 int /*<<< orphan*/  Rgb16ToPlanarRgb16Wrapper ; 
 int const SWS_ACCURATE_RND ; 
 int const SWS_BITEXACT ; 
 scalar_t__ SWS_DITHER_AUTO ; 
 scalar_t__ SWS_DITHER_BAYER ; 
 int SWS_FAST_BILINEAR ; 
 int SWS_POINT ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_9__* av_pix_fmt_desc_get (int const) ; 
 int /*<<< orphan*/  bayer_to_rgb24_wrapper ; 
 int /*<<< orphan*/  bayer_to_yv12_wrapper ; 
 int /*<<< orphan*/  bgr24ToYv12Wrapper ; 
 int /*<<< orphan*/  bswap_16bpc ; 
 int /*<<< orphan*/  ff_get_unscaled_swscale_aarch64 (TYPE_2__*) ; 
 int /*<<< orphan*/  ff_get_unscaled_swscale_arm (TYPE_2__*) ; 
 int /*<<< orphan*/  ff_get_unscaled_swscale_ppc (TYPE_2__*) ; 
 int /*<<< orphan*/  ff_yuv2rgb_get_func_ptr (TYPE_2__*) ; 
 scalar_t__ findRgbConvFn (TYPE_2__*) ; 
 int /*<<< orphan*/  float_y_to_uint_y_wrapper ; 
 scalar_t__ isAnyRGB (int const) ; 
 scalar_t__ isBayer (int const) ; 
 scalar_t__ isFloat (int const) ; 
 scalar_t__ isGray (int const) ; 
 scalar_t__ isPacked (int) ; 
 scalar_t__ isPackedRGB (int const) ; 
 scalar_t__ isPlanar (int const) ; 
 scalar_t__ isPlanarYUV (int const) ; 
 int /*<<< orphan*/  isSemiPlanarYUV (int const) ; 
 int /*<<< orphan*/  nv12ToPlanarWrapper ; 
 int /*<<< orphan*/  packedCopyWrapper ; 
 int /*<<< orphan*/  palToRgbWrapper ; 
 int /*<<< orphan*/  planar8ToP01xleWrapper ; 
 int /*<<< orphan*/  planarCopyWrapper ; 
 int /*<<< orphan*/  planarRgb16ToRgb16Wrapper ; 
 int /*<<< orphan*/  planarRgbToRgbWrapper ; 
 int /*<<< orphan*/  planarRgbToplanarRgbWrapper ; 
 int /*<<< orphan*/  planarRgbaToRgbWrapper ; 
 int /*<<< orphan*/  planarToNv12Wrapper ; 
 int /*<<< orphan*/  planarToP01xWrapper ; 
 int /*<<< orphan*/  planarToUyvyWrapper ; 
 int /*<<< orphan*/  planarToYuy2Wrapper ; 
 int /*<<< orphan*/  rgbToPlanarRgbWrapper ; 
 int /*<<< orphan*/  rgbToRgbWrapper ; 
 int /*<<< orphan*/  uint_y_to_float_y_wrapper ; 
 scalar_t__ usePal (int const) ; 
 int /*<<< orphan*/  uyvyToYuv420Wrapper ; 
 int /*<<< orphan*/  uyvyToYuv422Wrapper ; 
 int /*<<< orphan*/  yuv422pToUyvyWrapper ; 
 int /*<<< orphan*/  yuv422pToYuy2Wrapper ; 
 int /*<<< orphan*/  yuyvToYuv420Wrapper ; 
 int /*<<< orphan*/  yuyvToYuv422Wrapper ; 
 int /*<<< orphan*/  yvu9ToYv12Wrapper ; 

void ff_get_unscaled_swscale(SwsContext *c)
{
    const enum AVPixelFormat srcFormat = c->srcFormat;
    const enum AVPixelFormat dstFormat = c->dstFormat;
    const int flags = c->flags;
    const int dstH = c->dstH;
    int needsDither;

    needsDither = isAnyRGB(dstFormat) &&
            c->dstFormatBpp < 24 &&
           (c->dstFormatBpp < c->srcFormatBpp || (!isAnyRGB(srcFormat)));

    /* yv12_to_nv12 */
    if ((srcFormat == AV_PIX_FMT_YUV420P || srcFormat == AV_PIX_FMT_YUVA420P) &&
        (dstFormat == AV_PIX_FMT_NV12 || dstFormat == AV_PIX_FMT_NV21)) {
        c->swscale = planarToNv12Wrapper;
    }
    /* nv12_to_yv12 */
    if (dstFormat == AV_PIX_FMT_YUV420P &&
        (srcFormat == AV_PIX_FMT_NV12 || srcFormat == AV_PIX_FMT_NV21)) {
        c->swscale = nv12ToPlanarWrapper;
    }
    /* yuv2bgr */
    if ((srcFormat == AV_PIX_FMT_YUV420P || srcFormat == AV_PIX_FMT_YUV422P ||
         srcFormat == AV_PIX_FMT_YUVA420P) && isAnyRGB(dstFormat) &&
        !(flags & SWS_ACCURATE_RND) && (c->dither == SWS_DITHER_BAYER || c->dither == SWS_DITHER_AUTO) && !(dstH & 1)) {
        c->swscale = ff_yuv2rgb_get_func_ptr(c);
    }
    /* yuv420p1x_to_p01x */
    if ((srcFormat == AV_PIX_FMT_YUV420P10 || srcFormat == AV_PIX_FMT_YUVA420P10 ||
         srcFormat == AV_PIX_FMT_YUV420P12 ||
         srcFormat == AV_PIX_FMT_YUV420P14 ||
         srcFormat == AV_PIX_FMT_YUV420P16 || srcFormat == AV_PIX_FMT_YUVA420P16) &&
        (dstFormat == AV_PIX_FMT_P010 || dstFormat == AV_PIX_FMT_P016)) {
        c->swscale = planarToP01xWrapper;
    }
    /* yuv420p_to_p01xle */
    if ((srcFormat == AV_PIX_FMT_YUV420P || srcFormat == AV_PIX_FMT_YUVA420P) &&
        (dstFormat == AV_PIX_FMT_P010LE || dstFormat == AV_PIX_FMT_P016LE)) {
        c->swscale = planar8ToP01xleWrapper;
    }

    if (srcFormat == AV_PIX_FMT_YUV410P && !(dstH & 3) &&
        (dstFormat == AV_PIX_FMT_YUV420P || dstFormat == AV_PIX_FMT_YUVA420P) &&
        !(flags & SWS_BITEXACT)) {
        c->swscale = yvu9ToYv12Wrapper;
    }

    /* bgr24toYV12 */
    if (srcFormat == AV_PIX_FMT_BGR24 &&
        (dstFormat == AV_PIX_FMT_YUV420P || dstFormat == AV_PIX_FMT_YUVA420P) &&
        !(flags & SWS_ACCURATE_RND))
        c->swscale = bgr24ToYv12Wrapper;

    /* RGB/BGR -> RGB/BGR (no dither needed forms) */
    if (isAnyRGB(srcFormat) && isAnyRGB(dstFormat) && findRgbConvFn(c)
        && (!needsDither || (c->flags&(SWS_FAST_BILINEAR|SWS_POINT))))
        c->swscale = rgbToRgbWrapper;

    /* RGB to planar RGB */
    if ((srcFormat == AV_PIX_FMT_GBRP && dstFormat == AV_PIX_FMT_GBRAP) ||
        (srcFormat == AV_PIX_FMT_GBRAP && dstFormat == AV_PIX_FMT_GBRP))
        c->swscale = planarRgbToplanarRgbWrapper;

#define isByteRGB(f) (             \
        f == AV_PIX_FMT_RGB32   || \
        f == AV_PIX_FMT_RGB32_1 || \
        f == AV_PIX_FMT_RGB24   || \
        f == AV_PIX_FMT_BGR32   || \
        f == AV_PIX_FMT_BGR32_1 || \
        f == AV_PIX_FMT_BGR24)

    if (srcFormat == AV_PIX_FMT_GBRP && isPlanar(srcFormat) && isByteRGB(dstFormat))
        c->swscale = planarRgbToRgbWrapper;

    if (srcFormat == AV_PIX_FMT_GBRAP && isByteRGB(dstFormat))
        c->swscale = planarRgbaToRgbWrapper;

    if ((srcFormat == AV_PIX_FMT_RGB48LE  || srcFormat == AV_PIX_FMT_RGB48BE  ||
         srcFormat == AV_PIX_FMT_BGR48LE  || srcFormat == AV_PIX_FMT_BGR48BE  ||
         srcFormat == AV_PIX_FMT_RGBA64LE || srcFormat == AV_PIX_FMT_RGBA64BE ||
         srcFormat == AV_PIX_FMT_BGRA64LE || srcFormat == AV_PIX_FMT_BGRA64BE) &&
        (dstFormat == AV_PIX_FMT_GBRP9LE  || dstFormat == AV_PIX_FMT_GBRP9BE  ||
         dstFormat == AV_PIX_FMT_GBRP10LE || dstFormat == AV_PIX_FMT_GBRP10BE ||
         dstFormat == AV_PIX_FMT_GBRP12LE || dstFormat == AV_PIX_FMT_GBRP12BE ||
         dstFormat == AV_PIX_FMT_GBRP14LE || dstFormat == AV_PIX_FMT_GBRP14BE ||
         dstFormat == AV_PIX_FMT_GBRP16LE || dstFormat == AV_PIX_FMT_GBRP16BE ||
         dstFormat == AV_PIX_FMT_GBRAP12LE || dstFormat == AV_PIX_FMT_GBRAP12BE ||
         dstFormat == AV_PIX_FMT_GBRAP16LE || dstFormat == AV_PIX_FMT_GBRAP16BE ))
        c->swscale = Rgb16ToPlanarRgb16Wrapper;

    if ((srcFormat == AV_PIX_FMT_GBRP9LE  || srcFormat == AV_PIX_FMT_GBRP9BE  ||
         srcFormat == AV_PIX_FMT_GBRP16LE || srcFormat == AV_PIX_FMT_GBRP16BE ||
         srcFormat == AV_PIX_FMT_GBRP10LE || srcFormat == AV_PIX_FMT_GBRP10BE ||
         srcFormat == AV_PIX_FMT_GBRP12LE || srcFormat == AV_PIX_FMT_GBRP12BE ||
         srcFormat == AV_PIX_FMT_GBRP14LE || srcFormat == AV_PIX_FMT_GBRP14BE ||
         srcFormat == AV_PIX_FMT_GBRAP12LE || srcFormat == AV_PIX_FMT_GBRAP12BE ||
         srcFormat == AV_PIX_FMT_GBRAP16LE || srcFormat == AV_PIX_FMT_GBRAP16BE) &&
        (dstFormat == AV_PIX_FMT_RGB48LE  || dstFormat == AV_PIX_FMT_RGB48BE  ||
         dstFormat == AV_PIX_FMT_BGR48LE  || dstFormat == AV_PIX_FMT_BGR48BE  ||
         dstFormat == AV_PIX_FMT_RGBA64LE || dstFormat == AV_PIX_FMT_RGBA64BE ||
         dstFormat == AV_PIX_FMT_BGRA64LE || dstFormat == AV_PIX_FMT_BGRA64BE))
        c->swscale = planarRgb16ToRgb16Wrapper;

    if (av_pix_fmt_desc_get(srcFormat)->comp[0].depth == 8 &&
        isPackedRGB(srcFormat) && dstFormat == AV_PIX_FMT_GBRP)
        c->swscale = rgbToPlanarRgbWrapper;

    if (isBayer(srcFormat)) {
        if (dstFormat == AV_PIX_FMT_RGB24)
            c->swscale = bayer_to_rgb24_wrapper;
        else if (dstFormat == AV_PIX_FMT_YUV420P)
            c->swscale = bayer_to_yv12_wrapper;
        else if (!isBayer(dstFormat)) {
            av_log(c, AV_LOG_ERROR, "unsupported bayer conversion\n");
            av_assert0(0);
        }
    }

    /* bswap 16 bits per pixel/component packed formats */
    if (IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_BAYER_BGGR16) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_BAYER_RGGB16) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_BAYER_GBRG16) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_BAYER_GRBG16) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_BGR444) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_BGR48)  ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_BGRA64) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_BGR555) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_BGR565) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_BGRA64) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GRAY9)  ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GRAY10) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GRAY12) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GRAY14) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GRAY16) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YA16)   ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_AYUV64) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GBRP9)  ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GBRP10) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GBRP12) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GBRP14) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GBRP16) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GBRAP12) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_GBRAP16) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_RGB444) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_RGB48)  ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_RGBA64) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_RGB555) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_RGB565) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_RGBA64) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_XYZ12)  ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV420P9)  ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV420P10) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV420P12) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV420P14) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV420P16) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV422P9)  ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV422P10) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV422P12) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV422P14) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV422P16) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV440P10) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV440P12) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV444P9)  ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV444P10) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV444P12) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV444P14) ||
        IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, AV_PIX_FMT_YUV444P16))
        c->swscale = bswap_16bpc;

    if (usePal(srcFormat) && isByteRGB(dstFormat))
        c->swscale = palToRgbWrapper;

    if (srcFormat == AV_PIX_FMT_YUV422P) {
        if (dstFormat == AV_PIX_FMT_YUYV422)
            c->swscale = yuv422pToYuy2Wrapper;
        else if (dstFormat == AV_PIX_FMT_UYVY422)
            c->swscale = yuv422pToUyvyWrapper;
    }

    /* uint Y to float Y */
    if (srcFormat == AV_PIX_FMT_GRAY8 && dstFormat == AV_PIX_FMT_GRAYF32){
        c->swscale = uint_y_to_float_y_wrapper;
    }

    /* float Y to uint Y */
    if (srcFormat == AV_PIX_FMT_GRAYF32 && dstFormat == AV_PIX_FMT_GRAY8){
        c->swscale = float_y_to_uint_y_wrapper;
    }

    /* LQ converters if -sws 0 or -sws 4*/
    if (c->flags&(SWS_FAST_BILINEAR|SWS_POINT)) {
        /* yv12_to_yuy2 */
        if (srcFormat == AV_PIX_FMT_YUV420P || srcFormat == AV_PIX_FMT_YUVA420P) {
            if (dstFormat == AV_PIX_FMT_YUYV422)
                c->swscale = planarToYuy2Wrapper;
            else if (dstFormat == AV_PIX_FMT_UYVY422)
                c->swscale = planarToUyvyWrapper;
        }
    }
    if (srcFormat == AV_PIX_FMT_YUYV422 &&
       (dstFormat == AV_PIX_FMT_YUV420P || dstFormat == AV_PIX_FMT_YUVA420P))
        c->swscale = yuyvToYuv420Wrapper;
    if (srcFormat == AV_PIX_FMT_UYVY422 &&
       (dstFormat == AV_PIX_FMT_YUV420P || dstFormat == AV_PIX_FMT_YUVA420P))
        c->swscale = uyvyToYuv420Wrapper;
    if (srcFormat == AV_PIX_FMT_YUYV422 && dstFormat == AV_PIX_FMT_YUV422P)
        c->swscale = yuyvToYuv422Wrapper;
    if (srcFormat == AV_PIX_FMT_UYVY422 && dstFormat == AV_PIX_FMT_YUV422P)
        c->swscale = uyvyToYuv422Wrapper;

#define isPlanarGray(x) (isGray(x) && (x) != AV_PIX_FMT_YA8 && (x) != AV_PIX_FMT_YA16LE && (x) != AV_PIX_FMT_YA16BE)
    /* simple copy */
    if ( srcFormat == dstFormat ||
        (srcFormat == AV_PIX_FMT_YUVA420P && dstFormat == AV_PIX_FMT_YUV420P) ||
        (srcFormat == AV_PIX_FMT_YUV420P && dstFormat == AV_PIX_FMT_YUVA420P) ||
        (isFloat(srcFormat) == isFloat(dstFormat)) && ((isPlanarYUV(srcFormat) && isPlanarGray(dstFormat)) ||
        (isPlanarYUV(dstFormat) && isPlanarGray(srcFormat)) ||
        (isPlanarGray(dstFormat) && isPlanarGray(srcFormat)) ||
        (isPlanarYUV(srcFormat) && isPlanarYUV(dstFormat) &&
         c->chrDstHSubSample == c->chrSrcHSubSample &&
         c->chrDstVSubSample == c->chrSrcVSubSample &&
         !isSemiPlanarYUV(srcFormat) && !isSemiPlanarYUV(dstFormat))))
    {
        if (isPacked(c->srcFormat))
            c->swscale = packedCopyWrapper;
        else /* Planar YUV or gray */
            c->swscale = planarCopyWrapper;
    }

    if (ARCH_PPC)
        ff_get_unscaled_swscale_ppc(c);
     if (ARCH_ARM)
         ff_get_unscaled_swscale_arm(c);
    if (ARCH_AARCH64)
        ff_get_unscaled_swscale_aarch64(c);
}