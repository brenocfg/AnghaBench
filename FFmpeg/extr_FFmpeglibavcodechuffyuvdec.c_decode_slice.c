#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_22__ {TYPE_3__* priv_data; } ;
struct TYPE_21__ {int* linesize; int** data; } ;
struct TYPE_19__ {int (* add_left_pred ) (int*,int /*<<< orphan*/ ,int const,int) ;int /*<<< orphan*/  (* add_bytes ) (int*,int*,int) ;int /*<<< orphan*/  (* add_median_pred ) (int*,int*,int /*<<< orphan*/ ,int const,int*,int*) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  (* add_hfyu_left_pred_bgr32 ) (int*,int /*<<< orphan*/ ,int const,int*) ;} ;
struct TYPE_20__ {int width; int interlaced; int version; int chroma; int alpha; int chroma_h_shift; int chroma_v_shift; int predictor; int bitstream_bpp; int flags; TYPE_2__ llviddsp; int /*<<< orphan*/ * temp; TYPE_1__ hdsp; scalar_t__ bgr32; int /*<<< orphan*/  gb; scalar_t__ yuy2; scalar_t__ bitstream_buffer; } ;
typedef  TYPE_3__ HYuvContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 size_t A ; 
 int AVERROR_PATCHWELCOME ; 
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 size_t B ; 
 size_t G ; 
