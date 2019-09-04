#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* num; void* den; } ;
struct TYPE_8__ {int /*<<< orphan*/  codec; TYPE_1__ time_base; void* nb_frames; } ;
typedef  TYPE_2__ VideoProperties ;
struct TYPE_9__ {int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_CODEC_ID_VP6 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 void* avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int process_video_header_vp6(AVFormatContext *s, VideoProperties *video)
{
    AVIOContext *pb = s->pb;

    avio_skip(pb, 8);
    video->nb_frames = avio_rl32(pb);
    avio_skip(pb, 4);
    video->time_base.den = avio_rl32(pb);
    video->time_base.num = avio_rl32(pb);
    if (video->time_base.den <= 0 || video->time_base.num <= 0) {
        av_log(s, AV_LOG_ERROR, "Timebase is invalid\n");
        return AVERROR_INVALIDDATA;
    }
    video->codec   = AV_CODEC_ID_VP6;

    return 1;
}