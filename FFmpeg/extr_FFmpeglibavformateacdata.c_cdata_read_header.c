#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_13__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_12__ {TYPE_1__* codecpar; } ;
struct TYPE_11__ {int channels; scalar_t__ audio_pts; } ;
struct TYPE_10__ {int channels; unsigned int sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; scalar_t__ codec_tag; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ CdataDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_5POINT1_BACK ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_QUAD ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_EA_XAS ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,unsigned int) ; 

__attribute__((used)) static int cdata_read_header(AVFormatContext *s)
{
    CdataDemuxContext *cdata = s->priv_data;
    AVIOContext *pb = s->pb;
    unsigned int sample_rate, header;
    AVStream *st;
    int64_t channel_layout = 0;

    header = avio_rb16(pb);
    switch (header) {
        case 0x0400: cdata->channels = 1; break;
        case 0x0404: cdata->channels = 2; break;
        case 0x040C: cdata->channels = 4; channel_layout = AV_CH_LAYOUT_QUAD;         break;
        case 0x0414: cdata->channels = 6; channel_layout = AV_CH_LAYOUT_5POINT1_BACK; break;
        default:
            av_log(s, AV_LOG_INFO, "unknown header 0x%04x\n", header);
            return -1;
    };

    sample_rate = avio_rb16(pb);
    avio_skip(pb, (avio_r8(pb) & 0x20) ? 15 : 11);

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_tag = 0; /* no fourcc */
    st->codecpar->codec_id = AV_CODEC_ID_ADPCM_EA_XAS;
    st->codecpar->channels = cdata->channels;
    st->codecpar->channel_layout = channel_layout;
    st->codecpar->sample_rate = sample_rate;
    avpriv_set_pts_info(st, 64, 1, sample_rate);

    cdata->audio_pts = 0;
    return 0;
}