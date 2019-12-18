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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
#define  AV_PIX_FMT_ABGR 166 
#define  AV_PIX_FMT_ARGB 165 
 int AV_PIX_FMT_BGR24 ; 
 int AV_PIX_FMT_BGR48 ; 
#define  AV_PIX_FMT_BGRA 164 
#define  AV_PIX_FMT_BGRA64BE 163 
#define  AV_PIX_FMT_BGRA64LE 162 
#define  AV_PIX_FMT_GBRAP 161 
#define  AV_PIX_FMT_GBRAP10BE 160 
#define  AV_PIX_FMT_GBRAP10LE 159 
#define  AV_PIX_FMT_GBRAP12BE 158 
#define  AV_PIX_FMT_GBRAP12LE 157 
#define  AV_PIX_FMT_GBRAP16BE 156 
#define  AV_PIX_FMT_GBRAP16LE 155 
 int AV_PIX_FMT_GBRP ; 
 int AV_PIX_FMT_GBRP10 ; 
 int AV_PIX_FMT_GBRP12 ; 
 int AV_PIX_FMT_GBRP16 ; 
 int AV_PIX_FMT_GRAY16 ; 
 int AV_PIX_FMT_GRAY8 ; 
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_RGB24 ; 
 int AV_PIX_FMT_RGB48 ; 
#define  AV_PIX_FMT_RGBA 154 
#define  AV_PIX_FMT_RGBA64BE 153 
#define  AV_PIX_FMT_RGBA64LE 152 
#define  AV_PIX_FMT_YA16BE 151 
#define  AV_PIX_FMT_YA16LE 150 
#define  AV_PIX_FMT_YA8 149 
 int AV_PIX_FMT_YUV420P ; 
 int AV_PIX_FMT_YUV420P10 ; 
 int AV_PIX_FMT_YUV420P16 ; 
 int AV_PIX_FMT_YUV420P9 ; 
 int AV_PIX_FMT_YUV422P ; 
 int AV_PIX_FMT_YUV422P10 ; 
 int AV_PIX_FMT_YUV422P16 ; 
 int AV_PIX_FMT_YUV422P9 ; 
 int AV_PIX_FMT_YUV444P ; 
 int AV_PIX_FMT_YUV444P10 ; 
 int AV_PIX_FMT_YUV444P16 ; 
 int AV_PIX_FMT_YUV444P9 ; 
#define  AV_PIX_FMT_YUVA420P 148 
#define  AV_PIX_FMT_YUVA420P10BE 147 
#define  AV_PIX_FMT_YUVA420P10LE 146 
#define  AV_PIX_FMT_YUVA420P16BE 145 
#define  AV_PIX_FMT_YUVA420P16LE 144 
#define  AV_PIX_FMT_YUVA420P9BE 143 
#define  AV_PIX_FMT_YUVA420P9LE 142 
#define  AV_PIX_FMT_YUVA422P 141 
#define  AV_PIX_FMT_YUVA422P10BE 140 
#define  AV_PIX_FMT_YUVA422P10LE 139 
#define  AV_PIX_FMT_YUVA422P16BE 138 
#define  AV_PIX_FMT_YUVA422P16LE 137 
#define  AV_PIX_FMT_YUVA422P9BE 136 
#define  AV_PIX_FMT_YUVA422P9LE 135 
#define  AV_PIX_FMT_YUVA444P 134 
#define  AV_PIX_FMT_YUVA444P10BE 133 
#define  AV_PIX_FMT_YUVA444P10LE 132 
#define  AV_PIX_FMT_YUVA444P16BE 131 
#define  AV_PIX_FMT_YUVA444P16LE 130 
#define  AV_PIX_FMT_YUVA444P9BE 129 
#define  AV_PIX_FMT_YUVA444P9LE 128 

