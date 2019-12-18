#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_15__ ;

/* Type definitions */
struct TYPE_25__ {int bytes; int /*<<< orphan*/  granulepos; struct TYPE_25__* packet; } ;
typedef  TYPE_3__ ogg_packet ;
struct TYPE_29__ {int initial_padding; TYPE_4__* priv_data; } ;
struct TYPE_28__ {int nb_samples; int /*<<< orphan*/ * extended_data; } ;
struct TYPE_27__ {int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  size; TYPE_3__* data; } ;
struct TYPE_22__ {int remaining_samples; TYPE_2__* frames; int /*<<< orphan*/  remaining_delay; scalar_t__ frame_alloc; } ;
struct TYPE_23__ {int channels; } ;
struct TYPE_26__ {int eof; TYPE_15__ afq; int /*<<< orphan*/  vp; int /*<<< orphan*/  pkt_fifo; int /*<<< orphan*/  vd; int /*<<< orphan*/  vb; TYPE_1__ vi; } ;
struct TYPE_24__ {int duration; scalar_t__ pts; } ;
typedef  TYPE_4__ LibvorbisEncContext ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_generic_write (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int av_fifo_size (int /*<<< orphan*/ ) ; 
 int av_fifo_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int av_vorbis_parse_frame (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_af_queue_add (TYPE_15__*,TYPE_6__ const*) ; 
 int /*<<< orphan*/  ff_af_queue_remove (TYPE_15__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_alloc_packet2 (TYPE_7__*,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_samples_to_time_base (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int** ff_vorbis_encoding_channel_layout_offsets ; 
 int /*<<< orphan*/  memcpy (float*,int /*<<< orphan*/ ,int const) ; 
 int vorbis_analysis (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vorbis_analysis_blockout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float** vorbis_analysis_buffer (int /*<<< orphan*/ *,int const) ; 
 int vorbis_analysis_wrote (int /*<<< orphan*/ *,int const) ; 
 int vorbis_bitrate_addblock (int /*<<< orphan*/ *) ; 
 int vorbis_bitrate_flushpacket (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int vorbis_error_to_averror (int) ; 

__attribute__((used)) static int libvorbis_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,
                                  const AVFrame *frame, int *got_packet_ptr)
{
    LibvorbisEncContext *s = avctx->priv_data;
    ogg_packet op;
    int ret, duration;

    /* send samples to libvorbis */
    if (frame) {
        const int samples = frame->nb_samples;
        float **buffer;
        int c, channels = s->vi.channels;

        buffer = vorbis_analysis_buffer(&s->vd, samples);
        for (c = 0; c < channels; c++) {
            int co = (channels > 8) ? c :
                     ff_vorbis_encoding_channel_layout_offsets[channels - 1][c];
            memcpy(buffer[c], frame->extended_data[co],
                   samples * sizeof(*buffer[c]));
        }
        if ((ret = vorbis_analysis_wrote(&s->vd, samples)) < 0) {
            av_log(avctx, AV_LOG_ERROR, "error in vorbis_analysis_wrote()\n");
            return vorbis_error_to_averror(ret);
        }
        if ((ret = ff_af_queue_add(&s->afq, frame)) < 0)
            return ret;
    } else {
        if (!s->eof && s->afq.frame_alloc)
            if ((ret = vorbis_analysis_wrote(&s->vd, 0)) < 0) {
                av_log(avctx, AV_LOG_ERROR, "error in vorbis_analysis_wrote()\n");
                return vorbis_error_to_averror(ret);
            }
        s->eof = 1;
    }

    /* retrieve available packets from libvorbis */
    while ((ret = vorbis_analysis_blockout(&s->vd, &s->vb)) == 1) {
        if ((ret = vorbis_analysis(&s->vb, NULL)) < 0)
            break;
        if ((ret = vorbis_bitrate_addblock(&s->vb)) < 0)
            break;

        /* add any available packets to the output packet buffer */
        while ((ret = vorbis_bitrate_flushpacket(&s->vd, &op)) == 1) {
            if (av_fifo_space(s->pkt_fifo) < sizeof(ogg_packet) + op.bytes) {
                av_log(avctx, AV_LOG_ERROR, "packet buffer is too small\n");
                return AVERROR_BUG;
            }
            av_fifo_generic_write(s->pkt_fifo, &op, sizeof(ogg_packet), NULL);
            av_fifo_generic_write(s->pkt_fifo, op.packet, op.bytes, NULL);
        }
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR, "error getting available packets\n");
            break;
        }
    }
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "error getting available packets\n");
        return vorbis_error_to_averror(ret);
    }

    /* check for available packets */
    if (av_fifo_size(s->pkt_fifo) < sizeof(ogg_packet))
        return 0;

    av_fifo_generic_read(s->pkt_fifo, &op, sizeof(ogg_packet), NULL);

    if ((ret = ff_alloc_packet2(avctx, avpkt, op.bytes, 0)) < 0)
        return ret;
    av_fifo_generic_read(s->pkt_fifo, avpkt->data, op.bytes, NULL);

    avpkt->pts = ff_samples_to_time_base(avctx, op.granulepos);

    duration = av_vorbis_parse_frame(s->vp, avpkt->data, avpkt->size);
    if (duration > 0) {
        /* we do not know encoder delay until we get the first packet from
         * libvorbis, so we have to update the AudioFrameQueue counts */
        if (!avctx->initial_padding && s->afq.frames) {
            avctx->initial_padding    = duration;
            av_assert0(!s->afq.remaining_delay);
            s->afq.frames->duration  += duration;
            if (s->afq.frames->pts != AV_NOPTS_VALUE)
                s->afq.frames->pts       -= duration;
            s->afq.remaining_samples += duration;
        }
        ff_af_queue_remove(&s->afq, duration, &avpkt->pts, &avpkt->duration);
    }

    *got_packet_ptr = 1;
    return 0;
}