#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_20__ {int flags2; scalar_t__ skip_frame; int /*<<< orphan*/  err_recognition; int /*<<< orphan*/  flags; TYPE_1__* priv_data; } ;
struct TYPE_19__ {scalar_t__* buf; } ;
struct TYPE_18__ {int* data; int size; } ;
struct TYPE_17__ {scalar_t__ nal_unit_type; scalar_t__ mb_y; scalar_t__ mb_height; int /*<<< orphan*/  last_pic_for_ec; scalar_t__ next_output_pic; int /*<<< orphan*/ * slice_ctx; int /*<<< orphan*/  has_slice; int /*<<< orphan*/  cur_pic_ptr; int /*<<< orphan*/  nal_length_size; scalar_t__ is_avc; int /*<<< orphan*/  ps; scalar_t__ nb_slice_ctx_queued; scalar_t__ setup_finished; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ H264Context ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_NONREF ; 
 int AVERROR_INVALIDDATA ; 
 int AV_CODEC_FLAG2_CHUNKS ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_NEW_EXTRADATA ; 
 scalar_t__ H264_NAL_END_SEQUENCE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int* av_packet_get_side_data (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int decode_nal_units (TYPE_1__*,int const*,int) ; 
 int ff_h264_decode_extradata (int const*,int,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int ff_h264_field_end (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_h264_unref_picture (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int finalize_frame (TYPE_1__*,TYPE_3__*,scalar_t__,int*) ; 
 int get_consumed_bytes (int,int) ; 
 scalar_t__ is_extra (int const*,int) ; 
 int /*<<< orphan*/  memcmp (char*,int const*,int) ; 
 int send_next_delayed_frame (TYPE_1__*,TYPE_3__*,int*,int) ; 

__attribute__((used)) static int h264_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame, AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    H264Context *h     = avctx->priv_data;
    AVFrame *pict      = data;
    int buf_index;
    int ret;

    h->flags = avctx->flags;
    h->setup_finished = 0;
    h->nb_slice_ctx_queued = 0;

    ff_h264_unref_picture(h, &h->last_pic_for_ec);

    /* end of stream, output what is still in the buffers */
    if (buf_size == 0)
        return send_next_delayed_frame(h, pict, got_frame, 0);

    if (h->is_avc && av_packet_get_side_data(avpkt, AV_PKT_DATA_NEW_EXTRADATA, NULL)) {
        int side_size;
        uint8_t *side = av_packet_get_side_data(avpkt, AV_PKT_DATA_NEW_EXTRADATA, &side_size);
        if (is_extra(side, side_size))
            ff_h264_decode_extradata(side, side_size,
                                     &h->ps, &h->is_avc, &h->nal_length_size,
                                     avctx->err_recognition, avctx);
    }
    if (h->is_avc && buf_size >= 9 && buf[0]==1 && buf[2]==0 && (buf[4]&0xFC)==0xFC) {
        if (is_extra(buf, buf_size))
            return ff_h264_decode_extradata(buf, buf_size,
                                            &h->ps, &h->is_avc, &h->nal_length_size,
                                            avctx->err_recognition, avctx);
    }

    buf_index = decode_nal_units(h, buf, buf_size);
    if (buf_index < 0)
        return AVERROR_INVALIDDATA;

    if (!h->cur_pic_ptr && h->nal_unit_type == H264_NAL_END_SEQUENCE) {
        av_assert0(buf_index <= buf_size);
        return send_next_delayed_frame(h, pict, got_frame, buf_index);
    }

    if (!(avctx->flags2 & AV_CODEC_FLAG2_CHUNKS) && (!h->cur_pic_ptr || !h->has_slice)) {
        if (avctx->skip_frame >= AVDISCARD_NONREF ||
            buf_size >= 4 && !memcmp("Q264", buf, 4))
            return buf_size;
        av_log(avctx, AV_LOG_ERROR, "no frame!\n");
        return AVERROR_INVALIDDATA;
    }

    if (!(avctx->flags2 & AV_CODEC_FLAG2_CHUNKS) ||
        (h->mb_y >= h->mb_height && h->mb_height)) {
        if ((ret = ff_h264_field_end(h, &h->slice_ctx[0], 0)) < 0)
            return ret;

        /* Wait for second field. */
        if (h->next_output_pic) {
            ret = finalize_frame(h, pict, h->next_output_pic, got_frame);
            if (ret < 0)
                return ret;
        }
    }

    av_assert0(pict->buf[0] || !*got_frame);

    ff_h264_unref_picture(h, &h->last_pic_for_ec);

    return get_consumed_bytes(buf_index, buf_size);
}