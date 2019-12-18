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
struct TYPE_10__ {int nb_frames; int duration; TYPE_1__* codecpar; } ;
struct TYPE_9__ {int frames; int bits; int rate; int block_align; int has_video; int has_audio; int curstrm; scalar_t__ cur_frame; } ;
struct TYPE_8__ {int width; int height; int /*<<< orphan*/  format; int /*<<< orphan*/  codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ SIFFContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_VB ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_PAL8 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MKTAG (char,char,char,char) ; 
 scalar_t__ TAG_VBHD ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int create_audio_stream (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int siff_parse_vbv1(AVFormatContext *s, SIFFContext *c, AVIOContext *pb)
{
    AVStream *st;
    int width, height;

    if (avio_rl32(pb) != TAG_VBHD) {
        av_log(s, AV_LOG_ERROR, "Header chunk is missing\n");
        return AVERROR_INVALIDDATA;
    }
    if (avio_rb32(pb) != 32) {
        av_log(s, AV_LOG_ERROR, "Header chunk size is incorrect\n");
        return AVERROR_INVALIDDATA;
    }
    if (avio_rl16(pb) != 1) {
        av_log(s, AV_LOG_ERROR, "Incorrect header version\n");
        return AVERROR_INVALIDDATA;
    }
    width  = avio_rl16(pb);
    height = avio_rl16(pb);
    avio_skip(pb, 4);
    c->frames = avio_rl16(pb);
    if (!c->frames) {
        av_log(s, AV_LOG_ERROR, "File contains no frames ???\n");
        return AVERROR_INVALIDDATA;
    }
    c->bits        = avio_rl16(pb);
    c->rate        = avio_rl16(pb);
    c->block_align = c->rate * (c->bits >> 3);

    avio_skip(pb, 16); // zeroes

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id   = AV_CODEC_ID_VB;
    st->codecpar->codec_tag  = MKTAG('V', 'B', 'V', '1');
    st->codecpar->width      = width;
    st->codecpar->height     = height;
    st->codecpar->format     = AV_PIX_FMT_PAL8;
    st->nb_frames            =
    st->duration             = c->frames;
    avpriv_set_pts_info(st, 16, 1, 12);

    c->cur_frame = 0;
    c->has_video = 1;
    c->has_audio = !!c->rate;
    c->curstrm   = -1;
    if (c->has_audio)
        return create_audio_stream(s, c);
    return 0;
}