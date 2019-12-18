#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_14__ {TYPE_1__* codecpar; int /*<<< orphan*/  index; scalar_t__ start_time; } ;
struct TYPE_13__ {int /*<<< orphan*/  audio_stream_index; int /*<<< orphan*/  video_stream_index; scalar_t__ audio_buffer_full; scalar_t__ current_frame_pts; scalar_t__ current_frame_offs; } ;
struct TYPE_12__ {int channels; int sample_rate; int bits_per_coded_sample; int bit_rate; int block_align; int /*<<< orphan*/  channel_layout; scalar_t__ codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ SeqDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S16BE ; 
 int /*<<< orphan*/  AV_CODEC_ID_TIERTEXSEQVIDEO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEQ_FRAME_H ; 
 int SEQ_FRAME_RATE ; 
 int /*<<< orphan*/  SEQ_FRAME_W ; 
 int SEQ_SAMPLE_RATE ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int seq_init_frame_buffers (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int seq_parse_frame_data (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_read_close (TYPE_4__*) ; 

__attribute__((used)) static int seq_read_header(AVFormatContext *s)
{
    int i, rc;
    SeqDemuxContext *seq = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st;

    /* init internal buffers */
    rc = seq_init_frame_buffers(seq, pb);
    if (rc) {
        seq_read_close(s);
        return rc;
    }

    seq->current_frame_offs = 0;

    /* preload (no audio data, just buffer operations related data) */
    for (i = 1; i <= 100; i++) {
        rc = seq_parse_frame_data(seq, pb);
        if (rc) {
            seq_read_close(s);
            return rc;
        }
    }

    seq->current_frame_pts = 0;

    seq->audio_buffer_full = 0;

    /* initialize the video decoder stream */
    st = avformat_new_stream(s, NULL);
    if (!st) {
        seq_read_close(s);
        return AVERROR(ENOMEM);
    }

    avpriv_set_pts_info(st, 32, 1, SEQ_FRAME_RATE);
    seq->video_stream_index = st->index;
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id = AV_CODEC_ID_TIERTEXSEQVIDEO;
    st->codecpar->codec_tag = 0;  /* no fourcc */
    st->codecpar->width = SEQ_FRAME_W;
    st->codecpar->height = SEQ_FRAME_H;

    /* initialize the audio decoder stream */
    st = avformat_new_stream(s, NULL);
    if (!st) {
        seq_read_close(s);
        return AVERROR(ENOMEM);
    }

    st->start_time = 0;
    avpriv_set_pts_info(st, 32, 1, SEQ_SAMPLE_RATE);
    seq->audio_stream_index = st->index;
    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id = AV_CODEC_ID_PCM_S16BE;
    st->codecpar->codec_tag = 0;  /* no tag */
    st->codecpar->channels = 1;
    st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
    st->codecpar->sample_rate = SEQ_SAMPLE_RATE;
    st->codecpar->bits_per_coded_sample = 16;
    st->codecpar->bit_rate = st->codecpar->sample_rate * st->codecpar->bits_per_coded_sample * st->codecpar->channels;
    st->codecpar->block_align = st->codecpar->channels * st->codecpar->bits_per_coded_sample / 8;

    return 0;
}