#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AVColorSpace { ____Placeholder_AVColorSpace } AVColorSpace ;
struct TYPE_9__ {int bpp; } ;
struct TYPE_10__ {TYPE_1__ h; } ;
struct TYPE_13__ {int bpp_index; int bytesperpixel; size_t ss_h; size_t ss_v; int pix_fmt; int /*<<< orphan*/  gb; TYPE_2__ s; } ;
typedef  TYPE_5__ VP9Context ;
struct TYPE_14__ {int profile; int colorspace; void* color_range; TYPE_5__* priv_data; } ;
struct TYPE_12__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 void* AVCOL_RANGE_JPEG ; 
 void* AVCOL_RANGE_MPEG ; 
#define  AVCOL_SPC_BT2020_NCL 150 
#define  AVCOL_SPC_BT470BG 149 
#define  AVCOL_SPC_BT709 148 
#define  AVCOL_SPC_RESERVED 147 
#define  AVCOL_SPC_RGB 146 
#define  AVCOL_SPC_SMPTE170M 145 
#define  AVCOL_SPC_SMPTE240M 144 
#define  AVCOL_SPC_UNSPECIFIED 143 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PIX_FMT_GBRP 142 
#define  AV_PIX_FMT_GBRP10 141 
#define  AV_PIX_FMT_GBRP12 140 
#define  AV_PIX_FMT_YUV420P 139 
#define  AV_PIX_FMT_YUV420P10 138 
#define  AV_PIX_FMT_YUV420P12 137 
#define  AV_PIX_FMT_YUV422P 136 
#define  AV_PIX_FMT_YUV422P10 135 
#define  AV_PIX_FMT_YUV422P12 134 
#define  AV_PIX_FMT_YUV440P 133 
#define  AV_PIX_FMT_YUV440P10 132 
#define  AV_PIX_FMT_YUV440P12 131 
#define  AV_PIX_FMT_YUV444P 130 
#define  AV_PIX_FMT_YUV444P10 129 
#define  AV_PIX_FMT_YUV444P12 128 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 size_t get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_colorspace_details(AVCodecContext *avctx)
{
    static const enum AVColorSpace colorspaces[8] = {
        AVCOL_SPC_UNSPECIFIED, AVCOL_SPC_BT470BG, AVCOL_SPC_BT709, AVCOL_SPC_SMPTE170M,
        AVCOL_SPC_SMPTE240M, AVCOL_SPC_BT2020_NCL, AVCOL_SPC_RESERVED, AVCOL_SPC_RGB,
    };
    VP9Context *s = avctx->priv_data;
    int bits = avctx->profile <= 1 ? 0 : 1 + get_bits1(&s->gb); // 0:8, 1:10, 2:12

    s->bpp_index = bits;
    s->s.h.bpp = 8 + bits * 2;
    s->bytesperpixel = (7 + s->s.h.bpp) >> 3;
    avctx->colorspace = colorspaces[get_bits(&s->gb, 3)];
    if (avctx->colorspace == AVCOL_SPC_RGB) { // RGB = profile 1
        static const enum AVPixelFormat pix_fmt_rgb[3] = {
            AV_PIX_FMT_GBRP, AV_PIX_FMT_GBRP10, AV_PIX_FMT_GBRP12
        };
        s->ss_h = s->ss_v = 0;
        avctx->color_range = AVCOL_RANGE_JPEG;
        s->pix_fmt = pix_fmt_rgb[bits];
        if (avctx->profile & 1) {
            if (get_bits1(&s->gb)) {
                av_log(avctx, AV_LOG_ERROR, "Reserved bit set in RGB\n");
                return AVERROR_INVALIDDATA;
            }
        } else {
            av_log(avctx, AV_LOG_ERROR, "RGB not supported in profile %d\n",
                   avctx->profile);
            return AVERROR_INVALIDDATA;
        }
    } else {
        static const enum AVPixelFormat pix_fmt_for_ss[3][2 /* v */][2 /* h */] = {
            { { AV_PIX_FMT_YUV444P, AV_PIX_FMT_YUV422P },
              { AV_PIX_FMT_YUV440P, AV_PIX_FMT_YUV420P } },
            { { AV_PIX_FMT_YUV444P10, AV_PIX_FMT_YUV422P10 },
              { AV_PIX_FMT_YUV440P10, AV_PIX_FMT_YUV420P10 } },
            { { AV_PIX_FMT_YUV444P12, AV_PIX_FMT_YUV422P12 },
              { AV_PIX_FMT_YUV440P12, AV_PIX_FMT_YUV420P12 } }
        };
        avctx->color_range = get_bits1(&s->gb) ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG;
        if (avctx->profile & 1) {
            s->ss_h = get_bits1(&s->gb);
            s->ss_v = get_bits1(&s->gb);
            s->pix_fmt = pix_fmt_for_ss[bits][s->ss_v][s->ss_h];
            if (s->pix_fmt == AV_PIX_FMT_YUV420P) {
                av_log(avctx, AV_LOG_ERROR, "YUV 4:2:0 not supported in profile %d\n",
                       avctx->profile);
                return AVERROR_INVALIDDATA;
            } else if (get_bits1(&s->gb)) {
                av_log(avctx, AV_LOG_ERROR, "Profile %d color details reserved bit set\n",
                       avctx->profile);
                return AVERROR_INVALIDDATA;
            }
        } else {
            s->ss_h = s->ss_v = 1;
            s->pix_fmt = pix_fmt_for_ss[bits][1][1];
        }
    }

    return 0;
}