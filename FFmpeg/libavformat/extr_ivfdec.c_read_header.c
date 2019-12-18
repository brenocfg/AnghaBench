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
struct TYPE_13__ {int /*<<< orphan*/  pb; } ;
struct TYPE_12__ {void* den; void* num; } ;
struct TYPE_11__ {int /*<<< orphan*/  need_parsing; void* duration; TYPE_1__* codecpar; } ;
struct TYPE_10__ {void* height; void* width; void* codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVRational ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_HEADERS ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 void* avio_rl16 (int /*<<< orphan*/ ) ; 
 void* avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,void*,void*) ; 
 int /*<<< orphan*/  ff_codec_bmp_tags ; 
 int /*<<< orphan*/  ff_codec_get_id (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int read_header(AVFormatContext *s)
{
    AVStream *st;
    AVRational time_base;

    avio_rl32(s->pb); // DKIF
    avio_rl16(s->pb); // version
    avio_rl16(s->pb); // header size

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);


    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_tag  = avio_rl32(s->pb);
    st->codecpar->codec_id   = ff_codec_get_id(ff_codec_bmp_tags, st->codecpar->codec_tag);
    st->codecpar->width      = avio_rl16(s->pb);
    st->codecpar->height     = avio_rl16(s->pb);
    time_base.den         = avio_rl32(s->pb);
    time_base.num         = avio_rl32(s->pb);
    st->duration          = avio_rl32(s->pb);
    avio_skip(s->pb, 4); // unused

    st->need_parsing      = AVSTREAM_PARSE_HEADERS;

    if (!time_base.den || !time_base.num) {
        av_log(s, AV_LOG_ERROR, "Invalid frame rate\n");
        return AVERROR_INVALIDDATA;
    }

    avpriv_set_pts_info(st, 64, time_base.num, time_base.den);

    return 0;
}