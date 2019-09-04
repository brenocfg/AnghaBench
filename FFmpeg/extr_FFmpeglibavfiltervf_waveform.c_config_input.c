#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int bits; int max; int intensity; int fintensity; int filter; int size; int mode; int mirror; int* grat_yuva_color; int graticule; int rgb; int /*<<< orphan*/  bgopacity; int /*<<< orphan*/ * bg_color; void* nb_glines; int /*<<< orphan*/ * glines; int /*<<< orphan*/  scale; int /*<<< orphan*/  graticulef; int /*<<< orphan*/  waveform_slice; TYPE_6__* desc; scalar_t__* shift_h; scalar_t__* shift_w; int /*<<< orphan*/  ncomp; } ;
typedef  TYPE_2__ WaveformContext ;
struct TYPE_11__ {scalar_t__ log2_chroma_h; scalar_t__ log2_chroma_w; TYPE_1__* comp; int /*<<< orphan*/  nb_components; } ;
struct TYPE_10__ {TYPE_2__* priv; } ;
struct TYPE_9__ {int format; TYPE_4__* dst; } ;
struct TYPE_7__ {int depth; } ;
typedef  int /*<<< orphan*/  GraticuleLines ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
#define  ACOLOR 142 
#define  AFLAT 141 
#define  AV_PIX_FMT_GBRAP 140 
#define  AV_PIX_FMT_GBRP 139 
#define  AV_PIX_FMT_GBRP10 138 
#define  AV_PIX_FMT_GBRP12 137 
#define  AV_PIX_FMT_GBRP9 136 
#define  CHROMA 135 
#define  COLOR 134 
#define  DIGITAL 133 
 void* FF_ARRAY_ELEMS (scalar_t__) ; 
