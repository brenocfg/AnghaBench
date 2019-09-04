#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  name; TYPE_2__* comp; } ;
struct TYPE_12__ {size_t const* rgba; TYPE_1__* comp; } ;
struct TYPE_11__ {int nb_planes; TYPE_5__* desc; int /*<<< orphan*/  format; scalar_t__ full_range; } ;
struct TYPE_10__ {int depth; size_t plane; size_t offset; int shift; } ;
struct TYPE_9__ {size_t* u8; int* u16; } ;
typedef  TYPE_3__ FFDrawContext ;
typedef  TYPE_4__ FFDrawColor ;
typedef  TYPE_5__ AVPixFmtDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_PIX_FMT_FLAG_RGB ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY10LE ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY12LE ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY14LE ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY16LE ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY8 ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY8A ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY9LE ; 
 int /*<<< orphan*/  AV_PIX_FMT_YA16LE ; 
 int RGB_TO_U_CCIR (size_t const,size_t const,size_t const,int /*<<< orphan*/ ) ; 
 int RGB_TO_U_JPEG (size_t const,size_t const,size_t const) ; 
 int RGB_TO_V_CCIR (size_t const,size_t const,size_t const,int /*<<< orphan*/ ) ; 
 int RGB_TO_V_JPEG (size_t const,size_t const,size_t const) ; 
 void* RGB_TO_Y_CCIR (size_t const,size_t const,size_t const) ; 
 void* RGB_TO_Y_JPEG (size_t const,size_t const,size_t const) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_fill_rgba_map (size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (size_t const*,size_t const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int,int) ; 

void ff_draw_color(FFDrawContext *draw, FFDrawColor *color, const uint8_t rgba[4])
{
    unsigned i;
    uint8_t rgba_map[4];

    if (rgba != color->rgba)
        memcpy(color->rgba, rgba, sizeof(color->rgba));
    if ((draw->desc->flags & AV_PIX_FMT_FLAG_RGB) &&
        ff_fill_rgba_map(rgba_map, draw->format) >= 0) {
        if (draw->nb_planes == 1) {
            for (i = 0; i < 4; i++) {
                color->comp[0].u8[rgba_map[i]] = rgba[i];
                if (draw->desc->comp[rgba_map[i]].depth > 8) {
                    color->comp[0].u16[rgba_map[i]] = color->comp[0].u8[rgba_map[i]] << 8;
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                color->comp[rgba_map[i]].u8[0] = rgba[i];
                if (draw->desc->comp[rgba_map[i]].depth > 8)
                    color->comp[rgba_map[i]].u16[0] = color->comp[rgba_map[i]].u8[0] << (draw->desc->comp[rgba_map[i]].depth - 8);
            }
        }
    } else if (draw->nb_planes >= 2) {
        /* assume YUV */
        const AVPixFmtDescriptor *desc = draw->desc;
        color->comp[desc->comp[0].plane].u8[desc->comp[0].offset] = draw->full_range ? RGB_TO_Y_JPEG(rgba[0], rgba[1], rgba[2]) : RGB_TO_Y_CCIR(rgba[0], rgba[1], rgba[2]);
        color->comp[desc->comp[1].plane].u8[desc->comp[1].offset] = draw->full_range ? RGB_TO_U_JPEG(rgba[0], rgba[1], rgba[2]) : RGB_TO_U_CCIR(rgba[0], rgba[1], rgba[2], 0);
        color->comp[desc->comp[2].plane].u8[desc->comp[2].offset] = draw->full_range ? RGB_TO_V_JPEG(rgba[0], rgba[1], rgba[2]) : RGB_TO_V_CCIR(rgba[0], rgba[1], rgba[2], 0);
        color->comp[3].u8[0] = rgba[3];
#define EXPAND(compn) \
        if (desc->comp[compn].depth > 8) \
            color->comp[desc->comp[compn].plane].u16[desc->comp[compn].offset] = \
            color->comp[desc->comp[compn].plane].u8[desc->comp[compn].offset] << \
                (draw->desc->comp[compn].depth + draw->desc->comp[compn].shift - 8)
        EXPAND(3);
        EXPAND(2);
        EXPAND(1);
        EXPAND(0);
    } else if (draw->format == AV_PIX_FMT_GRAY8 || draw->format == AV_PIX_FMT_GRAY8A ||
               draw->format == AV_PIX_FMT_GRAY16LE || draw->format == AV_PIX_FMT_YA16LE ||
               draw->format == AV_PIX_FMT_GRAY9LE  ||
               draw->format == AV_PIX_FMT_GRAY10LE ||
               draw->format == AV_PIX_FMT_GRAY12LE ||
               draw->format == AV_PIX_FMT_GRAY14LE) {
        const AVPixFmtDescriptor *desc = draw->desc;
        color->comp[0].u8[0] = RGB_TO_Y_CCIR(rgba[0], rgba[1], rgba[2]);
        EXPAND(0);
        color->comp[1].u8[0] = rgba[3];
        EXPAND(1);
    } else {
        av_log(NULL, AV_LOG_WARNING,
               "Color conversion not implemented for %s\n", draw->desc->name);
        memset(color, 128, sizeof(*color));
    }
}