#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* internal; int /*<<< orphan*/  pb; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {void* data_offset; } ;
struct TYPE_8__ {int channels; int block_align; void* sample_rate; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_MS ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int FF_SANE_NB_CHANNELS ; 
 int INT_MAX ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_r8 (int /*<<< orphan*/ ) ; 
 void* avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_header(AVFormatContext *s)
{
    AVStream *st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id = AV_CODEC_ID_ADPCM_MS;

    avio_rl32(s->pb);
    avio_rl32(s->pb);
    st->codecpar->sample_rate = avio_rl32(s->pb);
    st->codecpar->channels    = avio_rl32(s->pb);
    if (st->codecpar->channels > FF_SANE_NB_CHANNELS)
        return AVERROR(ENOSYS);
    s->internal->data_offset = avio_rl32(s->pb);
    avio_r8(s->pb);
    st->codecpar->block_align = avio_rl32(s->pb);
    if (st->codecpar->block_align > INT_MAX / FF_SANE_NB_CHANNELS)
        return AVERROR_INVALIDDATA;
    st->codecpar->block_align *= st->codecpar->channels;

    avio_seek(s->pb, s->internal->data_offset, SEEK_SET);

    return 0;
}