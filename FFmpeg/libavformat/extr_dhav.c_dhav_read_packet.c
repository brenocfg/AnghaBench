#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  pb; TYPE_3__** streams; TYPE_5__* priv_data; } ;
struct TYPE_25__ {int stream_index; int duration; int /*<<< orphan*/  pos; int /*<<< orphan*/  pts; int /*<<< orphan*/  flags; } ;
struct TYPE_19__ {int den; int /*<<< orphan*/  num; } ;
struct TYPE_24__ {int index; TYPE_4__* priv_data; TYPE_2__* codecpar; TYPE_1__ avg_frame_rate; } ;
struct TYPE_23__ {int type; int video_stream_index; int video_codec; int audio_stream_index; int audio_codec; int /*<<< orphan*/  last_good_pos; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  audio_channels; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_22__ {void* last_timestamp; } ;
struct TYPE_21__ {int /*<<< orphan*/  priv_data; } ;
struct TYPE_20__ {int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channels; void* codec_id; int /*<<< orphan*/  codec_type; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_4__ DHAVStream ;
typedef  TYPE_5__ DHAVContext ;
typedef  TYPE_6__ AVStream ;
typedef  TYPE_7__ AVPacket ;
typedef  TYPE_8__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 void* AV_CODEC_ID_AAC ; 
 void* AV_CODEC_ID_ADPCM_MS ; 
 void* AV_CODEC_ID_H264 ; 
 void* AV_CODEC_ID_HEVC ; 
 void* AV_CODEC_ID_MJPEG ; 
 void* AV_CODEC_ID_MP2 ; 
 void* AV_CODEC_ID_MP3 ; 
 void* AV_CODEC_ID_MPEG4 ; 
 void* AV_CODEC_ID_PCM_ALAW ; 
 void* AV_CODEC_ID_PCM_MULAW ; 
 void* AV_CODEC_ID_PCM_S16LE ; 
 void* AV_CODEC_ID_PCM_S8 ; 
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_7__*,int) ; 
 TYPE_4__* av_mallocz (int) ; 
 TYPE_6__* avformat_new_stream (TYPE_8__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_8__*,char*,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_6__*,int,int,int) ; 
 int /*<<< orphan*/  get_pts (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int read_chunk (TYPE_8__*) ; 

__attribute__((used)) static int dhav_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    DHAVContext *dhav = s->priv_data;
    int ret, stream_index;

retry:
    while ((ret = read_chunk(s)) == 0)
        ;

    if (ret < 0)
        return ret;

    if (dhav->type == 0xfd && dhav->video_stream_index == -1) {
        AVStream *st = avformat_new_stream(s, NULL);
        DHAVStream *dst;

        if (!st)
            return AVERROR(ENOMEM);

        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        switch (dhav->video_codec) {
        case 0x1: st->codecpar->codec_id = AV_CODEC_ID_MPEG4; break;
        case 0x3: st->codecpar->codec_id = AV_CODEC_ID_MJPEG; break;
        case 0x2:
        case 0x4:
        case 0x8: st->codecpar->codec_id = AV_CODEC_ID_H264;  break;
        case 0xc: st->codecpar->codec_id = AV_CODEC_ID_HEVC;  break;
        default: avpriv_request_sample(s, "Unknown video codec %X\n", dhav->video_codec);
        }
        st->codecpar->width      = dhav->width;
        st->codecpar->height     = dhav->height;
        st->avg_frame_rate.num   = dhav->frame_rate;
        st->avg_frame_rate.den   = 1;
        st->priv_data = dst = av_mallocz(sizeof(DHAVStream));
        if (!st->priv_data)
            return AVERROR(ENOMEM);
        dst->last_timestamp = AV_NOPTS_VALUE;
        dhav->video_stream_index = st->index;

        avpriv_set_pts_info(st, 64, 1, 1000);
    } else if (dhav->type == 0xf0 && dhav->audio_stream_index == -1) {
        AVStream *st = avformat_new_stream(s, NULL);
        DHAVStream *dst;

        if (!st)
            return AVERROR(ENOMEM);

        st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
        switch (dhav->audio_codec) {
        case 0x07: st->codecpar->codec_id = AV_CODEC_ID_PCM_S8;    break;
        case 0x0c: st->codecpar->codec_id = AV_CODEC_ID_PCM_S16LE; break;
        case 0x10: st->codecpar->codec_id = AV_CODEC_ID_PCM_S16LE; break;
        case 0x0a: st->codecpar->codec_id = AV_CODEC_ID_PCM_MULAW; break;
        case 0x16: st->codecpar->codec_id = AV_CODEC_ID_PCM_MULAW; break;
        case 0x0e: st->codecpar->codec_id = AV_CODEC_ID_PCM_ALAW;  break;
        case 0x1a: st->codecpar->codec_id = AV_CODEC_ID_AAC;       break;
        case 0x1f: st->codecpar->codec_id = AV_CODEC_ID_MP2;       break;
        case 0x21: st->codecpar->codec_id = AV_CODEC_ID_MP3;       break;
        case 0x0d: st->codecpar->codec_id = AV_CODEC_ID_ADPCM_MS;  break;
        default: avpriv_request_sample(s, "Unknown audio codec %X\n", dhav->audio_codec);
        }
        st->codecpar->channels    = dhav->audio_channels;
        st->codecpar->sample_rate = dhav->sample_rate;
        st->priv_data = dst = av_mallocz(sizeof(DHAVStream));
        if (!st->priv_data)
            return AVERROR(ENOMEM);
        dst->last_timestamp = AV_NOPTS_VALUE;
        dhav->audio_stream_index  = st->index;

        avpriv_set_pts_info(st, 64, 1, 1000);
    }

    stream_index = dhav->type == 0xf0 ? dhav->audio_stream_index : dhav->video_stream_index;
    if (stream_index < 0) {
        avio_skip(s->pb, ret);
        if (avio_rl32(s->pb) == MKTAG('d','h','a','v'))
            avio_skip(s->pb, 4);
        goto retry;
    }

    ret = av_get_packet(s->pb, pkt, ret);
    if (ret < 0)
        return ret;
    pkt->stream_index = stream_index;
    if (dhav->type != 0xfc)
        pkt->flags   |= AV_PKT_FLAG_KEY;
    if (pkt->stream_index >= 0)
        pkt->pts = get_pts(s, s->streams[pkt->stream_index]->priv_data);
    pkt->duration = 1;
    pkt->pos = dhav->last_good_pos;
    if (avio_rl32(s->pb) == MKTAG('d','h','a','v'))
        avio_skip(s->pb, 4);

    return ret;
}