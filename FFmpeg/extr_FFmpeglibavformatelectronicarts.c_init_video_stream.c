#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_9__ {scalar_t__ codec; TYPE_7__ time_base; int /*<<< orphan*/  nb_frames; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  stream_index; } ;
typedef  TYPE_2__ VideoProperties ;
struct TYPE_10__ {int /*<<< orphan*/  avg_frame_rate; int /*<<< orphan*/  r_frame_rate; int /*<<< orphan*/  nb_frames; int /*<<< orphan*/  duration; TYPE_1__* codecpar; int /*<<< orphan*/  need_parsing; int /*<<< orphan*/  index; } ;
struct TYPE_8__ {scalar_t__ codec_id; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ codec_tag; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_HEADERS ; 
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_inv_q (TYPE_7__) ; 
 TYPE_3__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_video_stream(AVFormatContext *s, VideoProperties *video)
{
    AVStream *st;

    if (!video->codec)
        return 0;

    /* initialize the video decoder stream */
    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    video->stream_index = st->index;
    st->codecpar->codec_type  = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id    = video->codec;
    // parsing is necessary to make FFmpeg generate correct timestamps
    if (st->codecpar->codec_id == AV_CODEC_ID_MPEG2VIDEO)
        st->need_parsing = AVSTREAM_PARSE_HEADERS;
    st->codecpar->codec_tag   = 0; /* no fourcc */
    st->codecpar->width       = video->width;
    st->codecpar->height      = video->height;
    st->duration           = st->nb_frames = video->nb_frames;
    if (video->time_base.num)
        avpriv_set_pts_info(st, 64, video->time_base.num, video->time_base.den);
    st->r_frame_rate       =
    st->avg_frame_rate     = av_inv_q(video->time_base);
    return 0;
}