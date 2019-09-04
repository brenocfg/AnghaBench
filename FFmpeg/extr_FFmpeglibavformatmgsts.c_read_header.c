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
typedef  int uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_12__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_11__ {TYPE_1__* codecpar; void* duration; void* nb_frames; scalar_t__ start_time; int /*<<< orphan*/  need_parsing; } ;
struct TYPE_10__ {void* codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; void* height; void* width; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVRational ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_HEADERS ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  INT_MAX ; 
 TYPE_3__ av_d2q (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_int2float (void*) ; 
 TYPE_2__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_codec_bmp_tags ; 
 int /*<<< orphan*/  ff_codec_get_id (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int read_header(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    AVStream    *st;
    AVRational  fps;
    uint32_t chunk_size;

    avio_skip(pb, 4);
    chunk_size = avio_rb32(pb);
    if (chunk_size != 80)
        return AVERROR(EIO);
    avio_skip(pb, 20);

    st = avformat_new_stream(s, 0);
    if (!st)
        return AVERROR(ENOMEM);

    st->need_parsing = AVSTREAM_PARSE_HEADERS;
    st->start_time = 0;
    st->nb_frames  =
    st->duration   = avio_rb32(pb);
    fps = av_d2q(av_int2float(avio_rb32(pb)), INT_MAX);
    st->codecpar->width  = avio_rb32(pb);
    st->codecpar->height = avio_rb32(pb);
    avio_skip(pb, 12);
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_tag  = avio_rb32(pb);
    st->codecpar->codec_id   = ff_codec_get_id(ff_codec_bmp_tags,
                                               st->codecpar->codec_tag);
    avpriv_set_pts_info(st, 64, fps.den, fps.num);
    avio_skip(pb, 20);

    return 0;
}