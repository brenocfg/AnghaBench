#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  pb; TYPE_2__* priv_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  index; TYPE_1__* codecpar; scalar_t__ start_time; } ;
struct TYPE_12__ {scalar_t__ next_audio_index; scalar_t__ next_video_index; scalar_t__ is_audio_present; int /*<<< orphan*/  audio_stream_index; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  video_stream_index; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_11__ {int channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; void* codec_type; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ IFVContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AVMEDIA_TYPE_AUDIO ; 
 void* AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S16LE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int parse_header (TYPE_4__*) ; 
 int read_index (TYPE_4__*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ifv_read_header(AVFormatContext *s)
{
    IFVContext *ifv = s->priv_data;
    AVStream *st;
    int ret;

    ret = parse_header(s);
    if (ret < 0)
        return ret;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id = AV_CODEC_ID_H264;
    st->codecpar->width = ifv->width;
    st->codecpar->height = ifv->height;
    st->start_time = 0;
    ifv->video_stream_index = st->index;

    avpriv_set_pts_info(st, 32, 1, 1000);

    if (ifv->is_audio_present) {
        st = avformat_new_stream(s, NULL);
        if (!st)
            return AVERROR(ENOMEM);

        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_id = AV_CODEC_ID_PCM_S16LE;
        st->codecpar->channels = 1;
        st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
        st->codecpar->sample_rate = ifv->sample_rate;
        ifv->audio_stream_index = st->index;

        avpriv_set_pts_info(st, 32, 1, 1000);
    }

    /*read video index*/
    avio_seek(s->pb, 0xf8, SEEK_SET);

    ret = read_index(s, AVMEDIA_TYPE_VIDEO, 0);
    if (ret < 0)
        return ret;

    if (ifv->is_audio_present) {
        /*read audio index*/
        avio_seek(s->pb, 0x14918, SEEK_SET);

        ret = read_index(s, AVMEDIA_TYPE_AUDIO, 0);
        if (ret < 0)
            return ret;
    }

    ifv->next_video_index = 0;
    ifv->next_audio_index = 0;

    return 0;
}