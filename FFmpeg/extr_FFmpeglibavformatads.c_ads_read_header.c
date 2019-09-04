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
struct TYPE_10__ {int /*<<< orphan*/  pb; } ;
struct TYPE_9__ {int duration; TYPE_1__* codecpar; } ;
struct TYPE_8__ {int channels; scalar_t__ codec_id; int block_align; void* sample_rate; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AV_CODEC_ID_ADPCM_PSX ; 
 scalar_t__ AV_CODEC_ID_PCM_S16LE_PLANAR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 void* avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,void*) ; 

__attribute__((used)) static int ads_read_header(AVFormatContext *s)
{
    int align, codec, size;
    AVStream *st;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    avio_skip(s->pb, 8);
    st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
    codec                  = avio_rl32(s->pb);
    st->codecpar->sample_rate = avio_rl32(s->pb);
    if (st->codecpar->sample_rate <= 0)
        return AVERROR_INVALIDDATA;
    st->codecpar->channels    = avio_rl32(s->pb);
    if (st->codecpar->channels <= 0)
        return AVERROR_INVALIDDATA;
    align                  = avio_rl32(s->pb);
    if (align <= 0 || align > INT_MAX / st->codecpar->channels)
        return AVERROR_INVALIDDATA;

    if (codec == 1)
        st->codecpar->codec_id = AV_CODEC_ID_PCM_S16LE_PLANAR;
    else
        st->codecpar->codec_id = AV_CODEC_ID_ADPCM_PSX;

    st->codecpar->block_align = st->codecpar->channels * align;
    avio_skip(s->pb, 12);
    size = avio_rl32(s->pb);
    if (st->codecpar->codec_id == AV_CODEC_ID_ADPCM_PSX)
        st->duration = (size - 0x40) / 16 / st->codecpar->channels * 28;
    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}