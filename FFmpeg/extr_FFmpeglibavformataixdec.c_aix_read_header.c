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
struct TYPE_13__ {int /*<<< orphan*/  pb; TYPE_2__** streams; } ;
struct TYPE_12__ {TYPE_1__* codecpar; } ;
struct TYPE_11__ {int /*<<< orphan*/  codecpar; } ;
struct TYPE_10__ {int sample_rate; void* channels; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_ADX ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 void* avio_r8 (int /*<<< orphan*/ ) ; 
 unsigned int avio_rb16 (int /*<<< orphan*/ ) ; 
 int avio_rb32 (int /*<<< orphan*/ ) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  ff_get_extradata (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int aix_read_header(AVFormatContext *s)
{
    unsigned nb_streams, first_offset, nb_segments;
    unsigned stream_list_offset;
    unsigned segment_list_offset = 0x20;
    unsigned segment_list_entry_size = 0x10;
    unsigned size;
    int i;

    avio_skip(s->pb, 4);
    first_offset = avio_rb32(s->pb) + 8;
    avio_skip(s->pb, 16);
    nb_segments = avio_rb16(s->pb);
    if (nb_segments == 0)
        return AVERROR_INVALIDDATA;
    stream_list_offset = segment_list_offset + segment_list_entry_size * nb_segments + 0x10;
    if (stream_list_offset >= first_offset)
        return AVERROR_INVALIDDATA;
    avio_seek(s->pb, stream_list_offset, SEEK_SET);
    nb_streams = avio_r8(s->pb);
    if (nb_streams == 0)
        return AVERROR_INVALIDDATA;
    avio_skip(s->pb, 7);
    for (i = 0; i < nb_streams; i++) {
        AVStream *st = avformat_new_stream(s, NULL);

        if (!st)
            return AVERROR(ENOMEM);
        st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_id    = AV_CODEC_ID_ADPCM_ADX;
        st->codecpar->sample_rate = avio_rb32(s->pb);
        st->codecpar->channels    = avio_r8(s->pb);
        avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);
        avio_skip(s->pb, 3);
    }

    avio_seek(s->pb, first_offset, SEEK_SET);
    for (i = 0; i < nb_streams; i++) {
        if (avio_rl32(s->pb) != MKTAG('A','I','X','P'))
            return AVERROR_INVALIDDATA;
        size = avio_rb32(s->pb);
        if (size <= 8)
            return AVERROR_INVALIDDATA;
        avio_skip(s->pb, 8);
        ff_get_extradata(s, s->streams[i]->codecpar, s->pb, size - 8);
    }

    return 0;
}