__attribute__((used)) static enum AVPixelFormat alphaless_fmt(enum AVPixelFormat fmt)
{
    switch(fmt) {
    case AV_PIX_FMT_ARGB:       return AV_PIX_FMT_RGB24;
    case AV_PIX_FMT_RGBA:       return AV_PIX_FMT_RGB24;
    case AV_PIX_FMT_ABGR:       return AV_PIX_FMT_BGR24;
    case AV_PIX_FMT_BGRA:       return AV_PIX_FMT_BGR24;
    case AV_PIX_FMT_YA8:        return AV_PIX_FMT_GRAY8;

    case AV_PIX_FMT_YUVA420P:   return AV_PIX_FMT_YUV420P;
    case AV_PIX_FMT_YUVA422P:   return AV_PIX_FMT_YUV422P;
    case AV_PIX_FMT_YUVA444P:           return AV_PIX_FMT_YUV444P;

    case AV_PIX_FMT_GBRAP:              return AV_PIX_FMT_GBRP;

    case AV_PIX_FMT_GBRAP10LE:          return AV_PIX_FMT_GBRP10;
    case AV_PIX_FMT_GBRAP10BE:          return AV_PIX_FMT_GBRP10;

    case AV_PIX_FMT_GBRAP12LE:          return AV_PIX_FMT_GBRP12;
    case AV_PIX_FMT_GBRAP12BE:          return AV_PIX_FMT_GBRP12;

    case AV_PIX_FMT_GBRAP16LE:          return AV_PIX_FMT_GBRP16;
    case AV_PIX_FMT_GBRAP16BE:          return AV_PIX_FMT_GBRP16;

    case AV_PIX_FMT_RGBA64LE:   return AV_PIX_FMT_RGB48;
    case AV_PIX_FMT_RGBA64BE:   return AV_PIX_FMT_RGB48;
    case AV_PIX_FMT_BGRA64LE:   return AV_PIX_FMT_BGR48;
    case AV_PIX_FMT_BGRA64BE:   return AV_PIX_FMT_BGR48;

    case AV_PIX_FMT_YA16BE:             return AV_PIX_FMT_GRAY16;
    case AV_PIX_FMT_YA16LE:             return AV_PIX_FMT_GRAY16;

    case AV_PIX_FMT_YUVA420P9BE:        return AV_PIX_FMT_YUV420P9;
    case AV_PIX_FMT_YUVA422P9BE:        return AV_PIX_FMT_YUV422P9;
    case AV_PIX_FMT_YUVA444P9BE:        return AV_PIX_FMT_YUV444P9;
    case AV_PIX_FMT_YUVA420P9LE:        return AV_PIX_FMT_YUV420P9;
    case AV_PIX_FMT_YUVA422P9LE:        return AV_PIX_FMT_YUV422P9;
    case AV_PIX_FMT_YUVA444P9LE:        return AV_PIX_FMT_YUV444P9;
    case AV_PIX_FMT_YUVA420P10BE:       return AV_PIX_FMT_YUV420P10;
    case AV_PIX_FMT_YUVA422P10BE:       return AV_PIX_FMT_YUV422P10;
    case AV_PIX_FMT_YUVA444P10BE:       return AV_PIX_FMT_YUV444P10;
    case AV_PIX_FMT_YUVA420P10LE:       return AV_PIX_FMT_YUV420P10;
    case AV_PIX_FMT_YUVA422P10LE:       return AV_PIX_FMT_YUV422P10;
    case AV_PIX_FMT_YUVA444P10LE:       return AV_PIX_FMT_YUV444P10;
    case AV_PIX_FMT_YUVA420P16BE:       return AV_PIX_FMT_YUV420P16;
    case AV_PIX_FMT_YUVA422P16BE:       return AV_PIX_FMT_YUV422P16;
    case AV_PIX_FMT_YUVA444P16BE:       return AV_PIX_FMT_YUV444P16;
    case AV_PIX_FMT_YUVA420P16LE:       return AV_PIX_FMT_YUV420P16;
    case AV_PIX_FMT_YUVA422P16LE:       return AV_PIX_FMT_YUV422P16;
    case AV_PIX_FMT_YUVA444P16LE:       return AV_PIX_FMT_YUV444P16;

//     case AV_PIX_FMT_AYUV64LE:
//     case AV_PIX_FMT_AYUV64BE:
//     case AV_PIX_FMT_PAL8:
    default: return AV_PIX_FMT_NONE;
    }
}