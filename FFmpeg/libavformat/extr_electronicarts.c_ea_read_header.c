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
typedef  int int64_t ;
struct TYPE_15__ {TYPE_2__* priv_data; } ;
struct TYPE_14__ {scalar_t__ start_time; int /*<<< orphan*/  index; TYPE_1__* codecpar; } ;
struct TYPE_13__ {int num_channels; int sample_rate; int bytes; int /*<<< orphan*/  audio_stream_index; scalar_t__ audio_codec; int /*<<< orphan*/  alpha; int /*<<< orphan*/  video; } ;
struct TYPE_12__ {int channels; int sample_rate; int bits_per_coded_sample; int bit_rate; int block_align; scalar_t__ codec_tag; scalar_t__ codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ EaDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 scalar_t__ init_video_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ process_ea_header (TYPE_4__*) ; 

__attribute__((used)) static int ea_read_header(AVFormatContext *s)
{
    EaDemuxContext *ea = s->priv_data;
    AVStream *st;

    if (process_ea_header(s)<=0)
        return AVERROR(EIO);

    if (init_video_stream(s, &ea->video) || init_video_stream(s, &ea->alpha))
        return AVERROR(ENOMEM);

    if (ea->audio_codec) {
        if (ea->num_channels <= 0 || ea->num_channels > 2) {
            av_log(s, AV_LOG_WARNING,
                   "Unsupported number of channels: %d\n", ea->num_channels);
            ea->audio_codec = 0;
            return 1;
        }
        if (ea->sample_rate <= 0) {
            av_log(s, AV_LOG_ERROR,
                   "Unsupported sample rate: %d\n", ea->sample_rate);
            ea->audio_codec = 0;
            return 1;
        }
        if (ea->bytes <= 0 || ea->bytes > 2) {
            av_log(s, AV_LOG_ERROR,
                   "Invalid number of bytes per sample: %d\n", ea->bytes);
            ea->audio_codec = AV_CODEC_ID_NONE;
            return 1;
        }

        /* initialize the audio decoder stream */
        st = avformat_new_stream(s, NULL);
        if (!st)
            return AVERROR(ENOMEM);
        avpriv_set_pts_info(st, 33, 1, ea->sample_rate);
        st->codecpar->codec_type            = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_id              = ea->audio_codec;
        st->codecpar->codec_tag             = 0;   /* no tag */
        st->codecpar->channels              = ea->num_channels;
        st->codecpar->sample_rate           = ea->sample_rate;
        st->codecpar->bits_per_coded_sample = ea->bytes * 8;
        st->codecpar->bit_rate              = (int64_t)st->codecpar->channels *
                                              st->codecpar->sample_rate *
                                              st->codecpar->bits_per_coded_sample / 4;
        st->codecpar->block_align           = st->codecpar->channels *
                                              st->codecpar->bits_per_coded_sample;
        ea->audio_stream_index           = st->index;
        st->start_time                   = 0;
    }

    return 1;
}