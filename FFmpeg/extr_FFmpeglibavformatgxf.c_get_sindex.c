#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nb_streams; } ;
struct TYPE_9__ {int id; TYPE_1__* codecpar; void* need_parsing; } ;
struct TYPE_8__ {int channels; int sample_rate; int bit_rate; int block_align; int bits_per_coded_sample; void* codec_id; void* codec_type; void* channel_layout; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AVMEDIA_TYPE_AUDIO ; 
 void* AVMEDIA_TYPE_DATA ; 
 void* AVMEDIA_TYPE_UNKNOWN ; 
 void* AVMEDIA_TYPE_VIDEO ; 
 void* AVSTREAM_PARSE_HEADERS ; 
 void* AV_CH_LAYOUT_MONO ; 
 void* AV_CH_LAYOUT_STEREO ; 
 void* AV_CODEC_ID_AC3 ; 
 void* AV_CODEC_ID_DNXHD ; 
 void* AV_CODEC_ID_DVVIDEO ; 
 void* AV_CODEC_ID_H264 ; 
 void* AV_CODEC_ID_MJPEG ; 
 void* AV_CODEC_ID_MPEG1VIDEO ; 
 void* AV_CODEC_ID_MPEG2VIDEO ; 
 void* AV_CODEC_ID_NONE ; 
 void* AV_CODEC_ID_PCM_S16LE ; 
 void* AV_CODEC_ID_PCM_S24LE ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_find_stream_index (TYPE_3__*,int) ; 

__attribute__((used)) static int get_sindex(AVFormatContext *s, int id, int format) {
    int i;
    AVStream *st = NULL;
    i = ff_find_stream_index(s, id);
    if (i >= 0)
        return i;
    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    st->id = id;
    switch (format) {
        case 3:
        case 4:
            st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
            st->codecpar->codec_id = AV_CODEC_ID_MJPEG;
            break;
        case 13:
        case 14:
        case 15:
        case 16:
        case 25:
            st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
            st->codecpar->codec_id = AV_CODEC_ID_DVVIDEO;
            break;
        case 11:
        case 12:
        case 20:
            st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
            st->codecpar->codec_id = AV_CODEC_ID_MPEG2VIDEO;
            st->need_parsing = AVSTREAM_PARSE_HEADERS; //get keyframe flag etc.
            break;
        case 22:
        case 23:
            st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
            st->codecpar->codec_id = AV_CODEC_ID_MPEG1VIDEO;
            st->need_parsing = AVSTREAM_PARSE_HEADERS; //get keyframe flag etc.
            break;
        case 9:
            st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
            st->codecpar->codec_id = AV_CODEC_ID_PCM_S24LE;
            st->codecpar->channels = 1;
            st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
            st->codecpar->sample_rate = 48000;
            st->codecpar->bit_rate = 3 * 1 * 48000 * 8;
            st->codecpar->block_align = 3 * 1;
            st->codecpar->bits_per_coded_sample = 24;
            break;
        case 10:
            st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
            st->codecpar->codec_id = AV_CODEC_ID_PCM_S16LE;
            st->codecpar->channels = 1;
            st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
            st->codecpar->sample_rate = 48000;
            st->codecpar->bit_rate = 2 * 1 * 48000 * 8;
            st->codecpar->block_align = 2 * 1;
            st->codecpar->bits_per_coded_sample = 16;
            break;
        case 17:
            st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
            st->codecpar->codec_id = AV_CODEC_ID_AC3;
            st->codecpar->channels = 2;
            st->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;
            st->codecpar->sample_rate = 48000;
            break;
        case 26: /* AVCi50 / AVCi100 (AVC Intra) */
        case 29: /* AVCHD */
            st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
            st->codecpar->codec_id = AV_CODEC_ID_H264;
            st->need_parsing = AVSTREAM_PARSE_HEADERS;
            break;
        // timecode tracks:
        case 7:
        case 8:
        case 24:
            st->codecpar->codec_type = AVMEDIA_TYPE_DATA;
            st->codecpar->codec_id = AV_CODEC_ID_NONE;
            break;
        case 30:
            st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
            st->codecpar->codec_id = AV_CODEC_ID_DNXHD;
            break;
        default:
            st->codecpar->codec_type = AVMEDIA_TYPE_UNKNOWN;
            st->codecpar->codec_id = AV_CODEC_ID_NONE;
            break;
    }
    return s->nb_streams - 1;
}