#define  LEFT 130 
#define  MEDIAN 129 
#define  PLANE 128 
 size_t R ; 
 int /*<<< orphan*/  add_bytes (TYPE_3__*,int*,int*,int) ; 
 int /*<<< orphan*/  add_median_prediction (TYPE_3__*,int*,int*,int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  decode_422_bitstream (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  decode_bgr_bitstream (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  decode_gray_bitstream (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  decode_plane_bitstream (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  draw_slice (TYPE_3__*,TYPE_4__*,int) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int left_prediction (TYPE_3__*,int*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int stub1 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  stub10 (int*,int*,int const) ; 
 int /*<<< orphan*/  stub11 (int*,int*,int const) ; 
 int stub12 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int stub13 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int stub14 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int stub15 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int stub16 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int stub17 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int stub18 (int*,int /*<<< orphan*/ ,int,int) ; 
 int stub19 (int*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int stub20 (int*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub21 (int*,int*,int /*<<< orphan*/ ,int const,int*,int*) ; 
 int /*<<< orphan*/  stub22 (int*,int*,int /*<<< orphan*/ ,int const,int*,int*) ; 
 int /*<<< orphan*/  stub23 (int*,int*,int /*<<< orphan*/ ,int const,int*,int*) ; 
 int /*<<< orphan*/  stub24 (int*,int*,int /*<<< orphan*/ ,int const,int*,int*) ; 
 int /*<<< orphan*/  stub25 (int*,int*,int /*<<< orphan*/ ,int const,int*,int*) ; 
 int /*<<< orphan*/  stub26 (int*,int*,int /*<<< orphan*/ ,int const,int*,int*) ; 
 int /*<<< orphan*/  stub27 (int*,int*,int /*<<< orphan*/ ,int const,int*,int*) ; 
 int /*<<< orphan*/  stub28 (int*,int /*<<< orphan*/ ,int const,int*) ; 
 int /*<<< orphan*/  stub29 (int*,int /*<<< orphan*/ ,int const,int*) ; 
 int stub3 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  stub30 (int*,int*,int) ; 
 int stub4 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  stub5 (int*,int*,int const) ; 
 int stub6 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int stub7 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int stub8 (int*,int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  stub9 (int*,int*,int const) ; 

__attribute__((used)) static int decode_slice(AVCodecContext *avctx, AVFrame *p, int height,
                        int buf_size, int y_offset, int table_size)
{
    HYuvContext *s = avctx->priv_data;
    int fake_ystride, fake_ustride, fake_vstride;
    const int width  = s->width;
    const int width2 = s->width >> 1;
    int ret;

    if ((ret = init_get_bits8(&s->gb, s->bitstream_buffer + table_size, buf_size - table_size)) < 0)
        return ret;

    fake_ystride = s->interlaced ? p->linesize[0] * 2 : p->linesize[0];
    fake_ustride = s->interlaced ? p->linesize[1] * 2 : p->linesize[1];
    fake_vstride = s->interlaced ? p->linesize[2] * 2 : p->linesize[2];

    if (s->version > 2) {
        int plane;
        for(plane = 0; plane < 1 + 2*s->chroma + s->alpha; plane++) {
            int left, lefttop, y;
            int w = width;
            int h = height;
            int fake_stride = fake_ystride;

            if (s->chroma && (plane == 1 || plane == 2)) {
                w >>= s->chroma_h_shift;
                h >>= s->chroma_v_shift;
                fake_stride = plane == 1 ? fake_ustride : fake_vstride;
            }

            switch (s->predictor) {
            case LEFT:
            case PLANE:
                decode_plane_bitstream(s, w, plane);
                left = left_prediction(s, p->data[plane], s->temp[0], w, 0);

                for (y = 1; y < h; y++) {
                    uint8_t *dst = p->data[plane] + p->linesize[plane]*y;

                    decode_plane_bitstream(s, w, plane);
                    left = left_prediction(s, dst, s->temp[0], w, left);
                    if (s->predictor == PLANE) {
                        if (y > s->interlaced) {
                            add_bytes(s, dst, dst - fake_stride, w);
                        }
                    }
                }

                break;
            case MEDIAN:
                decode_plane_bitstream(s, w, plane);
                left= left_prediction(s, p->data[plane], s->temp[0], w, 0);

                y = 1;

                /* second line is left predicted for interlaced case */
                if (s->interlaced) {
                    decode_plane_bitstream(s, w, plane);
                    left = left_prediction(s, p->data[plane] + p->linesize[plane], s->temp[0], w, left);
                    y++;
                }

                lefttop = p->data[plane][0];
                decode_plane_bitstream(s, w, plane);
                add_median_prediction(s, p->data[plane] + fake_stride, p->data[plane], s->temp[0], w, &left, &lefttop);
                y++;

                for (; y<h; y++) {
                    uint8_t *dst;

                    decode_plane_bitstream(s, w, plane);

                    dst = p->data[plane] + p->linesize[plane] * y;

                    add_median_prediction(s, dst, dst - fake_stride, s->temp[0], w, &left, &lefttop);
                }

                break;
            }
        }
        draw_slice(s, p, height);
    } else if (s->bitstream_bpp < 24) {
        int y, cy;
        int lefty, leftu, leftv;
        int lefttopy, lefttopu, lefttopv;

        if (s->yuy2) {
            p->data[0][3] = get_bits(&s->gb, 8);
            p->data[0][2] = get_bits(&s->gb, 8);
            p->data[0][1] = get_bits(&s->gb, 8);
            p->data[0][0] = get_bits(&s->gb, 8);

            av_log(avctx, AV_LOG_ERROR,
                   "YUY2 output is not implemented yet\n");
            return AVERROR_PATCHWELCOME;
        } else {
            leftv         =
            p->data[2][0 + y_offset * p->linesize[2]] = get_bits(&s->gb, 8);
            lefty         =
            p->data[0][1 + y_offset * p->linesize[0]] = get_bits(&s->gb, 8);
            leftu         =
            p->data[1][0 + y_offset * p->linesize[1]] = get_bits(&s->gb, 8);
            p->data[0][0 + y_offset * p->linesize[0]] = get_bits(&s->gb, 8);

            switch (s->predictor) {
            case LEFT:
            case PLANE:
                decode_422_bitstream(s, width - 2);
                lefty = s->llviddsp.add_left_pred(p->data[0] + p->linesize[0] * y_offset + 2, s->temp[0],
                                                   width - 2, lefty);
                if (!(s->flags & AV_CODEC_FLAG_GRAY)) {
                    leftu = s->llviddsp.add_left_pred(p->data[1] + p->linesize[1] * y_offset + 1, s->temp[1], width2 - 1, leftu);
                    leftv = s->llviddsp.add_left_pred(p->data[2] + p->linesize[2] * y_offset + 1, s->temp[2], width2 - 1, leftv);
                }

                for (cy = y = 1; y < height; y++, cy++) {
                    uint8_t *ydst, *udst, *vdst;

                    if (s->bitstream_bpp == 12) {
                        decode_gray_bitstream(s, width);

                        ydst = p->data[0] + p->linesize[0] * (y + y_offset);

                        lefty = s->llviddsp.add_left_pred(ydst, s->temp[0],
                                                           width, lefty);
                        if (s->predictor == PLANE) {
                            if (y > s->interlaced)
                                s->llviddsp.add_bytes(ydst, ydst - fake_ystride, width);
                        }
                        y++;
                        if (y >= height)
                            break;
                    }

                    draw_slice(s, p, y);

                    ydst = p->data[0] + p->linesize[0] * (y  + y_offset);
                    udst = p->data[1] + p->linesize[1] * (cy + y_offset);
                    vdst = p->data[2] + p->linesize[2] * (cy + y_offset);

                    decode_422_bitstream(s, width);
                    lefty = s->llviddsp.add_left_pred(ydst, s->temp[0],
                                                       width, lefty);
                    if (!(s->flags & AV_CODEC_FLAG_GRAY)) {
                        leftu = s->llviddsp.add_left_pred(udst, s->temp[1], width2, leftu);
                        leftv = s->llviddsp.add_left_pred(vdst, s->temp[2], width2, leftv);
                    }
                    if (s->predictor == PLANE) {
                        if (cy > s->interlaced) {
                            s->llviddsp.add_bytes(ydst, ydst - fake_ystride, width);
                            if (!(s->flags & AV_CODEC_FLAG_GRAY)) {
                                s->llviddsp.add_bytes(udst, udst - fake_ustride, width2);
                                s->llviddsp.add_bytes(vdst, vdst - fake_vstride, width2);
                            }
                        }
                    }
                }
                draw_slice(s, p, height);

                break;
            case MEDIAN:
                /* first line except first 2 pixels is left predicted */
                decode_422_bitstream(s, width - 2);
                lefty = s->llviddsp.add_left_pred(p->data[0] + 2, s->temp[0],
                                                   width - 2, lefty);
                if (!(s->flags & AV_CODEC_FLAG_GRAY)) {
                    leftu = s->llviddsp.add_left_pred(p->data[1] + 1, s->temp[1], width2 - 1, leftu);
                    leftv = s->llviddsp.add_left_pred(p->data[2] + 1, s->temp[2], width2 - 1, leftv);
                }

                cy = y = 1;

                /* second line is left predicted for interlaced case */
                if (s->interlaced) {
                    decode_422_bitstream(s, width);
                    lefty = s->llviddsp.add_left_pred(p->data[0] + p->linesize[0],
                                                       s->temp[0], width, lefty);
                    if (!(s->flags & AV_CODEC_FLAG_GRAY)) {
                        leftu = s->llviddsp.add_left_pred(p->data[1] + p->linesize[2], s->temp[1], width2, leftu);
                        leftv = s->llviddsp.add_left_pred(p->data[2] + p->linesize[1], s->temp[2], width2, leftv);
                    }
                    y++;
                    cy++;
                }

                /* next 4 pixels are left predicted too */
                decode_422_bitstream(s, 4);
                lefty = s->llviddsp.add_left_pred(p->data[0] + fake_ystride,
                                                   s->temp[0], 4, lefty);
                if (!(s->flags & AV_CODEC_FLAG_GRAY)) {
                    leftu = s->llviddsp.add_left_pred(p->data[1] + fake_ustride, s->temp[1], 2, leftu);
                    leftv = s->llviddsp.add_left_pred(p->data[2] + fake_vstride, s->temp[2], 2, leftv);
                }

                /* next line except the first 4 pixels is median predicted */
                lefttopy = p->data[0][3];
                decode_422_bitstream(s, width - 4);
                s->llviddsp.add_median_pred(p->data[0] + fake_ystride + 4,
                                             p->data[0] + 4, s->temp[0],
                                             width - 4, &lefty, &lefttopy);
                if (!(s->flags & AV_CODEC_FLAG_GRAY)) {
                    lefttopu = p->data[1][1];
                    lefttopv = p->data[2][1];
                    s->llviddsp.add_median_pred(p->data[1] + fake_ustride + 2, p->data[1] + 2, s->temp[1], width2 - 2, &leftu, &lefttopu);
                    s->llviddsp.add_median_pred(p->data[2] + fake_vstride + 2, p->data[2] + 2, s->temp[2], width2 - 2, &leftv, &lefttopv);
                }
                y++;
                cy++;

                for (; y < height; y++, cy++) {
                    uint8_t *ydst, *udst, *vdst;

                    if (s->bitstream_bpp == 12) {
                        while (2 * cy > y) {
                            decode_gray_bitstream(s, width);
                            ydst = p->data[0] + p->linesize[0] * y;
                            s->llviddsp.add_median_pred(ydst, ydst - fake_ystride,
                                                         s->temp[0], width,
                                                         &lefty, &lefttopy);
                            y++;
                        }
                        if (y >= height)
                            break;
                    }
                    draw_slice(s, p, y);

                    decode_422_bitstream(s, width);

                    ydst = p->data[0] + p->linesize[0] * y;
                    udst = p->data[1] + p->linesize[1] * cy;
                    vdst = p->data[2] + p->linesize[2] * cy;

                    s->llviddsp.add_median_pred(ydst, ydst - fake_ystride,
                                                 s->temp[0], width,
                                                 &lefty, &lefttopy);
                    if (!(s->flags & AV_CODEC_FLAG_GRAY)) {
                        s->llviddsp.add_median_pred(udst, udst - fake_ustride, s->temp[1], width2, &leftu, &lefttopu);
                        s->llviddsp.add_median_pred(vdst, vdst - fake_vstride, s->temp[2], width2, &leftv, &lefttopv);
                    }
                }

                draw_slice(s, p, height);
                break;
            }
        }
    } else {
        int y;
        uint8_t left[4];
        const int last_line = (y_offset + height - 1) * p->linesize[0];

        if (s->bitstream_bpp == 32) {
            left[A] = p->data[0][last_line + A] = get_bits(&s->gb, 8);
            left[R] = p->data[0][last_line + R] = get_bits(&s->gb, 8);
            left[G] = p->data[0][last_line + G] = get_bits(&s->gb, 8);
            left[B] = p->data[0][last_line + B] = get_bits(&s->gb, 8);
        } else {
            left[R] = p->data[0][last_line + R] = get_bits(&s->gb, 8);
            left[G] = p->data[0][last_line + G] = get_bits(&s->gb, 8);
            left[B] = p->data[0][last_line + B] = get_bits(&s->gb, 8);
            left[A] = p->data[0][last_line + A] = 255;
            skip_bits(&s->gb, 8);
        }

        if (s->bgr32) {
            switch (s->predictor) {
            case LEFT:
            case PLANE:
                decode_bgr_bitstream(s, width - 1);
                s->hdsp.add_hfyu_left_pred_bgr32(p->data[0] + last_line + 4,
                                                 s->temp[0], width - 1, left);

                for (y = height - 2; y >= 0; y--) { // Yes it is stored upside down.
                    decode_bgr_bitstream(s, width);

                    s->hdsp.add_hfyu_left_pred_bgr32(p->data[0] + p->linesize[0] * (y + y_offset),
                                                     s->temp[0], width, left);
                    if (s->predictor == PLANE) {
                        if (s->bitstream_bpp != 32)
                            left[A] = 0;
                        if (y < height - 1 - s->interlaced) {
                            s->llviddsp.add_bytes(p->data[0] + p->linesize[0] * (y + y_offset),
                                              p->data[0] + p->linesize[0] * (y + y_offset) +
                                              fake_ystride, 4 * width);
                        }
                    }
                }
                // just 1 large slice as this is not possible in reverse order
                draw_slice(s, p, height);
                break;
            default:
                av_log(avctx, AV_LOG_ERROR,
                       "prediction type not supported!\n");
            }
        } else {
            av_log(avctx, AV_LOG_ERROR,
                   "BGR24 output is not implemented yet\n");
            return AVERROR_PATCHWELCOME;
        }
    }

    return 0;
}