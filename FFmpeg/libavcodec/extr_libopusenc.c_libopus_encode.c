#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  opus_int16 ;
struct TYPE_24__ {scalar_t__ sample_fmt; int const channels; TYPE_2__* priv_data; } ;
struct TYPE_23__ {int const nb_samples; int /*<<< orphan*/ ** data; } ;
struct TYPE_22__ {int duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {int const packet_size; } ;
struct TYPE_19__ {int /*<<< orphan*/  frame_count; int /*<<< orphan*/  frame_alloc; int /*<<< orphan*/  remaining_samples; } ;
struct TYPE_21__ {int stream_count; TYPE_1__ opts; TYPE_11__ afq; int /*<<< orphan*/  enc; int /*<<< orphan*/ * samples; int /*<<< orphan*/ * encoder_channel_map; } ;
typedef  TYPE_2__ LibopusEncContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_SKIP_SAMPLES ; 
 scalar_t__ AV_SAMPLE_FMT_FLT ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 int av_get_bytes_per_sample (scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int /*<<< orphan*/  av_shrink_packet (TYPE_3__*,int) ; 
 int ff_af_queue_add (TYPE_11__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  ff_af_queue_remove (TYPE_11__*,int const,int /*<<< orphan*/ *,int*) ; 
 int ff_alloc_packet2 (TYPE_5__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int ff_opus_error_to_averror (int) ; 
 int /*<<< orphan*/  libopus_copy_samples_with_channel_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int const,int const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int opus_multistream_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int opus_multistream_encode_float (int /*<<< orphan*/ ,float*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opus_strerror (int) ; 

__attribute__((used)) static int libopus_encode(AVCodecContext *avctx, AVPacket *avpkt,
                          const AVFrame *frame, int *got_packet_ptr)
{
    LibopusEncContext *opus = avctx->priv_data;
    const int bytes_per_sample = av_get_bytes_per_sample(avctx->sample_fmt);
    const int sample_size      = avctx->channels * bytes_per_sample;
    uint8_t *audio;
    int ret;
    int discard_padding;

    if (frame) {
        ret = ff_af_queue_add(&opus->afq, frame);
        if (ret < 0)
            return ret;
        if (opus->encoder_channel_map != NULL) {
            audio = opus->samples;
            libopus_copy_samples_with_channel_map(
                audio, frame->data[0], opus->encoder_channel_map,
                avctx->channels, frame->nb_samples, bytes_per_sample);
        } else if (frame->nb_samples < opus->opts.packet_size) {
            audio = opus->samples;
            memcpy(audio, frame->data[0], frame->nb_samples * sample_size);
        } else
            audio = frame->data[0];
    } else {
        if (!opus->afq.remaining_samples || (!opus->afq.frame_alloc && !opus->afq.frame_count))
            return 0;
        audio = opus->samples;
        memset(audio, 0, opus->opts.packet_size * sample_size);
    }

    /* Maximum packet size taken from opusenc in opus-tools. 120ms packets
     * consist of 6 frames in one packet. The maximum frame size is 1275
     * bytes along with the largest possible packet header of 7 bytes. */
    if ((ret = ff_alloc_packet2(avctx, avpkt, (1275 * 6 + 7) * opus->stream_count, 0)) < 0)
        return ret;

    if (avctx->sample_fmt == AV_SAMPLE_FMT_FLT)
        ret = opus_multistream_encode_float(opus->enc, (float *)audio,
                                            opus->opts.packet_size,
                                            avpkt->data, avpkt->size);
    else
        ret = opus_multistream_encode(opus->enc, (opus_int16 *)audio,
                                      opus->opts.packet_size,
                                      avpkt->data, avpkt->size);

    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR,
               "Error encoding frame: %s\n", opus_strerror(ret));
        return ff_opus_error_to_averror(ret);
    }

    av_shrink_packet(avpkt, ret);

    ff_af_queue_remove(&opus->afq, opus->opts.packet_size,
                       &avpkt->pts, &avpkt->duration);

    discard_padding = opus->opts.packet_size - avpkt->duration;
    // Check if subtraction resulted in an overflow
    if ((discard_padding < opus->opts.packet_size) != (avpkt->duration > 0)) {
        av_packet_unref(avpkt);
        av_free(avpkt);
        return AVERROR(EINVAL);
    }
    if (discard_padding > 0) {
        uint8_t* side_data = av_packet_new_side_data(avpkt,
                                                     AV_PKT_DATA_SKIP_SAMPLES,
                                                     10);
        if(!side_data) {
            av_packet_unref(avpkt);
            av_free(avpkt);
            return AVERROR(ENOMEM);
        }
        AV_WL32(side_data + 4, discard_padding);
    }

    *got_packet_ptr = 1;

    return 0;
}