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
typedef  int uint8_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 size_t ALPHA ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_0BGR 163 
#define  AV_PIX_FMT_0RGB 162 
#define  AV_PIX_FMT_ABGR 161 
#define  AV_PIX_FMT_ARGB 160 
#define  AV_PIX_FMT_BGR0 159 
#define  AV_PIX_FMT_BGR24 158 
#define  AV_PIX_FMT_BGR48BE 157 
#define  AV_PIX_FMT_BGR48LE 156 
#define  AV_PIX_FMT_BGRA 155 
#define  AV_PIX_FMT_BGRA64BE 154 
#define  AV_PIX_FMT_BGRA64LE 153 
#define  AV_PIX_FMT_GBRAP 152 
#define  AV_PIX_FMT_GBRAP10BE 151 
#define  AV_PIX_FMT_GBRAP10LE 150 
#define  AV_PIX_FMT_GBRAP12BE 149 
#define  AV_PIX_FMT_GBRAP12LE 148 
#define  AV_PIX_FMT_GBRAP16BE 147 
#define  AV_PIX_FMT_GBRAP16LE 146 
#define  AV_PIX_FMT_GBRP 145 
#define  AV_PIX_FMT_GBRP10BE 144 
#define  AV_PIX_FMT_GBRP10LE 143 
#define  AV_PIX_FMT_GBRP12BE 142 
#define  AV_PIX_FMT_GBRP12LE 141 
#define  AV_PIX_FMT_GBRP14BE 140 
#define  AV_PIX_FMT_GBRP14LE 139 
#define  AV_PIX_FMT_GBRP16BE 138 
#define  AV_PIX_FMT_GBRP16LE 137 
#define  AV_PIX_FMT_GBRP9BE 136 
#define  AV_PIX_FMT_GBRP9LE 135 
#define  AV_PIX_FMT_RGB0 134 
#define  AV_PIX_FMT_RGB24 133 
#define  AV_PIX_FMT_RGB48BE 132 
#define  AV_PIX_FMT_RGB48LE 131 
#define  AV_PIX_FMT_RGBA 130 
#define  AV_PIX_FMT_RGBA64BE 129 
#define  AV_PIX_FMT_RGBA64LE 128 
 size_t BLUE ; 
 int /*<<< orphan*/  EINVAL ; 
 size_t GREEN ; 
 size_t RED ; 

int ff_fill_rgba_map(uint8_t *rgba_map, enum AVPixelFormat pix_fmt)
{
    switch (pix_fmt) {
    case AV_PIX_FMT_0RGB:
    case AV_PIX_FMT_ARGB:  rgba_map[ALPHA] = 0; rgba_map[RED  ] = 1; rgba_map[GREEN] = 2; rgba_map[BLUE ] = 3; break;
    case AV_PIX_FMT_0BGR:
    case AV_PIX_FMT_ABGR:  rgba_map[ALPHA] = 0; rgba_map[BLUE ] = 1; rgba_map[GREEN] = 2; rgba_map[RED  ] = 3; break;
    case AV_PIX_FMT_RGB48LE:
    case AV_PIX_FMT_RGB48BE:
    case AV_PIX_FMT_RGBA64BE:
    case AV_PIX_FMT_RGBA64LE:
    case AV_PIX_FMT_RGB0:
    case AV_PIX_FMT_RGBA:
    case AV_PIX_FMT_RGB24: rgba_map[RED  ] = 0; rgba_map[GREEN] = 1; rgba_map[BLUE ] = 2; rgba_map[ALPHA] = 3; break;
    case AV_PIX_FMT_BGR48LE:
    case AV_PIX_FMT_BGR48BE:
    case AV_PIX_FMT_BGRA64BE:
    case AV_PIX_FMT_BGRA64LE:
    case AV_PIX_FMT_BGRA:
    case AV_PIX_FMT_BGR0:
    case AV_PIX_FMT_BGR24: rgba_map[BLUE ] = 0; rgba_map[GREEN] = 1; rgba_map[RED  ] = 2; rgba_map[ALPHA] = 3; break;
    case AV_PIX_FMT_GBRP9LE:
    case AV_PIX_FMT_GBRP9BE:
    case AV_PIX_FMT_GBRP10LE:
    case AV_PIX_FMT_GBRP10BE:
    case AV_PIX_FMT_GBRP12LE:
    case AV_PIX_FMT_GBRP12BE:
    case AV_PIX_FMT_GBRP14LE:
    case AV_PIX_FMT_GBRP14BE:
    case AV_PIX_FMT_GBRP16LE:
    case AV_PIX_FMT_GBRP16BE:
    case AV_PIX_FMT_GBRAP:
    case AV_PIX_FMT_GBRAP10LE:
    case AV_PIX_FMT_GBRAP10BE:
    case AV_PIX_FMT_GBRAP12LE:
    case AV_PIX_FMT_GBRAP12BE:
    case AV_PIX_FMT_GBRAP16LE:
    case AV_PIX_FMT_GBRAP16BE:
    case AV_PIX_FMT_GBRP:  rgba_map[GREEN] = 0; rgba_map[BLUE ] = 1; rgba_map[RED  ] = 2; rgba_map[ALPHA] = 3; break;
    default:                    /* unsupported */
        return AVERROR(EINVAL);
    }
    return 0;
}