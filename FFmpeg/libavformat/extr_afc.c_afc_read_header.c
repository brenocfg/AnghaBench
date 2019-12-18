#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int channels; int* extradata; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_11__ {void* data_end; } ;
struct TYPE_10__ {int /*<<< orphan*/  pb; TYPE_3__* priv_data; } ;
struct TYPE_9__ {TYPE_4__* codecpar; void* duration; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AFCDemuxContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_AFC ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_1__* avformat_new_stream (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb16 (int /*<<< orphan*/ ) ; 
 void* avio_rb32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_alloc_extradata (TYPE_4__*,int) ; 

__attribute__((used)) static int afc_read_header(AVFormatContext *s)
{
    AFCDemuxContext *c = s->priv_data;
    AVStream *st;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id   = AV_CODEC_ID_ADPCM_AFC;
    st->codecpar->channels   = 2;
    st->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;

    if (ff_alloc_extradata(st->codecpar, 1))
        return AVERROR(ENOMEM);
    st->codecpar->extradata[0] = 8 * st->codecpar->channels;

    c->data_end = avio_rb32(s->pb) + 32LL;
    st->duration = avio_rb32(s->pb);
    st->codecpar->sample_rate = avio_rb16(s->pb);
    avio_skip(s->pb, 22);
    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}