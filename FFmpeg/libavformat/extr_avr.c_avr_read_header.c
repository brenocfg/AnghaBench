#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_11__ {int /*<<< orphan*/  pb; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {int channels; int bits_per_coded_sample; scalar_t__ codec_id; int block_align; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avio_rb16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_rb24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_3__*,char*,int,...) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_get_pcm_codec_id (int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int avr_read_header(AVFormatContext *s)
{
    uint16_t chan, sign, bps;
    AVStream *st;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;

    avio_skip(s->pb, 4); // magic
    avio_skip(s->pb, 8); // sample_name

    chan = avio_rb16(s->pb);
    if (!chan) {
        st->codecpar->channels = 1;
    } else if (chan == 0xFFFFu) {
        st->codecpar->channels = 2;
    } else {
        avpriv_request_sample(s, "chan %d", chan);
        return AVERROR_PATCHWELCOME;
    }

    st->codecpar->bits_per_coded_sample = bps = avio_rb16(s->pb);

    sign = avio_rb16(s->pb);

    avio_skip(s->pb, 2); // loop
    avio_skip(s->pb, 2); // midi
    avio_skip(s->pb, 1); // replay speed

    st->codecpar->sample_rate = avio_rb24(s->pb);
    avio_skip(s->pb, 4 * 3);
    avio_skip(s->pb, 2 * 3);
    avio_skip(s->pb, 20);
    avio_skip(s->pb, 64);

    st->codecpar->codec_id = ff_get_pcm_codec_id(bps, 0, 1, sign);
    if (st->codecpar->codec_id == AV_CODEC_ID_NONE) {
        avpriv_request_sample(s, "Bps %d and sign %d", bps, sign);
        return AVERROR_PATCHWELCOME;
    }

    st->codecpar->block_align = bps * st->codecpar->channels / 8;

    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);
    return 0;
}