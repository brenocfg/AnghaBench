#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_18__ {int index; scalar_t__ buffer; } ;
struct TYPE_17__ {TYPE_1__* priv_data; } ;
struct TYPE_16__ {int mb_xy; int watermark_key; int mb_num; int const mb_x; int* intra4x4_pred_mode; int* mb2br_xy; scalar_t__ mb_y; int const mb_stride; int mb_width; TYPE_4__ gb_slice; scalar_t__ has_watermark; scalar_t__ adaptive_quant; void* qscale; void* slice_num; TYPE_2__* avctx; int /*<<< orphan*/  slice_type; TYPE_4__ gb; int /*<<< orphan*/ * slice_buf; int /*<<< orphan*/  slice_size; } ;
typedef  TYPE_1__ SVQ3Context ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RL32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_fast_malloc (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_log2 (int) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * ff_h264_golomb_to_pict_type ; 
 void* get_bits (TYPE_4__*,int) ; 
 scalar_t__ get_bits1 (TYPE_4__*) ; 
 int get_bits_left (TYPE_4__*) ; 
 unsigned int get_interleaved_ue_golomb (TYPE_4__*) ; 
 int /*<<< orphan*/  init_get_bits (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int show_bits (TYPE_4__*,int) ; 
 scalar_t__ skip_1stop_8data_bits (TYPE_4__*) ; 
 int /*<<< orphan*/  skip_bits (TYPE_4__*,int) ; 
 int /*<<< orphan*/  skip_bits1 (TYPE_4__*) ; 
 int /*<<< orphan*/  skip_bits_long (TYPE_4__*,int) ; 

__attribute__((used)) static int svq3_decode_slice_header(AVCodecContext *avctx)
{
    SVQ3Context *s = avctx->priv_data;
    const int mb_xy   = s->mb_xy;
    int i, header;
    unsigned slice_id;

    header = get_bits(&s->gb, 8);

    if (((header & 0x9F) != 1 && (header & 0x9F) != 2) || (header & 0x60) == 0) {
        /* TODO: what? */
        av_log(avctx, AV_LOG_ERROR, "unsupported slice header (%02X)\n", header);
        return -1;
    } else {
        int slice_bits, slice_bytes, slice_length;
        int length = header >> 5 & 3;

        slice_length = show_bits(&s->gb, 8 * length);
        slice_bits   = slice_length * 8;
        slice_bytes  = slice_length + length - 1;

        skip_bits(&s->gb, 8);

        av_fast_malloc(&s->slice_buf, &s->slice_size, slice_bytes + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!s->slice_buf)
            return AVERROR(ENOMEM);

        if (slice_bytes * 8LL > get_bits_left(&s->gb)) {
            av_log(avctx, AV_LOG_ERROR, "slice after bitstream end\n");
            return AVERROR_INVALIDDATA;
        }
        memcpy(s->slice_buf, s->gb.buffer + s->gb.index / 8, slice_bytes);

        if (s->watermark_key) {
            uint32_t header = AV_RL32(&s->slice_buf[1]);
            AV_WL32(&s->slice_buf[1], header ^ s->watermark_key);
        }
        init_get_bits(&s->gb_slice, s->slice_buf, slice_bits);

        if (length > 0) {
            memmove(s->slice_buf, &s->slice_buf[slice_length], length - 1);
        }
        skip_bits_long(&s->gb, slice_bytes * 8);
    }

    if ((slice_id = get_interleaved_ue_golomb(&s->gb_slice)) >= 3) {
        av_log(s->avctx, AV_LOG_ERROR, "illegal slice type %u \n", slice_id);
        return -1;
    }

    s->slice_type = ff_h264_golomb_to_pict_type[slice_id];

    if ((header & 0x9F) == 2) {
        i = (s->mb_num < 64) ? 6 : (1 + av_log2(s->mb_num - 1));
        get_bits(&s->gb_slice, i);
    } else if (get_bits1(&s->gb_slice)) {
        avpriv_report_missing_feature(s->avctx, "Media key encryption");
        return AVERROR_PATCHWELCOME;
    }

    s->slice_num      = get_bits(&s->gb_slice, 8);
    s->qscale         = get_bits(&s->gb_slice, 5);
    s->adaptive_quant = get_bits1(&s->gb_slice);

    /* unknown fields */
    skip_bits1(&s->gb_slice);

    if (s->has_watermark)
        skip_bits1(&s->gb_slice);

    skip_bits1(&s->gb_slice);
    skip_bits(&s->gb_slice, 2);

    if (skip_1stop_8data_bits(&s->gb_slice) < 0)
        return AVERROR_INVALIDDATA;

    /* reset intra predictors and invalidate motion vector references */
    if (s->mb_x > 0) {
        memset(s->intra4x4_pred_mode + s->mb2br_xy[mb_xy - 1] + 3,
               -1, 4 * sizeof(int8_t));
        memset(s->intra4x4_pred_mode + s->mb2br_xy[mb_xy - s->mb_x],
               -1, 8 * sizeof(int8_t) * s->mb_x);
    }
    if (s->mb_y > 0) {
        memset(s->intra4x4_pred_mode + s->mb2br_xy[mb_xy - s->mb_stride],
               -1, 8 * sizeof(int8_t) * (s->mb_width - s->mb_x));

        if (s->mb_x > 0)
            s->intra4x4_pred_mode[s->mb2br_xy[mb_xy - s->mb_stride - 1] + 3] = -1;
    }

    return 0;
}