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
struct TYPE_13__ {int /*<<< orphan*/  format; TYPE_1__* dst; } ;
struct TYPE_12__ {TYPE_2__* comp; } ;
struct TYPE_11__ {int step; int interpolation; int /*<<< orphan*/  interp; int /*<<< orphan*/  rgba_map; } ;
struct TYPE_10__ {int depth; } ;
struct TYPE_9__ {TYPE_3__* priv; } ;
typedef  TYPE_3__ LUT3DContext ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFilterLink ;

/* Variables and functions */
#define  AV_PIX_FMT_BGR48 144 
#define  AV_PIX_FMT_BGRA64 143 
#define  AV_PIX_FMT_GBRAP 142 
#define  AV_PIX_FMT_GBRAP10 141 
#define  AV_PIX_FMT_GBRAP12 140 
#define  AV_PIX_FMT_GBRAP16 139 
#define  AV_PIX_FMT_GBRP 138 
#define  AV_PIX_FMT_GBRP10 137 
#define  AV_PIX_FMT_GBRP12 136 
#define  AV_PIX_FMT_GBRP14 135 
#define  AV_PIX_FMT_GBRP16 134 
#define  AV_PIX_FMT_GBRP9 133 
#define  AV_PIX_FMT_RGB48 132 
#define  AV_PIX_FMT_RGBA64 131 
#define  INTERPOLATE_NEAREST 130 
#define  INTERPOLATE_TETRAHEDRAL 129 
#define  INTERPOLATE_TRILINEAR 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int av_get_padded_bits_per_pixel (TYPE_4__ const*) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_fill_rgba_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interp_16_nearest ; 
 int /*<<< orphan*/  interp_16_nearest_p10 ; 
 int /*<<< orphan*/  interp_16_nearest_p12 ; 
 int /*<<< orphan*/  interp_16_nearest_p14 ; 
 int /*<<< orphan*/  interp_16_nearest_p16 ; 
 int /*<<< orphan*/  interp_16_nearest_p9 ; 
 int /*<<< orphan*/  interp_16_tetrahedral ; 
 int /*<<< orphan*/  interp_16_tetrahedral_p10 ; 
 int /*<<< orphan*/  interp_16_tetrahedral_p12 ; 
 int /*<<< orphan*/  interp_16_tetrahedral_p14 ; 
 int /*<<< orphan*/  interp_16_tetrahedral_p16 ; 
 int /*<<< orphan*/  interp_16_tetrahedral_p9 ; 
 int /*<<< orphan*/  interp_16_trilinear ; 
 int /*<<< orphan*/  interp_16_trilinear_p10 ; 
 int /*<<< orphan*/  interp_16_trilinear_p12 ; 
 int /*<<< orphan*/  interp_16_trilinear_p14 ; 
 int /*<<< orphan*/  interp_16_trilinear_p16 ; 
 int /*<<< orphan*/  interp_16_trilinear_p9 ; 
 int /*<<< orphan*/  interp_8_nearest ; 
 int /*<<< orphan*/  interp_8_nearest_p8 ; 
 int /*<<< orphan*/  interp_8_tetrahedral ; 
 int /*<<< orphan*/  interp_8_tetrahedral_p8 ; 
 int /*<<< orphan*/  interp_8_trilinear ; 
 int /*<<< orphan*/  interp_8_trilinear_p8 ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    int depth, is16bit = 0, planar = 0;
    LUT3DContext *lut3d = inlink->dst->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);

    depth = desc->comp[0].depth;

    switch (inlink->format) {
    case AV_PIX_FMT_RGB48:
    case AV_PIX_FMT_BGR48:
    case AV_PIX_FMT_RGBA64:
    case AV_PIX_FMT_BGRA64:
        is16bit = 1;
        break;
    case AV_PIX_FMT_GBRP9:
    case AV_PIX_FMT_GBRP10:
    case AV_PIX_FMT_GBRP12:
    case AV_PIX_FMT_GBRP14:
    case AV_PIX_FMT_GBRP16:
    case AV_PIX_FMT_GBRAP10:
    case AV_PIX_FMT_GBRAP12:
    case AV_PIX_FMT_GBRAP16:
        is16bit = 1;
    case AV_PIX_FMT_GBRP:
    case AV_PIX_FMT_GBRAP:
        planar = 1;
        break;
    }

    ff_fill_rgba_map(lut3d->rgba_map, inlink->format);
    lut3d->step = av_get_padded_bits_per_pixel(desc) >> (3 + is16bit);

#define SET_FUNC(name) do {                                     \
    if (planar) {                                               \
        switch (depth) {                                        \
        case  8: lut3d->interp = interp_8_##name##_p8;   break; \
        case  9: lut3d->interp = interp_16_##name##_p9;  break; \
        case 10: lut3d->interp = interp_16_##name##_p10; break; \
        case 12: lut3d->interp = interp_16_##name##_p12; break; \
        case 14: lut3d->interp = interp_16_##name##_p14; break; \
        case 16: lut3d->interp = interp_16_##name##_p16; break; \
        }                                                       \
    } else if (is16bit) { lut3d->interp = interp_16_##name;     \
    } else {       lut3d->interp = interp_8_##name; }           \
} while (0)

    switch (lut3d->interpolation) {
    case INTERPOLATE_NEAREST:     SET_FUNC(nearest);        break;
    case INTERPOLATE_TRILINEAR:   SET_FUNC(trilinear);      break;
    case INTERPOLATE_TETRAHEDRAL: SET_FUNC(tetrahedral);    break;
    default:
        av_assert0(0);
    }

    return 0;
}