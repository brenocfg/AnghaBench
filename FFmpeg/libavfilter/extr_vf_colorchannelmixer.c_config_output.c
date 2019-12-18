#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* priv; } ;
struct TYPE_11__ {int /*<<< orphan*/  format; TYPE_5__* src; } ;
struct TYPE_10__ {TYPE_1__* comp; } ;
struct TYPE_9__ {int* buffer; int*** lut; int rr; int rg; int rb; int ra; int gr; int gg; int gb; int ga; int br; int bg; int bb; int ba; int ar; int ag; int ab; int aa; int /*<<< orphan*/  filter_slice; int /*<<< orphan*/  rgba_map; } ;
struct TYPE_8__ {int depth; } ;
typedef  TYPE_2__ ColorChannelMixerContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 size_t A ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_0BGR 151 
#define  AV_PIX_FMT_0RGB 150 
#define  AV_PIX_FMT_ABGR 149 
#define  AV_PIX_FMT_ARGB 148 
#define  AV_PIX_FMT_BGR0 147 
#define  AV_PIX_FMT_BGR24 146 
#define  AV_PIX_FMT_BGR48 145 
#define  AV_PIX_FMT_BGRA 144 
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
#define  AV_PIX_FMT_RGB0 132 
#define  AV_PIX_FMT_RGB24 131 
#define  AV_PIX_FMT_RGB48 130 
#define  AV_PIX_FMT_RGBA 129 
#define  AV_PIX_FMT_RGBA64 128 
 size_t B ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t G ; 
 size_t R ; 
 int* av_malloc (int) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_fill_rgba_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_slice_gbrap ; 
 int /*<<< orphan*/  filter_slice_gbrap10 ; 
 int /*<<< orphan*/  filter_slice_gbrap12 ; 
 int /*<<< orphan*/  filter_slice_gbrap16 ; 
 int /*<<< orphan*/  filter_slice_gbrp ; 
 int /*<<< orphan*/  filter_slice_gbrp10 ; 
 int /*<<< orphan*/  filter_slice_gbrp12 ; 
 int /*<<< orphan*/  filter_slice_gbrp14 ; 
 int /*<<< orphan*/  filter_slice_gbrp16 ; 
 int /*<<< orphan*/  filter_slice_gbrp9 ; 
 int /*<<< orphan*/  filter_slice_rgb0 ; 
 int /*<<< orphan*/  filter_slice_rgb24 ; 
 int /*<<< orphan*/  filter_slice_rgb48 ; 
 int /*<<< orphan*/  filter_slice_rgba ; 
 int /*<<< orphan*/  filter_slice_rgba64 ; 
 void* lrint (int) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    ColorChannelMixerContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(outlink->format);
    const int depth = desc->comp[0].depth;
    int i, j, size, *buffer = s->buffer;

    ff_fill_rgba_map(s->rgba_map, outlink->format);

    size = 1 << depth;
    if (!s->buffer) {
        s->buffer = buffer = av_malloc(16 * size * sizeof(*s->buffer));
        if (!s->buffer)
            return AVERROR(ENOMEM);

        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++, buffer += size)
                s->lut[i][j] = buffer;
    }

    for (i = 0; i < size; i++) {
        s->lut[R][R][i] = lrint(i * s->rr);
        s->lut[R][G][i] = lrint(i * s->rg);
        s->lut[R][B][i] = lrint(i * s->rb);
        s->lut[R][A][i] = lrint(i * s->ra);

        s->lut[G][R][i] = lrint(i * s->gr);
        s->lut[G][G][i] = lrint(i * s->gg);
        s->lut[G][B][i] = lrint(i * s->gb);
        s->lut[G][A][i] = lrint(i * s->ga);

        s->lut[B][R][i] = lrint(i * s->br);
        s->lut[B][G][i] = lrint(i * s->bg);
        s->lut[B][B][i] = lrint(i * s->bb);
        s->lut[B][A][i] = lrint(i * s->ba);

        s->lut[A][R][i] = lrint(i * s->ar);
        s->lut[A][G][i] = lrint(i * s->ag);
        s->lut[A][B][i] = lrint(i * s->ab);
        s->lut[A][A][i] = lrint(i * s->aa);
    }

    switch (outlink->format) {
    case AV_PIX_FMT_BGR24:
    case AV_PIX_FMT_RGB24:
        s->filter_slice = filter_slice_rgb24;
        break;
    case AV_PIX_FMT_0BGR:
    case AV_PIX_FMT_0RGB:
    case AV_PIX_FMT_BGR0:
    case AV_PIX_FMT_RGB0:
        s->filter_slice = filter_slice_rgb0;
        break;
    case AV_PIX_FMT_ABGR:
    case AV_PIX_FMT_ARGB:
    case AV_PIX_FMT_BGRA:
    case AV_PIX_FMT_RGBA:
        s->filter_slice = filter_slice_rgba;
        break;
    case AV_PIX_FMT_BGR48:
    case AV_PIX_FMT_RGB48:
        s->filter_slice = filter_slice_rgb48;
        break;
    case AV_PIX_FMT_BGRA64:
    case AV_PIX_FMT_RGBA64:
        s->filter_slice = filter_slice_rgba64;
        break;
    case AV_PIX_FMT_GBRP:
        s->filter_slice = filter_slice_gbrp;
        break;
    case AV_PIX_FMT_GBRAP:
        s->filter_slice = filter_slice_gbrap;
        break;
    case AV_PIX_FMT_GBRP9:
        s->filter_slice = filter_slice_gbrp9;
        break;
    case AV_PIX_FMT_GBRP10:
        s->filter_slice = filter_slice_gbrp10;
        break;
    case AV_PIX_FMT_GBRAP10:
        s->filter_slice = filter_slice_gbrap10;
        break;
    case AV_PIX_FMT_GBRP12:
        s->filter_slice = filter_slice_gbrp12;
        break;
    case AV_PIX_FMT_GBRAP12:
        s->filter_slice = filter_slice_gbrap12;
        break;
    case AV_PIX_FMT_GBRP14:
        s->filter_slice = filter_slice_gbrp14;
        break;
    case AV_PIX_FMT_GBRP16:
        s->filter_slice = filter_slice_gbrp16;
        break;
    case AV_PIX_FMT_GBRAP16:
        s->filter_slice = filter_slice_gbrap16;
        break;
    }

    return 0;
}