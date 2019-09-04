#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* need_parsing; TYPE_1__* codecpar; } ;
struct TYPE_5__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 void* AVSTREAM_PARSE_HEADERS ; 
 int /*<<< orphan*/  AV_CODEC_ID_MP2 ; 
 int /*<<< orphan*/  AV_CODEC_ID_MPEG4 ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 

__attribute__((used)) static int lmlm4_read_header(AVFormatContext *s)
{
    AVStream *st;

    if (!(st = avformat_new_stream(s, NULL)))
        return AVERROR(ENOMEM);
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id   = AV_CODEC_ID_MPEG4;
    st->need_parsing      = AVSTREAM_PARSE_HEADERS;
    avpriv_set_pts_info(st, 64, 1001, 30000);

    if (!(st = avformat_new_stream(s, NULL)))
        return AVERROR(ENOMEM);
    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id   = AV_CODEC_ID_MP2;
    st->need_parsing      = AVSTREAM_PARSE_HEADERS;

    /* the parameters will be extracted from the compressed bitstream */
    return 0;
}