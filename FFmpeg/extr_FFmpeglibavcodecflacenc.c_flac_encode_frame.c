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
struct TYPE_27__ {int /*<<< orphan*/  bits_per_raw_sample; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  extradata; TYPE_2__* priv_data; } ;
struct TYPE_26__ {scalar_t__ nb_samples; scalar_t__ pts; int /*<<< orphan*/ * data; } ;
struct TYPE_25__ {int size; scalar_t__ duration; scalar_t__ pts; } ;
struct TYPE_23__ {scalar_t__ blocksize; int verbatim_only; } ;
struct TYPE_24__ {int max_framesize; int max_encoded_framesize; int flushed; int min_framesize; scalar_t__ next_pts; int /*<<< orphan*/  sample_count; int /*<<< orphan*/  frame_count; TYPE_1__ frame; int /*<<< orphan*/  channels; int /*<<< orphan*/  md5sum; int /*<<< orphan*/  md5ctx; } ;
typedef  TYPE_2__ FlacEncodeContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_NEW_EXTRADATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_md5_final (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_decorrelation (TYPE_2__*) ; 
 int /*<<< orphan*/  copy_samples (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int encode_frame (TYPE_2__*) ; 
 int ff_alloc_packet2 (TYPE_5__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int ff_flac_get_max_frame_size (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_samples_to_time_base (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  init_frame (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wasted_bits (TYPE_2__*) ; 
 int update_md5_sum (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int write_frame (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  write_streaminfo (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flac_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,
                             const AVFrame *frame, int *got_packet_ptr)
{
    FlacEncodeContext *s;
    int frame_bytes, out_bytes, ret;

    s = avctx->priv_data;

    /* when the last block is reached, update the header in extradata */
    if (!frame) {
        s->max_framesize = s->max_encoded_framesize;
        av_md5_final(s->md5ctx, s->md5sum);
        write_streaminfo(s, avctx->extradata);

#if FF_API_SIDEDATA_ONLY_PKT
FF_DISABLE_DEPRECATION_WARNINGS
        if (avctx->side_data_only_packets && !s->flushed) {
FF_ENABLE_DEPRECATION_WARNINGS
#else
        if (!s->flushed) {
#endif
            uint8_t *side_data = av_packet_new_side_data(avpkt, AV_PKT_DATA_NEW_EXTRADATA,
                                                         avctx->extradata_size);
            if (!side_data)
                return AVERROR(ENOMEM);
            memcpy(side_data, avctx->extradata, avctx->extradata_size);

            avpkt->pts = s->next_pts;

            *got_packet_ptr = 1;
            s->flushed = 1;
        }

        return 0;
    }

    /* change max_framesize for small final frame */
    if (frame->nb_samples < s->frame.blocksize) {
        s->max_framesize = ff_flac_get_max_frame_size(frame->nb_samples,
                                                      s->channels,
                                                      avctx->bits_per_raw_sample);
    }

    init_frame(s, frame->nb_samples);

    copy_samples(s, frame->data[0]);

    channel_decorrelation(s);

    remove_wasted_bits(s);

    frame_bytes = encode_frame(s);

    /* Fall back on verbatim mode if the compressed frame is larger than it
       would be if encoded uncompressed. */
    if (frame_bytes < 0 || frame_bytes > s->max_framesize) {
        s->frame.verbatim_only = 1;
        frame_bytes = encode_frame(s);
        if (frame_bytes < 0) {
            av_log(avctx, AV_LOG_ERROR, "Bad frame count\n");
            return frame_bytes;
        }
    }

    if ((ret = ff_alloc_packet2(avctx, avpkt, frame_bytes, 0)) < 0)
        return ret;

    out_bytes = write_frame(s, avpkt);

    s->frame_count++;
    s->sample_count += frame->nb_samples;
    if ((ret = update_md5_sum(s, frame->data[0])) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error updating MD5 checksum\n");
        return ret;
    }
    if (out_bytes > s->max_encoded_framesize)
        s->max_encoded_framesize = out_bytes;
    if (out_bytes < s->min_framesize)
        s->min_framesize = out_bytes;

    avpkt->pts      = frame->pts;
    avpkt->duration = ff_samples_to_time_base(avctx, frame->nb_samples);
    avpkt->size     = out_bytes;

    s->next_pts = avpkt->pts + avpkt->duration;

    *got_packet_ptr = 1;
    return 0;
}