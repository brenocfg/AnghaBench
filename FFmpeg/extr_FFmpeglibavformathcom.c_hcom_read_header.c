#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int channels; int sample_rate; int bits_per_coded_sample; int block_align; int /*<<< orphan*/ * extradata; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_9__ {int /*<<< orphan*/  pb; } ;
struct TYPE_8__ {TYPE_4__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_HCOM ; 
 int /*<<< orphan*/  AV_WB16 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  AV_WB32 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_1__* avformat_new_stream (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_r8 (int /*<<< orphan*/ ) ; 
 unsigned int avio_rb16 (int /*<<< orphan*/ ) ; 
 unsigned int avio_rb32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,int) ; 
 int ff_alloc_extradata (TYPE_4__*,unsigned int) ; 

__attribute__((used)) static int hcom_read_header(AVFormatContext *s)
{
    AVStream *st;
    unsigned data_size, rsrc_size, huffcount;
    unsigned compresstype, divisor;
    unsigned dict_entries;
    int ret;

    avio_skip(s->pb, 83);
    data_size = avio_rb32(s->pb);
    rsrc_size = avio_rb32(s->pb);
    avio_skip(s->pb, 128-91+4);
    huffcount = avio_rb32(s->pb);
    avio_skip(s->pb, 4);
    compresstype = avio_rb32(s->pb);
    if (compresstype > 1)
        return AVERROR_INVALIDDATA;
    divisor = avio_rb32(s->pb);
    if (divisor == 0 || divisor > 4)
        return AVERROR_INVALIDDATA;
    dict_entries = avio_rb16(s->pb);

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
    st->codecpar->channels    = 1;
    st->codecpar->sample_rate = 22050 / divisor;
    st->codecpar->codec_id    = AV_CODEC_ID_HCOM;
    st->codecpar->bits_per_coded_sample = 8;
    st->codecpar->block_align = 4;

    ret = ff_alloc_extradata(st->codecpar, dict_entries * 4 + 7);
    if (ret < 0)
        return ret;
    AV_WB16(st->codecpar->extradata, dict_entries);
    AV_WB32(st->codecpar->extradata + 2, compresstype);
    avio_read(s->pb, st->codecpar->extradata + 6, dict_entries * 4);
    avio_skip(s->pb, 1);
    st->codecpar->extradata[dict_entries * 4 + 6] = avio_r8(s->pb);

    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}