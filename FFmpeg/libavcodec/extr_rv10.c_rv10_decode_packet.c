#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_27__ {TYPE_3__* priv_data; } ;
struct TYPE_26__ {scalar_t__ codec_id; int mb_x; int mb_width; int mb_y; int mb_height; int resync_mb_x; int resync_mb_y; scalar_t__ pict_type; int first_slice_line; int mb_num_left; int /*<<< orphan*/  er; scalar_t__ loop_filter; int /*<<< orphan*/  block; TYPE_5__* avctx; int /*<<< orphan*/  gb; int /*<<< orphan*/  mv_type; int /*<<< orphan*/  mv_dir; int /*<<< orphan*/  mb_stride; int /*<<< orphan*/ * block_wrap; int /*<<< orphan*/  b8_stride; scalar_t__* rv10_first_dc_coded; int /*<<< orphan*/  qscale; int /*<<< orphan*/  chroma_qscale_table; scalar_t__ modified_quant; int /*<<< orphan*/  c_dc_scale_table; int /*<<< orphan*/  y_dc_scale_table; scalar_t__ h263_aic; TYPE_2__* current_picture_ptr; } ;
struct TYPE_25__ {TYPE_4__ m; } ;
struct TYPE_24__ {TYPE_1__* f; } ;
struct TYPE_23__ {scalar_t__ pict_type; } ;
typedef  TYPE_3__ RVDecContext ;
typedef  TYPE_4__ MpegEncContext ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_RV10 ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 int ERROR_SKIP_FRAME ; 
 int /*<<< orphan*/  ER_MB_END ; 
 int FFMAX (int,int) ; 
 int /*<<< orphan*/  MV_DIR_FORWARD ; 
 int /*<<< orphan*/  MV_TYPE_16X16 ; 
 int SLICE_END ; 
 int SLICE_ERROR ; 
 int SLICE_OK ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ff_aic_dc_scale_table ; 
 int /*<<< orphan*/  ff_dlog (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_er_add_slice (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_er_frame_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_h263_chroma_qscale_table ; 
 int ff_h263_decode_mb (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_h263_loop_filter (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_h263_update_motion_val (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_init_block_index (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_mpeg1_dc_scale_table ; 
 int /*<<< orphan*/  ff_mpeg_er_frame_start (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_mpv_frame_end (TYPE_4__*) ; 
 int ff_mpv_frame_start (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ff_mpv_reconstruct_mb (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_set_qscale (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_tlog (TYPE_5__*,char*,int,int) ; 
 int /*<<< orphan*/  ff_update_block_index (TYPE_4__*) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int rv10_decode_picture_header (TYPE_4__*) ; 
 int rv20_decode_picture_header (TYPE_3__*) ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rv10_decode_packet(AVCodecContext *avctx, const uint8_t *buf,
                              int buf_size, int buf_size2, int whole_size)
{
    RVDecContext *rv = avctx->priv_data;
    MpegEncContext *s = &rv->m;
    int mb_count, mb_pos, left, start_mb_x, active_bits_size, ret;

    active_bits_size = buf_size * 8;
    init_get_bits(&s->gb, buf, FFMAX(buf_size, buf_size2) * 8);
    if (s->codec_id == AV_CODEC_ID_RV10)
        mb_count = rv10_decode_picture_header(s);
    else
        mb_count = rv20_decode_picture_header(rv);
    if (mb_count < 0) {
        if (mb_count != ERROR_SKIP_FRAME)
            av_log(s->avctx, AV_LOG_ERROR, "HEADER ERROR\n");
        return AVERROR_INVALIDDATA;
    }

    if (s->mb_x >= s->mb_width ||
        s->mb_y >= s->mb_height) {
        av_log(s->avctx, AV_LOG_ERROR, "POS ERROR %d %d\n", s->mb_x, s->mb_y);
        return AVERROR_INVALIDDATA;
    }
    mb_pos = s->mb_y * s->mb_width + s->mb_x;
    left   = s->mb_width * s->mb_height - mb_pos;
    if (mb_count > left) {
        av_log(s->avctx, AV_LOG_ERROR, "COUNT ERROR\n");
        return AVERROR_INVALIDDATA;
    }

    if (whole_size < s->mb_width * s->mb_height / 8)
        return AVERROR_INVALIDDATA;

    if ((s->mb_x == 0 && s->mb_y == 0) || !s->current_picture_ptr) {
        // FIXME write parser so we always have complete frames?
        if (s->current_picture_ptr) {
            ff_er_frame_end(&s->er);
            ff_mpv_frame_end(s);
            s->mb_x = s->mb_y = s->resync_mb_x = s->resync_mb_y = 0;
        }
        if ((ret = ff_mpv_frame_start(s, avctx)) < 0)
            return ret;
        ff_mpeg_er_frame_start(s);
    } else {
        if (s->current_picture_ptr->f->pict_type != s->pict_type) {
            av_log(s->avctx, AV_LOG_ERROR, "Slice type mismatch\n");
            return AVERROR_INVALIDDATA;
        }
    }


    ff_dlog(avctx, "qscale=%d\n", s->qscale);

    /* default quantization values */
    if (s->codec_id == AV_CODEC_ID_RV10) {
        if (s->mb_y == 0)
            s->first_slice_line = 1;
    } else {
        s->first_slice_line = 1;
        s->resync_mb_x      = s->mb_x;
    }
    start_mb_x     = s->mb_x;
    s->resync_mb_y = s->mb_y;
    if (s->h263_aic) {
        s->y_dc_scale_table =
        s->c_dc_scale_table = ff_aic_dc_scale_table;
    } else {
        s->y_dc_scale_table =
        s->c_dc_scale_table = ff_mpeg1_dc_scale_table;
    }

    if (s->modified_quant)
        s->chroma_qscale_table = ff_h263_chroma_qscale_table;

    ff_set_qscale(s, s->qscale);

    s->rv10_first_dc_coded[0] = 0;
    s->rv10_first_dc_coded[1] = 0;
    s->rv10_first_dc_coded[2] = 0;
    s->block_wrap[0] =
    s->block_wrap[1] =
    s->block_wrap[2] =
    s->block_wrap[3] = s->b8_stride;
    s->block_wrap[4] =
    s->block_wrap[5] = s->mb_stride;
    ff_init_block_index(s);

    /* decode each macroblock */
    for (s->mb_num_left = mb_count; s->mb_num_left > 0; s->mb_num_left--) {
        int ret;
        ff_update_block_index(s);
        ff_tlog(avctx, "**mb x=%d y=%d\n", s->mb_x, s->mb_y);

        s->mv_dir  = MV_DIR_FORWARD;
        s->mv_type = MV_TYPE_16X16;
        ret = ff_h263_decode_mb(s, s->block);

        // Repeat the slice end check from ff_h263_decode_mb with our active
        // bitstream size
        if (ret != SLICE_ERROR && active_bits_size >= get_bits_count(&s->gb)) {
            int v = show_bits(&s->gb, 16);

            if (get_bits_count(&s->gb) + 16 > active_bits_size)
                v >>= get_bits_count(&s->gb) + 16 - active_bits_size;

            if (!v)
                ret = SLICE_END;
        }
        if (ret != SLICE_ERROR && active_bits_size < get_bits_count(&s->gb) &&
            8 * buf_size2 >= get_bits_count(&s->gb)) {
            active_bits_size = buf_size2 * 8;
            av_log(avctx, AV_LOG_DEBUG, "update size from %d to %d\n",
                   8 * buf_size, active_bits_size);
            ret = SLICE_OK;
        }

        if (ret == SLICE_ERROR || active_bits_size < get_bits_count(&s->gb)) {
            av_log(s->avctx, AV_LOG_ERROR, "ERROR at MB %d %d\n", s->mb_x,
                   s->mb_y);
            return AVERROR_INVALIDDATA;
        }
        if (s->pict_type != AV_PICTURE_TYPE_B)
            ff_h263_update_motion_val(s);
        ff_mpv_reconstruct_mb(s, s->block);
        if (s->loop_filter)
            ff_h263_loop_filter(s);

        if (++s->mb_x == s->mb_width) {
            s->mb_x = 0;
            s->mb_y++;
            ff_init_block_index(s);
        }
        if (s->mb_x == s->resync_mb_x)
            s->first_slice_line = 0;
        if (ret == SLICE_END)
            break;
    }

    ff_er_add_slice(&s->er, start_mb_x, s->resync_mb_y, s->mb_x - 1, s->mb_y,
                    ER_MB_END);

    return active_bits_size;
}