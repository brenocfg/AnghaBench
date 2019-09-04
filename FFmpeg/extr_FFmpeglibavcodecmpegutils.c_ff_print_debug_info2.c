#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int16_t ;
struct TYPE_13__ {int flags2; scalar_t__ codec_id; int debug; scalar_t__ hwaccel; int /*<<< orphan*/  frame_number; TYPE_1__* codec; } ;
struct TYPE_12__ {int /*<<< orphan*/  pict_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {scalar_t__ id; } ;
typedef  int /*<<< orphan*/  AVMotionVector ;
typedef  TYPE_2__ AVFrameSideData ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AV_CODEC_FLAG2_EXPORT_MVS ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_SVQ3 ; 
 int /*<<< orphan*/  AV_FRAME_DATA_MOTION_VECTORS ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int FF_DEBUG_MB_TYPE ; 
 int FF_DEBUG_QP ; 
 int FF_DEBUG_SKIP ; 
 scalar_t__ IS_16X16 (int) ; 
 scalar_t__ IS_16X8 (int) ; 
 scalar_t__ IS_8X16 (int) ; 
 scalar_t__ IS_8X8 (int) ; 
 scalar_t__ IS_ACPRED (int) ; 
 scalar_t__ IS_DIRECT (int) ; 
 scalar_t__ IS_GMC (int) ; 
 scalar_t__ IS_INTERLACED (int) ; 
 scalar_t__ IS_INTRA (int) ; 
 scalar_t__ IS_INTRA16x16 (int) ; 
 scalar_t__ IS_INTRA4x4 (int) ; 
 scalar_t__ IS_PCM (int) ; 
 scalar_t__ IS_SKIP (int) ; 
 scalar_t__ USES_LIST (int,int) ; 
 scalar_t__ add_mb (int /*<<< orphan*/ *,int,int,int,int,int,int const,int) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 TYPE_2__* av_frame_new_side_data (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_get_picture_type_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * av_malloc_array (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void ff_print_debug_info2(AVCodecContext *avctx, AVFrame *pict, uint8_t *mbskip_table,
                         uint32_t *mbtype_table, int8_t *qscale_table, int16_t (*motion_val[2])[2],
                         int *low_delay,
                         int mb_width, int mb_height, int mb_stride, int quarter_sample)
{
    if ((avctx->flags2 & AV_CODEC_FLAG2_EXPORT_MVS) && mbtype_table && motion_val[0]) {
        const int shift = 1 + quarter_sample;
        const int scale = 1 << shift;
        const int mv_sample_log2 = avctx->codec_id == AV_CODEC_ID_H264 || avctx->codec_id == AV_CODEC_ID_SVQ3 ? 2 : 1;
        const int mv_stride      = (mb_width << mv_sample_log2) +
                                   (avctx->codec->id == AV_CODEC_ID_H264 ? 0 : 1);
        int mb_x, mb_y, mbcount = 0;

        /* size is width * height * 2 * 4 where 2 is for directions and 4 is
         * for the maximum number of MB (4 MB in case of IS_8x8) */
        AVMotionVector *mvs = av_malloc_array(mb_width * mb_height, 2 * 4 * sizeof(AVMotionVector));
        if (!mvs)
            return;

        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            for (mb_x = 0; mb_x < mb_width; mb_x++) {
                int i, direction, mb_type = mbtype_table[mb_x + mb_y * mb_stride];
                for (direction = 0; direction < 2; direction++) {
                    if (!USES_LIST(mb_type, direction))
                        continue;
                    if (IS_8X8(mb_type)) {
                        for (i = 0; i < 4; i++) {
                            int sx = mb_x * 16 + 4 + 8 * (i & 1);
                            int sy = mb_y * 16 + 4 + 8 * (i >> 1);
                            int xy = (mb_x * 2 + (i & 1) +
                                      (mb_y * 2 + (i >> 1)) * mv_stride) << (mv_sample_log2 - 1);
                            int mx = motion_val[direction][xy][0];
                            int my = motion_val[direction][xy][1];
                            mbcount += add_mb(mvs + mbcount, mb_type, sx, sy, mx, my, scale, direction);
                        }
                    } else if (IS_16X8(mb_type)) {
                        for (i = 0; i < 2; i++) {
                            int sx = mb_x * 16 + 8;
                            int sy = mb_y * 16 + 4 + 8 * i;
                            int xy = (mb_x * 2 + (mb_y * 2 + i) * mv_stride) << (mv_sample_log2 - 1);
                            int mx = motion_val[direction][xy][0];
                            int my = motion_val[direction][xy][1];

                            if (IS_INTERLACED(mb_type))
                                my *= 2;

                            mbcount += add_mb(mvs + mbcount, mb_type, sx, sy, mx, my, scale, direction);
                        }
                    } else if (IS_8X16(mb_type)) {
                        for (i = 0; i < 2; i++) {
                            int sx = mb_x * 16 + 4 + 8 * i;
                            int sy = mb_y * 16 + 8;
                            int xy = (mb_x * 2 + i + mb_y * 2 * mv_stride) << (mv_sample_log2 - 1);
                            int mx = motion_val[direction][xy][0];
                            int my = motion_val[direction][xy][1];

                            if (IS_INTERLACED(mb_type))
                                my *= 2;

                            mbcount += add_mb(mvs + mbcount, mb_type, sx, sy, mx, my, scale, direction);
                        }
                    } else {
                          int sx = mb_x * 16 + 8;
                          int sy = mb_y * 16 + 8;
                          int xy = (mb_x + mb_y * mv_stride) << mv_sample_log2;
                          int mx = motion_val[direction][xy][0];
                          int my = motion_val[direction][xy][1];
                          mbcount += add_mb(mvs + mbcount, mb_type, sx, sy, mx, my, scale, direction);
                    }
                }
            }
        }

        if (mbcount) {
            AVFrameSideData *sd;

            av_log(avctx, AV_LOG_DEBUG, "Adding %d MVs info to frame %d\n", mbcount, avctx->frame_number);
            sd = av_frame_new_side_data(pict, AV_FRAME_DATA_MOTION_VECTORS, mbcount * sizeof(AVMotionVector));
            if (!sd) {
                av_freep(&mvs);
                return;
            }
            memcpy(sd->data, mvs, mbcount * sizeof(AVMotionVector));
        }

        av_freep(&mvs);
    }

    /* TODO: export all the following to make them accessible for users (and filters) */
    if (avctx->hwaccel || !mbtype_table)
        return;


    if (avctx->debug & (FF_DEBUG_SKIP | FF_DEBUG_QP | FF_DEBUG_MB_TYPE)) {
        int x,y;

        av_log(avctx, AV_LOG_DEBUG, "New frame, type: %c\n",
               av_get_picture_type_char(pict->pict_type));
        for (y = 0; y < mb_height; y++) {
            for (x = 0; x < mb_width; x++) {
                if (avctx->debug & FF_DEBUG_SKIP) {
                    int count = mbskip_table ? mbskip_table[x + y * mb_stride] : 0;
                    if (count > 9)
                        count = 9;
                    av_log(avctx, AV_LOG_DEBUG, "%1d", count);
                }
                if (avctx->debug & FF_DEBUG_QP) {
                    av_log(avctx, AV_LOG_DEBUG, "%2d",
                           qscale_table[x + y * mb_stride]);
                }
                if (avctx->debug & FF_DEBUG_MB_TYPE) {
                    int mb_type = mbtype_table[x + y * mb_stride];
                    // Type & MV direction
                    if (IS_PCM(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "P");
                    else if (IS_INTRA(mb_type) && IS_ACPRED(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "A");
                    else if (IS_INTRA4x4(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "i");
                    else if (IS_INTRA16x16(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "I");
                    else if (IS_DIRECT(mb_type) && IS_SKIP(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "d");
                    else if (IS_DIRECT(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "D");
                    else if (IS_GMC(mb_type) && IS_SKIP(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "g");
                    else if (IS_GMC(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "G");
                    else if (IS_SKIP(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "S");
                    else if (!USES_LIST(mb_type, 1))
                        av_log(avctx, AV_LOG_DEBUG, ">");
                    else if (!USES_LIST(mb_type, 0))
                        av_log(avctx, AV_LOG_DEBUG, "<");
                    else {
                        av_assert2(USES_LIST(mb_type, 0) && USES_LIST(mb_type, 1));
                        av_log(avctx, AV_LOG_DEBUG, "X");
                    }

                    // segmentation
                    if (IS_8X8(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "+");
                    else if (IS_16X8(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "-");
                    else if (IS_8X16(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "|");
                    else if (IS_INTRA(mb_type) || IS_16X16(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, " ");
                    else
                        av_log(avctx, AV_LOG_DEBUG, "?");


                    if (IS_INTERLACED(mb_type))
                        av_log(avctx, AV_LOG_DEBUG, "=");
                    else
                        av_log(avctx, AV_LOG_DEBUG, " ");
                }
            }
            av_log(avctx, AV_LOG_DEBUG, "\n");
        }
    }

#if FF_API_DEBUG_MV
    if ((avctx->debug & (FF_DEBUG_VIS_QP | FF_DEBUG_VIS_MB_TYPE)) ||
        (avctx->debug_mv)) {
        int mb_y;
        int i, ret;
        int h_chroma_shift, v_chroma_shift, block_height;
        const int mv_sample_log2 = avctx->codec_id == AV_CODEC_ID_H264 || avctx->codec_id == AV_CODEC_ID_SVQ3 ? 2 : 1;
        const int mv_stride      = (mb_width << mv_sample_log2) +
                                   (avctx->codec->id == AV_CODEC_ID_H264 ? 0 : 1);

        if (low_delay)
            *low_delay = 0; // needed to see the vectors without trashing the buffers

        ret = av_pix_fmt_get_chroma_sub_sample (avctx->pix_fmt, &h_chroma_shift, &v_chroma_shift);
        if (ret)
            return ret;

        av_frame_make_writable(pict);

        pict->opaque = NULL;
        block_height = 16 >> v_chroma_shift;

        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            int mb_x;
            for (mb_x = 0; mb_x < mb_width; mb_x++) {
                const int mb_index = mb_x + mb_y * mb_stride;
                if ((avctx->debug & FF_DEBUG_VIS_QP)) {
                    uint64_t c = (qscale_table[mb_index] * 128 / 31) *
                                 0x0101010101010101ULL;
                    int y;
                    for (y = 0; y < block_height; y++) {
                        *(uint64_t *)(pict->data[1] + 8 * mb_x +
                                      (block_height * mb_y + y) *
                                      pict->linesize[1]) = c;
                        *(uint64_t *)(pict->data[2] + 8 * mb_x +
                                      (block_height * mb_y + y) *
                                      pict->linesize[2]) = c;
                    }
                }
                if ((avctx->debug & FF_DEBUG_VIS_MB_TYPE) &&
                    motion_val[0]) {
                    int mb_type = mbtype_table[mb_index];
                    uint64_t u,v;
                    int y;
#define COLOR(theta, r) \
    u = (int)(128 + r * cos(theta * M_PI / 180)); \
    v = (int)(128 + r * sin(theta * M_PI / 180));


                    u = v = 128;
                    if (IS_PCM(mb_type)) {
                        COLOR(120, 48)
                    } else if ((IS_INTRA(mb_type) && IS_ACPRED(mb_type)) ||
                               IS_INTRA16x16(mb_type)) {
                        COLOR(30, 48)
                    } else if (IS_INTRA4x4(mb_type)) {
                        COLOR(90, 48)
                    } else if (IS_DIRECT(mb_type) && IS_SKIP(mb_type)) {
                        // COLOR(120, 48)
                    } else if (IS_DIRECT(mb_type)) {
                        COLOR(150, 48)
                    } else if (IS_GMC(mb_type) && IS_SKIP(mb_type)) {
                        COLOR(170, 48)
                    } else if (IS_GMC(mb_type)) {
                        COLOR(190, 48)
                    } else if (IS_SKIP(mb_type)) {
                        // COLOR(180, 48)
                    } else if (!USES_LIST(mb_type, 1)) {
                        COLOR(240, 48)
                    } else if (!USES_LIST(mb_type, 0)) {
                        COLOR(0, 48)
                    } else {
                        av_assert2(USES_LIST(mb_type, 0) && USES_LIST(mb_type, 1));
                        COLOR(300,48)
                    }

                    u *= 0x0101010101010101ULL;
                    v *= 0x0101010101010101ULL;
                    for (y = 0; y < block_height; y++) {
                        *(uint64_t *)(pict->data[1] + 8 * mb_x +
                                      (block_height * mb_y + y) * pict->linesize[1]) = u;
                        *(uint64_t *)(pict->data[2] + 8 * mb_x +
                                      (block_height * mb_y + y) * pict->linesize[2]) = v;
                    }

                    // segmentation
                    if (IS_8X8(mb_type) || IS_16X8(mb_type)) {
                        *(uint64_t *)(pict->data[0] + 16 * mb_x + 0 +
                                      (16 * mb_y + 8) * pict->linesize[0]) ^= 0x8080808080808080ULL;
                        *(uint64_t *)(pict->data[0] + 16 * mb_x + 8 +
                                      (16 * mb_y + 8) * pict->linesize[0]) ^= 0x8080808080808080ULL;
                    }
                    if (IS_8X8(mb_type) || IS_8X16(mb_type)) {
                        for (y = 0; y < 16; y++)
                            pict->data[0][16 * mb_x + 8 + (16 * mb_y + y) *
                                          pict->linesize[0]] ^= 0x80;
                    }
                    if (IS_8X8(mb_type) && mv_sample_log2 >= 2) {
                        int dm = 1 << (mv_sample_log2 - 2);
                        for (i = 0; i < 4; i++) {
                            int sx = mb_x * 16 + 8 * (i & 1);
                            int sy = mb_y * 16 + 8 * (i >> 1);
                            int xy = (mb_x * 2 + (i & 1) +
                                     (mb_y * 2 + (i >> 1)) * mv_stride) << (mv_sample_log2 - 1);
                            // FIXME bidir
                            int32_t *mv = (int32_t *) &motion_val[0][xy];
                            if (mv[0] != mv[dm] ||
                                mv[dm * mv_stride] != mv[dm * (mv_stride + 1)])
                                for (y = 0; y < 8; y++)
                                    pict->data[0][sx + 4 + (sy + y) * pict->linesize[0]] ^= 0x80;
                            if (mv[0] != mv[dm * mv_stride] || mv[dm] != mv[dm * (mv_stride + 1)])
                                *(uint64_t *)(pict->data[0] + sx + (sy + 4) *
                                              pict->linesize[0]) ^= 0x8080808080808080ULL;
                        }
                    }

                    if (IS_INTERLACED(mb_type) &&
                        avctx->codec->id == AV_CODEC_ID_H264) {
                        // hmm
                    }
                }
                if (mbskip_table)
                    mbskip_table[mb_index] = 0;
            }
        }
    }
#endif
}