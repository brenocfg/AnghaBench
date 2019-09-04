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
typedef  int /*<<< orphan*/ * rgbConvFn ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int srcFormat; int dstFormat; int srcFormatBpp; int dstFormatBpp; int flags; } ;
typedef  TYPE_1__ SwsContext ;

/* Variables and functions */
 scalar_t__ ALT32_CORR ; 
 int const AV_PIX_FMT_ABGR ; 
 int const AV_PIX_FMT_ARGB ; 
 int const AV_PIX_FMT_BGR32 ; 
 int const AV_PIX_FMT_BGR32_1 ; 
 int const AV_PIX_FMT_BGR48BE ; 
 int const AV_PIX_FMT_BGR48LE ; 
 int const AV_PIX_FMT_BGRA ; 
 int const AV_PIX_FMT_BGRA64BE ; 
 int const AV_PIX_FMT_BGRA64LE ; 
 int const AV_PIX_FMT_RGB32 ; 
 int const AV_PIX_FMT_RGB32_1 ; 
 int const AV_PIX_FMT_RGB48BE ; 
 int const AV_PIX_FMT_RGB48LE ; 
 int const AV_PIX_FMT_RGBA ; 
 int const AV_PIX_FMT_RGBA64BE ; 
 int const AV_PIX_FMT_RGBA64LE ; 
 int SWS_BITEXACT ; 
 scalar_t__ isBGRinInt (int const) ; 
 scalar_t__ isRGB48 (int const) ; 
 scalar_t__ isRGBA32 (int const) ; 
 scalar_t__ isRGBA64 (int const) ; 
 scalar_t__ isRGBinInt (int const) ; 
 int /*<<< orphan*/ * rgb12to15 ; 
 int /*<<< orphan*/ * rgb12tobgr12 ; 
 int /*<<< orphan*/ * rgb15to16 ; 
 int /*<<< orphan*/ * rgb15to24 ; 
 int /*<<< orphan*/ * rgb15to32 ; 
 int /*<<< orphan*/ * rgb15tobgr15 ; 
 int /*<<< orphan*/ * rgb15tobgr16 ; 
 int /*<<< orphan*/ * rgb15tobgr24 ; 
 int /*<<< orphan*/ * rgb15tobgr32 ; 
 int /*<<< orphan*/ * rgb16to15 ; 
 int /*<<< orphan*/ * rgb16to24 ; 
 int /*<<< orphan*/ * rgb16to32 ; 
 int /*<<< orphan*/ * rgb16tobgr15 ; 
 int /*<<< orphan*/ * rgb16tobgr16 ; 
 int /*<<< orphan*/ * rgb16tobgr24 ; 
 int /*<<< orphan*/ * rgb16tobgr32 ; 
 int /*<<< orphan*/ * rgb24to15 ; 
 int /*<<< orphan*/ * rgb24to16 ; 
 int /*<<< orphan*/ * rgb24to32 ; 
 int /*<<< orphan*/ * rgb24tobgr15 ; 
 int /*<<< orphan*/ * rgb24tobgr16 ; 
 int /*<<< orphan*/ * rgb24tobgr24 ; 
 int /*<<< orphan*/ * rgb24tobgr32 ; 
 int /*<<< orphan*/ * rgb32to15 ; 
 int /*<<< orphan*/ * rgb32to16 ; 
 int /*<<< orphan*/ * rgb32to24 ; 
 int /*<<< orphan*/ * rgb32tobgr15 ; 
 int /*<<< orphan*/ * rgb32tobgr16 ; 
 int /*<<< orphan*/ * rgb32tobgr24 ; 
 int /*<<< orphan*/ * rgb48to64_bswap ; 
 int /*<<< orphan*/ * rgb48to64_nobswap ; 
 int /*<<< orphan*/ * rgb48tobgr48_bswap ; 
 int /*<<< orphan*/ * rgb48tobgr48_nobswap ; 
 int /*<<< orphan*/ * rgb48tobgr64_bswap ; 
 int /*<<< orphan*/ * rgb48tobgr64_nobswap ; 
 int /*<<< orphan*/ * rgb64to48_bswap ; 
 int /*<<< orphan*/ * rgb64to48_nobswap ; 
 int /*<<< orphan*/ * rgb64tobgr48_bswap ; 
 int /*<<< orphan*/ * rgb64tobgr48_nobswap ; 
 int /*<<< orphan*/ * shuffle_bytes_0321 ; 
 int /*<<< orphan*/ * shuffle_bytes_1230 ; 
 int /*<<< orphan*/ * shuffle_bytes_2103 ; 
 int /*<<< orphan*/ * shuffle_bytes_3012 ; 
 int /*<<< orphan*/ * shuffle_bytes_3210 ; 

