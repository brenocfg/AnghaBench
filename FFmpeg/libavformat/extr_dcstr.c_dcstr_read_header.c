#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pb; } ;
struct TYPE_11__ {TYPE_1__* codecpar; void* duration; } ;
struct TYPE_10__ {int channels; unsigned int block_align; void* sample_rate; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_AICA ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S16LE_PLANAR ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 void* avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_3__*,char*,unsigned int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,void*) ; 

__attribute__((used)) static int dcstr_read_header(AVFormatContext *s)
{
    unsigned codec, align;
    int mult;
    AVStream *st;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
    st->codecpar->channels    = avio_rl32(s->pb);
    st->codecpar->sample_rate = avio_rl32(s->pb);
    codec                  = avio_rl32(s->pb);
    align                  = avio_rl32(s->pb);
    avio_skip(s->pb, 4);
    st->duration           = avio_rl32(s->pb);
    mult                   = avio_rl32(s->pb);
    if (st->codecpar->channels <= 0 || mult <= 0 || mult > INT_MAX / st->codecpar->channels) {
        av_log(s, AV_LOG_ERROR, "invalid number of channels %d x %d\n", st->codecpar->channels, mult);
        return AVERROR_INVALIDDATA;
    }
    st->codecpar->channels *= mult;
    if (!align || align > INT_MAX / st->codecpar->channels)
        return AVERROR_INVALIDDATA;
    st->codecpar->block_align = align * st->codecpar->channels;

    switch (codec) {
    case  4: st->codecpar->codec_id = AV_CODEC_ID_ADPCM_AICA;       break;
    case 16: st->codecpar->codec_id = AV_CODEC_ID_PCM_S16LE_PLANAR; break;
    default: avpriv_request_sample(s, "codec %X", codec);
             return AVERROR_PATCHWELCOME;
    }

    avio_skip(s->pb, 0x800 - avio_tell(s->pb));
    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}