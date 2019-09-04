#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* iformat; TYPE_3__* priv_data; } ;
struct TYPE_13__ {TYPE_2__* codecpar; } ;
struct TYPE_12__ {int sample_rate; } ;
struct TYPE_11__ {int channels; int sample_rate; int bit_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  raw_codec_id; } ;
typedef  TYPE_3__ GSMDemuxerContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int GSM_BLOCK_SAMPLES ; 
 int GSM_BLOCK_SIZE ; 
 int /*<<< orphan*/  GSM_SAMPLE_RATE ; 
 TYPE_4__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gsm_read_header(AVFormatContext *s)
{
    GSMDemuxerContext *c = s->priv_data;
    AVStream *st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id    = s->iformat->raw_codec_id;
    st->codecpar->channels    = 1;
    st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
    st->codecpar->sample_rate = c->sample_rate;
    st->codecpar->bit_rate    = GSM_BLOCK_SIZE * 8 * c->sample_rate / GSM_BLOCK_SAMPLES;

    avpriv_set_pts_info(st, 64, GSM_BLOCK_SAMPLES, GSM_SAMPLE_RATE);

    return 0;
}