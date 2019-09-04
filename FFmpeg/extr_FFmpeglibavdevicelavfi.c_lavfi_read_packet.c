#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_30__ {int len; int /*<<< orphan*/  str; } ;
struct TYPE_29__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct TYPE_28__ {TYPE_1__* priv_data; } ;
struct TYPE_27__ {int channels; int nb_samples; int /*<<< orphan*/  pkt_pos; int /*<<< orphan*/  pts; int /*<<< orphan*/ * metadata; int /*<<< orphan*/ * data; int /*<<< orphan*/  format; int /*<<< orphan*/  height; scalar_t__ width; int /*<<< orphan*/  linesize; } ;
struct TYPE_26__ {int size; int stream_index; int /*<<< orphan*/  pos; int /*<<< orphan*/  pts; int /*<<< orphan*/ * data; } ;
struct TYPE_25__ {int nb_sinks; int* sink_eof; int* sink_stream_map; int /*<<< orphan*/ * sinks; TYPE_2__ subcc_packet; TYPE_3__* decoded_frame; } ;
typedef  TYPE_1__ LavfiContext ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_6__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_BUFFERSINK_FLAG_PEEK ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_PKT_DATA_STRINGS_METADATA ; 
 int AV_ROUND_NEAR_INF ; 
 int AV_ROUND_PASS_MINMAX ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 double DBL_MAX ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_bprint_chars (TYPE_6__*,char,int) ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprint_is_complete (TYPE_6__*) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 int av_buffersink_get_frame_flags (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffersink_get_time_base (int /*<<< orphan*/ ) ; 
 TYPE_5__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_3__*) ; 
 int av_get_bytes_per_sample (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_image_copy_to_buffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int av_image_get_buffer_size (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_2__*) ; 
 int av_new_packet (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 double av_rescale_q_rnd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int create_subcc_packet (TYPE_4__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_4__*,char*,int,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lavfi_read_packet(AVFormatContext *avctx, AVPacket *pkt)
{
    LavfiContext *lavfi = avctx->priv_data;
    double min_pts = DBL_MAX;
    int stream_idx, min_pts_sink_idx = 0;
    AVFrame *frame = lavfi->decoded_frame;
    AVDictionary *frame_metadata;
    int ret, i;
    int size = 0;

    if (lavfi->subcc_packet.size) {
        *pkt = lavfi->subcc_packet;
        av_init_packet(&lavfi->subcc_packet);
        lavfi->subcc_packet.size = 0;
        lavfi->subcc_packet.data = NULL;
        return pkt->size;
    }

    /* iterate through all the graph sinks. Select the sink with the
     * minimum PTS */
    for (i = 0; i < lavfi->nb_sinks; i++) {
        AVRational tb = av_buffersink_get_time_base(lavfi->sinks[i]);
        double d;
        int ret;

        if (lavfi->sink_eof[i])
            continue;

        ret = av_buffersink_get_frame_flags(lavfi->sinks[i], frame,
                                            AV_BUFFERSINK_FLAG_PEEK);
        if (ret == AVERROR_EOF) {
            ff_dlog(avctx, "EOF sink_idx:%d\n", i);
            lavfi->sink_eof[i] = 1;
            continue;
        } else if (ret < 0)
            return ret;
        d = av_rescale_q_rnd(frame->pts, tb, AV_TIME_BASE_Q, AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX);
        ff_dlog(avctx, "sink_idx:%d time:%f\n", i, d);
        av_frame_unref(frame);

        if (d < min_pts) {
            min_pts = d;
            min_pts_sink_idx = i;
        }
    }
    if (min_pts == DBL_MAX)
        return AVERROR_EOF;

    ff_dlog(avctx, "min_pts_sink_idx:%i\n", min_pts_sink_idx);

    av_buffersink_get_frame_flags(lavfi->sinks[min_pts_sink_idx], frame, 0);
    stream_idx = lavfi->sink_stream_map[min_pts_sink_idx];

    if (frame->width /* FIXME best way of testing a video */) {
        size = av_image_get_buffer_size(frame->format, frame->width, frame->height, 1);
        if ((ret = av_new_packet(pkt, size)) < 0)
            return ret;

        av_image_copy_to_buffer(pkt->data, size, (const uint8_t **)frame->data, frame->linesize,
                                frame->format, frame->width, frame->height, 1);
    } else if (frame->channels /* FIXME test audio */) {
        size = frame->nb_samples * av_get_bytes_per_sample(frame->format) *
                                   frame->channels;
        if ((ret = av_new_packet(pkt, size)) < 0)
            return ret;
        memcpy(pkt->data, frame->data[0], size);
    }

    frame_metadata = frame->metadata;
    if (frame_metadata) {
        uint8_t *metadata;
        AVDictionaryEntry *e = NULL;
        AVBPrint meta_buf;

        av_bprint_init(&meta_buf, 0, AV_BPRINT_SIZE_UNLIMITED);
        while ((e = av_dict_get(frame_metadata, "", e, AV_DICT_IGNORE_SUFFIX))) {
            av_bprintf(&meta_buf, "%s", e->key);
            av_bprint_chars(&meta_buf, '\0', 1);
            av_bprintf(&meta_buf, "%s", e->value);
            av_bprint_chars(&meta_buf, '\0', 1);
        }
        if (!av_bprint_is_complete(&meta_buf) ||
            !(metadata = av_packet_new_side_data(pkt, AV_PKT_DATA_STRINGS_METADATA,
                                                 meta_buf.len))) {
            av_bprint_finalize(&meta_buf, NULL);
            return AVERROR(ENOMEM);
        }
        memcpy(metadata, meta_buf.str, meta_buf.len);
        av_bprint_finalize(&meta_buf, NULL);
    }

    if ((ret = create_subcc_packet(avctx, frame, min_pts_sink_idx)) < 0) {
        av_frame_unref(frame);
        av_packet_unref(pkt);
        return ret;
    }

    pkt->stream_index = stream_idx;
    pkt->pts = frame->pts;
    pkt->pos = frame->pkt_pos;
    pkt->size = size;
    av_frame_unref(frame);
    return size;
}