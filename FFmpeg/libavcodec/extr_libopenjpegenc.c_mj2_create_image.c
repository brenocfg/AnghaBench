#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int x1; int y1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_16__ {int dx; int dy; int w; int h; scalar_t__ sgnd; int /*<<< orphan*/  bpp; int /*<<< orphan*/  prec; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ opj_image_cmptparm_t ;
struct TYPE_17__ {int subsampling_dx; int subsampling_dy; } ;
typedef  TYPE_4__ opj_cparameters_t ;
struct TYPE_19__ {int pix_fmt; int width; int height; } ;
struct TYPE_18__ {int log2_chroma_w; int log2_chroma_h; int nb_components; TYPE_1__* comp; } ;
struct TYPE_14__ {int /*<<< orphan*/  depth; } ;
typedef  int /*<<< orphan*/  OPJ_COLOR_SPACE ;
typedef  TYPE_5__ AVPixFmtDescriptor ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PIX_FMT_GBR24P 178 
#define  AV_PIX_FMT_GBRP10 177 
#define  AV_PIX_FMT_GBRP12 176 
#define  AV_PIX_FMT_GBRP14 175 
#define  AV_PIX_FMT_GBRP16 174 
#define  AV_PIX_FMT_GBRP9 173 
#define  AV_PIX_FMT_GRAY10 172 
#define  AV_PIX_FMT_GRAY12 171 
#define  AV_PIX_FMT_GRAY14 170 
#define  AV_PIX_FMT_GRAY16 169 
#define  AV_PIX_FMT_GRAY8 168 
#define  AV_PIX_FMT_RGB24 167 
#define  AV_PIX_FMT_RGB48 166 
#define  AV_PIX_FMT_RGBA 165 
#define  AV_PIX_FMT_RGBA64 164 
#define  AV_PIX_FMT_XYZ12 163 
#define  AV_PIX_FMT_YA16 162 
#define  AV_PIX_FMT_YA8 161 
#define  AV_PIX_FMT_YUV410P 160 
#define  AV_PIX_FMT_YUV411P 159 
#define  AV_PIX_FMT_YUV420P 158 
#define  AV_PIX_FMT_YUV420P10 157 
#define  AV_PIX_FMT_YUV420P12 156 
#define  AV_PIX_FMT_YUV420P14 155 
#define  AV_PIX_FMT_YUV420P16 154 
#define  AV_PIX_FMT_YUV420P9 153 
#define  AV_PIX_FMT_YUV422P 152 
#define  AV_PIX_FMT_YUV422P10 151 
#define  AV_PIX_FMT_YUV422P12 150 
#define  AV_PIX_FMT_YUV422P14 149 
#define  AV_PIX_FMT_YUV422P16 148 
#define  AV_PIX_FMT_YUV422P9 147 
#define  AV_PIX_FMT_YUV440P 146 
#define  AV_PIX_FMT_YUV444P 145 
#define  AV_PIX_FMT_YUV444P10 144 
#define  AV_PIX_FMT_YUV444P12 143 
#define  AV_PIX_FMT_YUV444P14 142 
#define  AV_PIX_FMT_YUV444P16 141 
#define  AV_PIX_FMT_YUV444P9 140 
#define  AV_PIX_FMT_YUVA420P 139 
#define  AV_PIX_FMT_YUVA420P10 138 
#define  AV_PIX_FMT_YUVA420P16 137 
#define  AV_PIX_FMT_YUVA420P9 136 
#define  AV_PIX_FMT_YUVA422P 135 
#define  AV_PIX_FMT_YUVA422P10 134 
#define  AV_PIX_FMT_YUVA422P16 133 
#define  AV_PIX_FMT_YUVA422P9 132 
#define  AV_PIX_FMT_YUVA444P 131 
#define  AV_PIX_FMT_YUVA444P10 130 
#define  AV_PIX_FMT_YUVA444P16 129 
#define  AV_PIX_FMT_YUVA444P9 128 
 int /*<<< orphan*/  OPJ_CLRSPC_GRAY ; 
 int /*<<< orphan*/  OPJ_CLRSPC_SRGB ; 
 int /*<<< orphan*/  OPJ_CLRSPC_SYCC ; 
 int /*<<< orphan*/  OPJ_CLRSPC_UNKNOWN ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* av_pix_fmt_desc_get (int) ; 
 TYPE_2__* opj_image_create (int,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static opj_image_t *mj2_create_image(AVCodecContext *avctx, opj_cparameters_t *parameters)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(avctx->pix_fmt);
    opj_image_cmptparm_t cmptparm[4] = {{0}};
    opj_image_t *img;
    int i;
    int sub_dx[4];
    int sub_dy[4];
    int numcomps;
    OPJ_COLOR_SPACE color_space = OPJ_CLRSPC_UNKNOWN;

    sub_dx[0] = sub_dx[3] = 1;
    sub_dy[0] = sub_dy[3] = 1;
    sub_dx[1] = sub_dx[2] = 1 << desc->log2_chroma_w;
    sub_dy[1] = sub_dy[2] = 1 << desc->log2_chroma_h;

    numcomps = desc->nb_components;

    switch (avctx->pix_fmt) {
    case AV_PIX_FMT_GRAY8:
    case AV_PIX_FMT_YA8:
    case AV_PIX_FMT_GRAY10:
    case AV_PIX_FMT_GRAY12:
    case AV_PIX_FMT_GRAY14:
    case AV_PIX_FMT_GRAY16:
    case AV_PIX_FMT_YA16:
        color_space = OPJ_CLRSPC_GRAY;
        break;
    case AV_PIX_FMT_RGB24:
    case AV_PIX_FMT_RGBA:
    case AV_PIX_FMT_RGB48:
    case AV_PIX_FMT_RGBA64:
    case AV_PIX_FMT_GBR24P:
    case AV_PIX_FMT_GBRP9:
    case AV_PIX_FMT_GBRP10:
    case AV_PIX_FMT_GBRP12:
    case AV_PIX_FMT_GBRP14:
    case AV_PIX_FMT_GBRP16:
    case AV_PIX_FMT_XYZ12:
        color_space = OPJ_CLRSPC_SRGB;
        break;
    case AV_PIX_FMT_YUV410P:
    case AV_PIX_FMT_YUV411P:
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUV422P:
    case AV_PIX_FMT_YUV440P:
    case AV_PIX_FMT_YUV444P:
    case AV_PIX_FMT_YUVA420P:
    case AV_PIX_FMT_YUVA422P:
    case AV_PIX_FMT_YUVA444P:
    case AV_PIX_FMT_YUV420P9:
    case AV_PIX_FMT_YUV422P9:
    case AV_PIX_FMT_YUV444P9:
    case AV_PIX_FMT_YUVA420P9:
    case AV_PIX_FMT_YUVA422P9:
    case AV_PIX_FMT_YUVA444P9:
    case AV_PIX_FMT_YUV420P10:
    case AV_PIX_FMT_YUV422P10:
    case AV_PIX_FMT_YUV444P10:
    case AV_PIX_FMT_YUVA420P10:
    case AV_PIX_FMT_YUVA422P10:
    case AV_PIX_FMT_YUVA444P10:
    case AV_PIX_FMT_YUV420P12:
    case AV_PIX_FMT_YUV422P12:
    case AV_PIX_FMT_YUV444P12:
    case AV_PIX_FMT_YUV420P14:
    case AV_PIX_FMT_YUV422P14:
    case AV_PIX_FMT_YUV444P14:
    case AV_PIX_FMT_YUV420P16:
    case AV_PIX_FMT_YUV422P16:
    case AV_PIX_FMT_YUV444P16:
    case AV_PIX_FMT_YUVA420P16:
    case AV_PIX_FMT_YUVA422P16:
    case AV_PIX_FMT_YUVA444P16:
        color_space = OPJ_CLRSPC_SYCC;
        break;
    default:
        av_log(avctx, AV_LOG_ERROR,
               "The requested pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(avctx->pix_fmt));
        return NULL;
    }

    for (i = 0; i < numcomps; i++) {
        cmptparm[i].prec = desc->comp[i].depth;
        cmptparm[i].bpp  = desc->comp[i].depth;
        cmptparm[i].sgnd = 0;
        cmptparm[i].dx = sub_dx[i];
        cmptparm[i].dy = sub_dy[i];
        cmptparm[i].w = (avctx->width + sub_dx[i] - 1) / sub_dx[i];
        cmptparm[i].h = (avctx->height + sub_dy[i] - 1) / sub_dy[i];
    }

    img = opj_image_create(numcomps, cmptparm, color_space);

    if (!img)
        return NULL;

    // x0, y0 is the top left corner of the image
    // x1, y1 is the width, height of the reference grid
    img->x0 = 0;
    img->y0 = 0;
    img->x1 = (avctx->width  - 1) * parameters->subsampling_dx + 1;
    img->y1 = (avctx->height - 1) * parameters->subsampling_dy + 1;

    return img;
}