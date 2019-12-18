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
struct TYPE_11__ {int /*<<< orphan*/  pb; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {int channels; int sample_rate; int bits_per_coded_sample; int block_align; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S16BE ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S16LE ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S8 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_SANE_NB_CHANNELS ; 
 int av_get_bits_per_sample (int /*<<< orphan*/ ) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ ) ; 
 int avio_rl32 (int /*<<< orphan*/ ) ; 
 scalar_t__ avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 

__attribute__((used)) static int epaf_read_header(AVFormatContext *s)
{
    int le, sample_rate, codec, channels;
    AVStream *st;

    avio_skip(s->pb, 4);
    if (avio_rl32(s->pb))
        return AVERROR_INVALIDDATA;

    le = avio_rl32(s->pb);
    if (le && le != 1)
        return AVERROR_INVALIDDATA;

    if (le) {
        sample_rate = avio_rl32(s->pb);
        codec       = avio_rl32(s->pb);
        channels    = avio_rl32(s->pb);
    } else {
        sample_rate = avio_rb32(s->pb);
        codec       = avio_rb32(s->pb);
        channels    = avio_rb32(s->pb);
    }

    if (channels <= 0 || channels > FF_SANE_NB_CHANNELS || sample_rate <= 0)
        return AVERROR_INVALIDDATA;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
    st->codecpar->channels    = channels;
    st->codecpar->sample_rate = sample_rate;
    switch (codec) {
    case 0:
        st->codecpar->codec_id = le ? AV_CODEC_ID_PCM_S16LE : AV_CODEC_ID_PCM_S16BE;
        break;
    case 2:
        st->codecpar->codec_id = AV_CODEC_ID_PCM_S8;
        break;
    case 1:
        avpriv_request_sample(s, "24-bit Paris PCM format");
    default:
        return AVERROR_INVALIDDATA;
    }

    st->codecpar->bits_per_coded_sample = av_get_bits_per_sample(st->codecpar->codec_id);
    st->codecpar->block_align = st->codecpar->bits_per_coded_sample * st->codecpar->channels / 8;

    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    if (avio_skip(s->pb, 2024) < 0)
        return AVERROR_INVALIDDATA;
    return 0;
}