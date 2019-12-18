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
typedef  int uint16_t ;
typedef  int ptrdiff_t ;
struct TYPE_14__ {int coded_width; scalar_t__ coded_height; TYPE_4__* priv_data; } ;
struct TYPE_13__ {int* linesize; scalar_t__* data; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* add_left_pred_int16 ) (int*,int*,int const,int,int) ;} ;
struct TYPE_12__ {int interlaced; int bps; int max; int planes; int slice_height; scalar_t__ decorrelate; TYPE_2__ llviddsp; TYPE_1__* vlc; TYPE_3__** slices; scalar_t__ buf; int /*<<< orphan*/ * vshift; int /*<<< orphan*/ * hshift; TYPE_5__* p; } ;
struct TYPE_11__ {int /*<<< orphan*/  size; scalar_t__ start; } ;
struct TYPE_9__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
typedef  TYPE_4__ MagicYUVContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int FFMIN (int,scalar_t__) ; 
#define  GRADIENT 130 
#define  LEFT 129 
#define  MEDIAN 128 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_6__*,char*,int) ; 
 int get_bits (int /*<<< orphan*/ *,int const) ; 
 int const get_bits_left (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  magicyuv_median_pred16 (int*,int*,int*,int,int*,int*,int const) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int const,int,int) ; 
 int /*<<< orphan*/  stub2 (int*,int*,int const,int,int) ; 
 int /*<<< orphan*/  stub3 (int*,int*,int const,int,int) ; 
 int /*<<< orphan*/  stub4 (int*,int*,int const,int,int) ; 
 int /*<<< orphan*/  stub5 (int*,int*,int const,int,int) ; 
 int /*<<< orphan*/  stub6 (int*,int*,int const,int,int) ; 
 int /*<<< orphan*/  stub7 (int*,int*,int const,int,int) ; 

__attribute__((used)) static int magy_decode_slice10(AVCodecContext *avctx, void *tdata,
                               int j, int threadnr)
{
    MagicYUVContext *s = avctx->priv_data;
    int interlaced = s->interlaced;
    const int bps = s->bps;
    const int max = s->max - 1;
    AVFrame *p = s->p;
    int i, k, x;
    GetBitContext gb;
    uint16_t *dst;

    for (i = 0; i < s->planes; i++) {
        int left, lefttop, top;
        int height = AV_CEIL_RSHIFT(FFMIN(s->slice_height, avctx->coded_height - j * s->slice_height), s->vshift[i]);
        int width = AV_CEIL_RSHIFT(avctx->coded_width, s->hshift[i]);
        int sheight = AV_CEIL_RSHIFT(s->slice_height, s->vshift[i]);
        ptrdiff_t fake_stride = (p->linesize[i] / 2) * (1 + interlaced);
        ptrdiff_t stride = p->linesize[i] / 2;
        int flags, pred;
        int ret = init_get_bits8(&gb, s->buf + s->slices[i][j].start,
                                 s->slices[i][j].size);

        if (ret < 0)
            return ret;

        flags = get_bits(&gb, 8);
        pred  = get_bits(&gb, 8);

        dst = (uint16_t *)p->data[i] + j * sheight * stride;
        if (flags & 1) {
            if (get_bits_left(&gb) < bps * width * height)
                return AVERROR_INVALIDDATA;
            for (k = 0; k < height; k++) {
                for (x = 0; x < width; x++)
                    dst[x] = get_bits(&gb, bps);

                dst += stride;
            }
        } else {
            for (k = 0; k < height; k++) {
                for (x = 0; x < width; x++) {
                    int pix;
                    if (get_bits_left(&gb) <= 0)
                        return AVERROR_INVALIDDATA;

                    pix = get_vlc2(&gb, s->vlc[i].table, s->vlc[i].bits, 3);
                    if (pix < 0)
                        return AVERROR_INVALIDDATA;

                    dst[x] = max - pix;
                }
                dst += stride;
            }
        }

        switch (pred) {
        case LEFT:
            dst = (uint16_t *)p->data[i] + j * sheight * stride;
            s->llviddsp.add_left_pred_int16(dst, dst, max, width, 0);
            dst += stride;
            if (interlaced) {
                s->llviddsp.add_left_pred_int16(dst, dst, max, width, 0);
                dst += stride;
            }
            for (k = 1 + interlaced; k < height; k++) {
                s->llviddsp.add_left_pred_int16(dst, dst, max, width, dst[-fake_stride]);
                dst += stride;
            }
            break;
        case GRADIENT:
            dst = (uint16_t *)p->data[i] + j * sheight * stride;
            s->llviddsp.add_left_pred_int16(dst, dst, max, width, 0);
            dst += stride;
            if (interlaced) {
                s->llviddsp.add_left_pred_int16(dst, dst, max, width, 0);
                dst += stride;
            }
            for (k = 1 + interlaced; k < height; k++) {
                top = dst[-fake_stride];
                left = top + dst[0];
                dst[0] = left & max;
                for (x = 1; x < width; x++) {
                    top = dst[x - fake_stride];
                    lefttop = dst[x - (fake_stride + 1)];
                    left += top - lefttop + dst[x];
                    dst[x] = left & max;
                }
                dst += stride;
            }
            break;
        case MEDIAN:
            dst = (uint16_t *)p->data[i] + j * sheight * stride;
            s->llviddsp.add_left_pred_int16(dst, dst, max, width, 0);
            dst += stride;
            if (interlaced) {
                s->llviddsp.add_left_pred_int16(dst, dst, max, width, 0);
                dst += stride;
            }
            lefttop = left = dst[0];
            for (k = 1 + interlaced; k < height; k++) {
                magicyuv_median_pred16(dst, dst - fake_stride, dst, width, &left, &lefttop, max);
                lefttop = left = dst[0];
                dst += stride;
            }
            break;
        default:
            avpriv_request_sample(avctx, "Unknown prediction: %d", pred);
        }
    }

    if (s->decorrelate) {
        int height = FFMIN(s->slice_height, avctx->coded_height - j * s->slice_height);
        int width = avctx->coded_width;
        uint16_t *r = (uint16_t *)p->data[0] + j * s->slice_height * p->linesize[0] / 2;
        uint16_t *g = (uint16_t *)p->data[1] + j * s->slice_height * p->linesize[1] / 2;
        uint16_t *b = (uint16_t *)p->data[2] + j * s->slice_height * p->linesize[2] / 2;

        for (i = 0; i < height; i++) {
            for (k = 0; k < width; k++) {
                b[k] = (b[k] + g[k]) & max;
                r[k] = (r[k] + g[k]) & max;
            }
            b += p->linesize[0] / 2;
            g += p->linesize[1] / 2;
            r += p->linesize[2] / 2;
        }
    }

    return 0;
}