#define  FLAT 132 
#define  IRE 131 
#define  LOWPASS 130 
#define  MILLIVOLTS 129 
#define  XFLAT 128 
 int /*<<< orphan*/  acolor16_column ; 
 int /*<<< orphan*/  acolor16_column_mirror ; 
 int /*<<< orphan*/  acolor16_row ; 
 int /*<<< orphan*/  acolor16_row_mirror ; 
 int /*<<< orphan*/  acolor_column ; 
 int /*<<< orphan*/  acolor_column_mirror ; 
 int /*<<< orphan*/  acolor_row ; 
 int /*<<< orphan*/  acolor_row_mirror ; 
 int /*<<< orphan*/  aflat16_column ; 
 int /*<<< orphan*/  aflat16_column_mirror ; 
 int /*<<< orphan*/  aflat16_row ; 
 int /*<<< orphan*/  aflat16_row_mirror ; 
 int /*<<< orphan*/  aflat_column ; 
 int /*<<< orphan*/  aflat_column_mirror ; 
 scalar_t__ aflat_digital10 ; 
 scalar_t__ aflat_digital12 ; 
 scalar_t__ aflat_digital8 ; 
 scalar_t__ aflat_digital9 ; 
 scalar_t__ aflat_ire10 ; 
 scalar_t__ aflat_ire12 ; 
 scalar_t__ aflat_ire8 ; 
 scalar_t__ aflat_ire9 ; 
 scalar_t__ aflat_millivolts10 ; 
 scalar_t__ aflat_millivolts12 ; 
 scalar_t__ aflat_millivolts8 ; 
 scalar_t__ aflat_millivolts9 ; 
 int /*<<< orphan*/  aflat_row ; 
 int /*<<< orphan*/  aflat_row_mirror ; 
 TYPE_6__* av_pix_fmt_desc_get (int) ; 
 int /*<<< orphan*/  black_gbrp_color ; 
 int /*<<< orphan*/  black_yuva_color ; 
 int /*<<< orphan*/  chroma16_column ; 
 int /*<<< orphan*/  chroma16_column_mirror ; 
 int /*<<< orphan*/  chroma16_row ; 
 int /*<<< orphan*/  chroma16_row_mirror ; 
 int /*<<< orphan*/  chroma_column ; 
 int /*<<< orphan*/  chroma_column_mirror ; 
 scalar_t__ chroma_digital10 ; 
 scalar_t__ chroma_digital12 ; 
 scalar_t__ chroma_digital8 ; 
 scalar_t__ chroma_digital9 ; 
 int /*<<< orphan*/  chroma_row ; 
 int /*<<< orphan*/  chroma_row_mirror ; 
 int /*<<< orphan*/  color16_column ; 
 int /*<<< orphan*/  color16_column_mirror ; 
 int /*<<< orphan*/  color16_row ; 
 int /*<<< orphan*/  color16_row_mirror ; 
 int /*<<< orphan*/  color_column ; 
 int /*<<< orphan*/  color_column_mirror ; 
 int /*<<< orphan*/  color_row ; 
 int /*<<< orphan*/  color_row_mirror ; 
 scalar_t__ digital10 ; 
 scalar_t__ digital12 ; 
 scalar_t__ digital8 ; 
 scalar_t__ digital9 ; 
 int /*<<< orphan*/  flat16_column ; 
 int /*<<< orphan*/  flat16_column_mirror ; 
 int /*<<< orphan*/  flat16_row ; 
 int /*<<< orphan*/  flat16_row_mirror ; 
 int /*<<< orphan*/  flat_column ; 
 int /*<<< orphan*/  flat_column_mirror ; 
 scalar_t__ flat_digital10 ; 
 scalar_t__ flat_digital12 ; 
 scalar_t__ flat_digital8 ; 
 scalar_t__ flat_digital9 ; 
 scalar_t__ flat_ire10 ; 
 scalar_t__ flat_ire12 ; 
 scalar_t__ flat_ire8 ; 
 scalar_t__ flat_ire9 ; 
 scalar_t__ flat_millivolts10 ; 
 scalar_t__ flat_millivolts12 ; 
 scalar_t__ flat_millivolts8 ; 
 scalar_t__ flat_millivolts9 ; 
 int /*<<< orphan*/  flat_row ; 
 int /*<<< orphan*/  flat_row_mirror ; 
 int /*<<< orphan*/  graticule16_column ; 
 int /*<<< orphan*/  graticule16_row ; 
 int /*<<< orphan*/  graticule_column ; 
 int /*<<< orphan*/  graticule_none ; 
 int /*<<< orphan*/  graticule_row ; 
 scalar_t__ ire10 ; 
 scalar_t__ ire12 ; 
 scalar_t__ ire8 ; 
 scalar_t__ ire9 ; 
 int /*<<< orphan*/  lowpass16_column ; 
 int /*<<< orphan*/  lowpass16_column_mirror ; 
 int /*<<< orphan*/  lowpass16_row ; 
 int /*<<< orphan*/  lowpass16_row_mirror ; 
 int /*<<< orphan*/  lowpass_column ; 
 int /*<<< orphan*/  lowpass_column_mirror ; 
 int /*<<< orphan*/  lowpass_row ; 
 int /*<<< orphan*/  lowpass_row_mirror ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ millivolts10 ; 
 scalar_t__ millivolts12 ; 
 scalar_t__ millivolts8 ; 
 scalar_t__ millivolts9 ; 
 int /*<<< orphan*/  xflat16_column ; 
 int /*<<< orphan*/  xflat16_column_mirror ; 
 int /*<<< orphan*/  xflat16_row ; 
 int /*<<< orphan*/  xflat16_row_mirror ; 
 int /*<<< orphan*/  xflat_column ; 
 int /*<<< orphan*/  xflat_column_mirror ; 
 int /*<<< orphan*/  xflat_row ; 
 int /*<<< orphan*/  xflat_row_mirror ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    WaveformContext *s = ctx->priv;

    s->desc  = av_pix_fmt_desc_get(inlink->format);
    s->ncomp = s->desc->nb_components;
    s->bits = s->desc->comp[0].depth;
    s->max = 1 << s->bits;
    s->intensity = s->fintensity * (s->max - 1);

    s->shift_w[0] = s->shift_w[3] = 0;
    s->shift_h[0] = s->shift_h[3] = 0;
    s->shift_w[1] = s->shift_w[2] = s->desc->log2_chroma_w;
    s->shift_h[1] = s->shift_h[2] = s->desc->log2_chroma_h;

    s->graticulef = graticule_none;

    switch (s->filter) {
    case XFLAT:
    case AFLAT: s->size = 256 * 2; break;
    case FLAT:  s->size = 256 * 3; break;
    default:    s->size = 256;     break;
    }

    switch (s->filter | ((s->bits > 8) << 4) |
            (s->mode << 8) | (s->mirror << 12)) {
    case 0x1100: s->waveform_slice = lowpass_column_mirror; break;
    case 0x1000: s->waveform_slice = lowpass_row_mirror;    break;
    case 0x0100: s->waveform_slice = lowpass_column;        break;
    case 0x0000: s->waveform_slice = lowpass_row;           break;
    case 0x1110: s->waveform_slice = lowpass16_column_mirror; break;
    case 0x1010: s->waveform_slice = lowpass16_row_mirror;    break;
    case 0x0110: s->waveform_slice = lowpass16_column;        break;
    case 0x0010: s->waveform_slice = lowpass16_row;           break;
    case 0x1101: s->waveform_slice = flat_column_mirror; break;
    case 0x1001: s->waveform_slice = flat_row_mirror;    break;
    case 0x0101: s->waveform_slice = flat_column;        break;
    case 0x0001: s->waveform_slice = flat_row;           break;
    case 0x1111: s->waveform_slice = flat16_column_mirror; break;
    case 0x1011: s->waveform_slice = flat16_row_mirror;    break;
    case 0x0111: s->waveform_slice = flat16_column;        break;
    case 0x0011: s->waveform_slice = flat16_row;           break;
    case 0x1102: s->waveform_slice = aflat_column_mirror; break;
    case 0x1002: s->waveform_slice = aflat_row_mirror;    break;
    case 0x0102: s->waveform_slice = aflat_column;        break;
    case 0x0002: s->waveform_slice = aflat_row;           break;
    case 0x1112: s->waveform_slice = aflat16_column_mirror; break;
    case 0x1012: s->waveform_slice = aflat16_row_mirror;    break;
    case 0x0112: s->waveform_slice = aflat16_column;        break;
    case 0x0012: s->waveform_slice = aflat16_row;           break;
    case 0x1103: s->waveform_slice = chroma_column_mirror; break;
    case 0x1003: s->waveform_slice = chroma_row_mirror;    break;
    case 0x0103: s->waveform_slice = chroma_column;        break;
    case 0x0003: s->waveform_slice = chroma_row;           break;
    case 0x1113: s->waveform_slice = chroma16_column_mirror; break;
    case 0x1013: s->waveform_slice = chroma16_row_mirror;    break;
    case 0x0113: s->waveform_slice = chroma16_column;        break;
    case 0x0013: s->waveform_slice = chroma16_row;           break;
    case 0x1104: s->waveform_slice = color_column_mirror; break;
    case 0x1004: s->waveform_slice = color_row_mirror;    break;
    case 0x0104: s->waveform_slice = color_column;        break;
    case 0x0004: s->waveform_slice = color_row;           break;
    case 0x1114: s->waveform_slice = color16_column_mirror; break;
    case 0x1014: s->waveform_slice = color16_row_mirror;    break;
    case 0x0114: s->waveform_slice = color16_column;        break;
    case 0x0014: s->waveform_slice = color16_row;           break;
    case 0x1105: s->waveform_slice = acolor_column_mirror; break;
    case 0x1005: s->waveform_slice = acolor_row_mirror;    break;
    case 0x0105: s->waveform_slice = acolor_column;        break;
    case 0x0005: s->waveform_slice = acolor_row;           break;
    case 0x1115: s->waveform_slice = acolor16_column_mirror; break;
    case 0x1015: s->waveform_slice = acolor16_row_mirror;    break;
    case 0x0115: s->waveform_slice = acolor16_column;        break;
    case 0x0015: s->waveform_slice = acolor16_row;           break;
    case 0x1106: s->waveform_slice = xflat_column_mirror; break;
    case 0x1006: s->waveform_slice = xflat_row_mirror;    break;
    case 0x0106: s->waveform_slice = xflat_column;        break;
    case 0x0006: s->waveform_slice = xflat_row;           break;
    case 0x1116: s->waveform_slice = xflat16_column_mirror; break;
    case 0x1016: s->waveform_slice = xflat16_row_mirror;    break;
    case 0x0116: s->waveform_slice = xflat16_column;        break;
    case 0x0016: s->waveform_slice = xflat16_row;           break;
    }

    s->grat_yuva_color[0] = 255;
    s->grat_yuva_color[2] = s->graticule == 2 ? 255 : 0;
    s->grat_yuva_color[3] = 255;

    switch (s->filter) {
    case LOWPASS:
    case COLOR:
    case ACOLOR:
    case CHROMA:
    case AFLAT:
    case XFLAT:
    case FLAT:
        if (s->graticule && s->mode == 1)
            s->graticulef = s->bits > 8 ? graticule16_column : graticule_column;
        else if (s->graticule && s->mode == 0)
            s->graticulef = s->bits > 8 ? graticule16_row : graticule_row;
        break;
    }

    switch (s->filter) {
    case COLOR:
    case ACOLOR:
    case LOWPASS:
        switch (s->scale) {
        case DIGITAL:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)digital8;  s->nb_glines = FF_ARRAY_ELEMS(digital8);  break;
            case  9: s->glines = (GraticuleLines *)digital9;  s->nb_glines = FF_ARRAY_ELEMS(digital9);  break;
            case 10: s->glines = (GraticuleLines *)digital10; s->nb_glines = FF_ARRAY_ELEMS(digital10); break;
            case 12: s->glines = (GraticuleLines *)digital12; s->nb_glines = FF_ARRAY_ELEMS(digital12); break;
            }
            break;
        case MILLIVOLTS:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)millivolts8;  s->nb_glines = FF_ARRAY_ELEMS(millivolts8);  break;
            case  9: s->glines = (GraticuleLines *)millivolts9;  s->nb_glines = FF_ARRAY_ELEMS(millivolts9);  break;
            case 10: s->glines = (GraticuleLines *)millivolts10; s->nb_glines = FF_ARRAY_ELEMS(millivolts10); break;
            case 12: s->glines = (GraticuleLines *)millivolts12; s->nb_glines = FF_ARRAY_ELEMS(millivolts12); break;
            }
            break;
        case IRE:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)ire8;  s->nb_glines = FF_ARRAY_ELEMS(ire8);  break;
            case  9: s->glines = (GraticuleLines *)ire9;  s->nb_glines = FF_ARRAY_ELEMS(ire9);  break;
            case 10: s->glines = (GraticuleLines *)ire10; s->nb_glines = FF_ARRAY_ELEMS(ire10); break;
            case 12: s->glines = (GraticuleLines *)ire12; s->nb_glines = FF_ARRAY_ELEMS(ire12); break;
            }
            break;
        }
        break;
    case CHROMA:
        switch (s->scale) {
        case DIGITAL:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)chroma_digital8;  s->nb_glines = FF_ARRAY_ELEMS(chroma_digital8);  break;
            case  9: s->glines = (GraticuleLines *)chroma_digital9;  s->nb_glines = FF_ARRAY_ELEMS(chroma_digital9);  break;
            case 10: s->glines = (GraticuleLines *)chroma_digital10; s->nb_glines = FF_ARRAY_ELEMS(chroma_digital10); break;
            case 12: s->glines = (GraticuleLines *)chroma_digital12; s->nb_glines = FF_ARRAY_ELEMS(chroma_digital12); break;
            }
            break;
        case MILLIVOLTS:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)millivolts8;  s->nb_glines = FF_ARRAY_ELEMS(millivolts8);  break;
            case  9: s->glines = (GraticuleLines *)millivolts9;  s->nb_glines = FF_ARRAY_ELEMS(millivolts9);  break;
            case 10: s->glines = (GraticuleLines *)millivolts10; s->nb_glines = FF_ARRAY_ELEMS(millivolts10); break;
            case 12: s->glines = (GraticuleLines *)millivolts12; s->nb_glines = FF_ARRAY_ELEMS(millivolts12); break;
            }
            break;
        case IRE:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)ire8;  s->nb_glines = FF_ARRAY_ELEMS(ire8);  break;
            case  9: s->glines = (GraticuleLines *)ire9;  s->nb_glines = FF_ARRAY_ELEMS(ire9);  break;
            case 10: s->glines = (GraticuleLines *)ire10; s->nb_glines = FF_ARRAY_ELEMS(ire10); break;
            case 12: s->glines = (GraticuleLines *)ire12; s->nb_glines = FF_ARRAY_ELEMS(ire12); break;
            }
            break;
        }
        break;
    case XFLAT:
    case AFLAT:
        switch (s->scale) {
        case DIGITAL:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)aflat_digital8;  s->nb_glines = FF_ARRAY_ELEMS(aflat_digital8);  break;
            case  9: s->glines = (GraticuleLines *)aflat_digital9;  s->nb_glines = FF_ARRAY_ELEMS(aflat_digital9);  break;
            case 10: s->glines = (GraticuleLines *)aflat_digital10; s->nb_glines = FF_ARRAY_ELEMS(aflat_digital10); break;
            case 12: s->glines = (GraticuleLines *)aflat_digital12; s->nb_glines = FF_ARRAY_ELEMS(aflat_digital12); break;
            }
            break;
        case MILLIVOLTS:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)aflat_millivolts8;  s->nb_glines = FF_ARRAY_ELEMS(aflat_millivolts8);  break;
            case  9: s->glines = (GraticuleLines *)aflat_millivolts9;  s->nb_glines = FF_ARRAY_ELEMS(aflat_millivolts9);  break;
            case 10: s->glines = (GraticuleLines *)aflat_millivolts10; s->nb_glines = FF_ARRAY_ELEMS(aflat_millivolts10); break;
            case 12: s->glines = (GraticuleLines *)aflat_millivolts12; s->nb_glines = FF_ARRAY_ELEMS(aflat_millivolts12); break;
            }
            break;
        case IRE:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)aflat_ire8;  s->nb_glines = FF_ARRAY_ELEMS(aflat_ire8);  break;
            case  9: s->glines = (GraticuleLines *)aflat_ire9;  s->nb_glines = FF_ARRAY_ELEMS(aflat_ire9);  break;
            case 10: s->glines = (GraticuleLines *)aflat_ire10; s->nb_glines = FF_ARRAY_ELEMS(aflat_ire10); break;
            case 12: s->glines = (GraticuleLines *)aflat_ire12; s->nb_glines = FF_ARRAY_ELEMS(aflat_ire12); break;
            }
            break;
        }
        break;
    case FLAT:
        switch (s->scale) {
        case DIGITAL:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)flat_digital8;  s->nb_glines = FF_ARRAY_ELEMS(flat_digital8);  break;
            case  9: s->glines = (GraticuleLines *)flat_digital9;  s->nb_glines = FF_ARRAY_ELEMS(flat_digital9);  break;
            case 10: s->glines = (GraticuleLines *)flat_digital10; s->nb_glines = FF_ARRAY_ELEMS(flat_digital10); break;
            case 12: s->glines = (GraticuleLines *)flat_digital12; s->nb_glines = FF_ARRAY_ELEMS(flat_digital12); break;
            }
            break;
        case MILLIVOLTS:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)flat_millivolts8;  s->nb_glines = FF_ARRAY_ELEMS(flat_millivolts8);  break;
            case  9: s->glines = (GraticuleLines *)flat_millivolts9;  s->nb_glines = FF_ARRAY_ELEMS(flat_millivolts9);  break;
            case 10: s->glines = (GraticuleLines *)flat_millivolts10; s->nb_glines = FF_ARRAY_ELEMS(flat_millivolts10); break;
            case 12: s->glines = (GraticuleLines *)flat_millivolts12; s->nb_glines = FF_ARRAY_ELEMS(flat_millivolts12); break;
            }
            break;
        case IRE:
            switch (s->bits) {
            case  8: s->glines = (GraticuleLines *)flat_ire8;  s->nb_glines = FF_ARRAY_ELEMS(flat_ire8);  break;
            case  9: s->glines = (GraticuleLines *)flat_ire9;  s->nb_glines = FF_ARRAY_ELEMS(flat_ire9);  break;
            case 10: s->glines = (GraticuleLines *)flat_ire10; s->nb_glines = FF_ARRAY_ELEMS(flat_ire10); break;
            case 12: s->glines = (GraticuleLines *)flat_ire12; s->nb_glines = FF_ARRAY_ELEMS(flat_ire12); break;
            }
            break;
        }
        break;
    }

    s->size = s->size << (s->bits - 8);

    switch (inlink->format) {
    case AV_PIX_FMT_GBRAP:
    case AV_PIX_FMT_GBRP:
    case AV_PIX_FMT_GBRP9:
    case AV_PIX_FMT_GBRP10:
    case AV_PIX_FMT_GBRP12:
        s->rgb = 1;
        memcpy(s->bg_color, black_gbrp_color, sizeof(s->bg_color));
        break;
    default:
        memcpy(s->bg_color, black_yuva_color, sizeof(s->bg_color));
    }

    s->bg_color[3] *= s->bgopacity;

    return 0;
}