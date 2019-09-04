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
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_10__ {int /*<<< orphan*/  pb; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {int channels; int sample_rate; int bits_per_coded_sample; int block_align; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_SANE_NB_CHANNELS ; 
 int INT_MAX ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  ff_get_line (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ff_get_pcm_codec_id (int,int /*<<< orphan*/ ,int,int) ; 
 int sscanf (char*,char*,int*,int*,int*) ; 

__attribute__((used)) static int pvf_read_header(AVFormatContext *s)
{
    char buffer[32];
    AVStream *st;
    int bps, channels, sample_rate;

    avio_skip(s->pb, 5);
    ff_get_line(s->pb, buffer, sizeof(buffer));
    if (sscanf(buffer, "%d %d %d",
               &channels,
               &sample_rate,
               &bps) != 3)
        return AVERROR_INVALIDDATA;

    if (channels <= 0 || channels > FF_SANE_NB_CHANNELS ||
        bps <= 0 || bps > INT_MAX / FF_SANE_NB_CHANNELS || sample_rate <= 0)
        return AVERROR_INVALIDDATA;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
    st->codecpar->channels    = channels;
    st->codecpar->sample_rate = sample_rate;
    st->codecpar->codec_id    = ff_get_pcm_codec_id(bps, 0, 1, 0xFFFF);
    st->codecpar->bits_per_coded_sample = bps;
    st->codecpar->block_align = bps * st->codecpar->channels / 8;

    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}