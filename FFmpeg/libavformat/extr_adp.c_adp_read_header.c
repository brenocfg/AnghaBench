#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int channels; int sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_11__ {int seekable; } ;
struct TYPE_10__ {TYPE_4__* pb; } ;
struct TYPE_9__ {TYPE_7__* codecpar; int /*<<< orphan*/  duration; scalar_t__ start_time; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_DTK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_get_audio_frame_duration2 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* avformat_new_stream (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_size (TYPE_4__*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static int adp_read_header(AVFormatContext *s)
{
    AVStream *st;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type     = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id       = AV_CODEC_ID_ADPCM_DTK;
    st->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;
    st->codecpar->channels       = 2;
    st->codecpar->sample_rate    = 48000;
    st->start_time            = 0;
    if (s->pb->seekable & AVIO_SEEKABLE_NORMAL)
        st->duration          = av_get_audio_frame_duration2(st->codecpar, avio_size(s->pb));

    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}