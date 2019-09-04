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
struct TYPE_9__ {TYPE_1__* codecpar; int /*<<< orphan*/  need_parsing; } ;
struct TYPE_8__ {int width; int height; int channels; int sample_rate; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_FULL ; 
 int /*<<< orphan*/  AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S16LE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FIRST ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 

__attribute__((used)) static int sdr2_read_header(AVFormatContext *s)
{
    AVStream *st, *ast;

    ast = avformat_new_stream(s, 0);
    if (!ast)
        return AVERROR(ENOMEM);

    st = avformat_new_stream(s, 0);
    if (!st)
        return AVERROR(ENOMEM);

    avio_skip(s->pb, 20);
    avpriv_set_pts_info(st, 64, 1, avio_rl32(s->pb));
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->width      = avio_rl32(s->pb);
    st->codecpar->height     = avio_rl32(s->pb);
    st->codecpar->codec_id   = AV_CODEC_ID_H264;
    st->need_parsing      = AVSTREAM_PARSE_FULL;

    ast->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
    ast->codecpar->channels    = 1;
    ast->codecpar->sample_rate = 8000;
    ast->codecpar->codec_id    = AV_CODEC_ID_PCM_S16LE;
    avpriv_set_pts_info(ast, 64, 1, 8000);

    avio_seek(s->pb, FIRST, SEEK_SET);

    return 0;
}