__attribute__((used)) static rgbConvFn findRgbConvFn(SwsContext *c)
{
    const enum AVPixelFormat srcFormat = c->srcFormat;
    const enum AVPixelFormat dstFormat = c->dstFormat;
    const int srcId = c->srcFormatBpp;
    const int dstId = c->dstFormatBpp;
    rgbConvFn conv = NULL;

#define IS_NOT_NE(bpp, desc) \
    (((bpp + 7) >> 3) == 2 && \
     (!(desc->flags & AV_PIX_FMT_FLAG_BE) != !HAVE_BIGENDIAN))

#define CONV_IS(src, dst) (srcFormat == AV_PIX_FMT_##src && dstFormat == AV_PIX_FMT_##dst)

    if (isRGBA32(srcFormat) && isRGBA32(dstFormat)) {
        if (     CONV_IS(ABGR, RGBA)
              || CONV_IS(ARGB, BGRA)
              || CONV_IS(BGRA, ARGB)
              || CONV_IS(RGBA, ABGR)) conv = shuffle_bytes_3210;
        else if (CONV_IS(ABGR, ARGB)
              || CONV_IS(ARGB, ABGR)) conv = shuffle_bytes_0321;
        else if (CONV_IS(ABGR, BGRA)
              || CONV_IS(ARGB, RGBA)) conv = shuffle_bytes_1230;
        else if (CONV_IS(BGRA, RGBA)
              || CONV_IS(RGBA, BGRA)) conv = shuffle_bytes_2103;
        else if (CONV_IS(BGRA, ABGR)
              || CONV_IS(RGBA, ARGB)) conv = shuffle_bytes_3012;
    } else if (isRGB48(srcFormat) && isRGB48(dstFormat)) {
        if      (CONV_IS(RGB48LE, BGR48LE)
              || CONV_IS(BGR48LE, RGB48LE)
              || CONV_IS(RGB48BE, BGR48BE)
              || CONV_IS(BGR48BE, RGB48BE)) conv = rgb48tobgr48_nobswap;
        else if (CONV_IS(RGB48LE, BGR48BE)
              || CONV_IS(BGR48LE, RGB48BE)
              || CONV_IS(RGB48BE, BGR48LE)
              || CONV_IS(BGR48BE, RGB48LE)) conv = rgb48tobgr48_bswap;
    } else if (isRGB48(srcFormat) && isRGBA64(dstFormat)) {
        if      (CONV_IS(RGB48LE, BGRA64LE)
              || CONV_IS(BGR48LE, RGBA64LE)
              || CONV_IS(RGB48BE, BGRA64BE)
              || CONV_IS(BGR48BE, RGBA64BE)) conv = rgb48tobgr64_nobswap;
        else if (CONV_IS(RGB48LE, BGRA64BE)
              || CONV_IS(BGR48LE, RGBA64BE)
              || CONV_IS(RGB48BE, BGRA64LE)
              || CONV_IS(BGR48BE, RGBA64LE)) conv = rgb48tobgr64_bswap;
        if      (CONV_IS(RGB48LE, RGBA64LE)
              || CONV_IS(BGR48LE, BGRA64LE)
              || CONV_IS(RGB48BE, RGBA64BE)
              || CONV_IS(BGR48BE, BGRA64BE)) conv = rgb48to64_nobswap;
        else if (CONV_IS(RGB48LE, RGBA64BE)
              || CONV_IS(BGR48LE, BGRA64BE)
              || CONV_IS(RGB48BE, RGBA64LE)
              || CONV_IS(BGR48BE, BGRA64LE)) conv = rgb48to64_bswap;
    } else if (isRGBA64(srcFormat) && isRGB48(dstFormat)) {
        if      (CONV_IS(RGBA64LE, BGR48LE)
              || CONV_IS(BGRA64LE, RGB48LE)
              || CONV_IS(RGBA64BE, BGR48BE)
              || CONV_IS(BGRA64BE, RGB48BE)) conv = rgb64tobgr48_nobswap;
        else if (CONV_IS(RGBA64LE, BGR48BE)
              || CONV_IS(BGRA64LE, RGB48BE)
              || CONV_IS(RGBA64BE, BGR48LE)
              || CONV_IS(BGRA64BE, RGB48LE)) conv = rgb64tobgr48_bswap;
        else if (CONV_IS(RGBA64LE, RGB48LE)
              || CONV_IS(BGRA64LE, BGR48LE)
              || CONV_IS(RGBA64BE, RGB48BE)
              || CONV_IS(BGRA64BE, BGR48BE)) conv = rgb64to48_nobswap;
        else if (CONV_IS(RGBA64LE, RGB48BE)
              || CONV_IS(BGRA64LE, BGR48BE)
              || CONV_IS(RGBA64BE, RGB48LE)
              || CONV_IS(BGRA64BE, BGR48LE)) conv = rgb64to48_bswap;
    } else
    /* BGR -> BGR */
    if ((isBGRinInt(srcFormat) && isBGRinInt(dstFormat)) ||
        (isRGBinInt(srcFormat) && isRGBinInt(dstFormat))) {
        switch (srcId | (dstId << 16)) {
        case 0x000F000C: conv = rgb12to15; break;
        case 0x000F0010: conv = rgb16to15; break;
        case 0x000F0018: conv = rgb24to15; break;
        case 0x000F0020: conv = rgb32to15; break;
        case 0x0010000F: conv = rgb15to16; break;
        case 0x00100018: conv = rgb24to16; break;
        case 0x00100020: conv = rgb32to16; break;
        case 0x0018000F: conv = rgb15to24; break;
        case 0x00180010: conv = rgb16to24; break;
        case 0x00180020: conv = rgb32to24; break;
        case 0x0020000F: conv = rgb15to32; break;
        case 0x00200010: conv = rgb16to32; break;
        case 0x00200018: conv = rgb24to32; break;
        }
    } else if ((isBGRinInt(srcFormat) && isRGBinInt(dstFormat)) ||
               (isRGBinInt(srcFormat) && isBGRinInt(dstFormat))) {
        switch (srcId | (dstId << 16)) {
        case 0x000C000C: conv = rgb12tobgr12; break;
        case 0x000F000F: conv = rgb15tobgr15; break;
        case 0x000F0010: conv = rgb16tobgr15; break;
        case 0x000F0018: conv = rgb24tobgr15; break;
        case 0x000F0020: conv = rgb32tobgr15; break;
        case 0x0010000F: conv = rgb15tobgr16; break;
        case 0x00100010: conv = rgb16tobgr16; break;
        case 0x00100018: conv = rgb24tobgr16; break;
        case 0x00100020: conv = rgb32tobgr16; break;
        case 0x0018000F: conv = rgb15tobgr24; break;
        case 0x00180010: conv = rgb16tobgr24; break;
        case 0x00180018: conv = rgb24tobgr24; break;
        case 0x00180020: conv = rgb32tobgr24; break;
        case 0x0020000F: conv = rgb15tobgr32; break;
        case 0x00200010: conv = rgb16tobgr32; break;
        case 0x00200018: conv = rgb24tobgr32; break;
        }
    }

    if ((dstFormat == AV_PIX_FMT_RGB32_1 || dstFormat == AV_PIX_FMT_BGR32_1) && !isRGBA32(srcFormat) && ALT32_CORR<0)
        return NULL;

    // Maintain symmetry between endianness
    if (c->flags & SWS_BITEXACT)
        if ((dstFormat == AV_PIX_FMT_RGB32   || dstFormat == AV_PIX_FMT_BGR32  ) && !isRGBA32(srcFormat) && ALT32_CORR>0)
            return NULL;

    return conv;
}