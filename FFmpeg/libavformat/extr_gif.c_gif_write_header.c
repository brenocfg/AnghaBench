#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* codecpar; } ;
struct TYPE_7__ {int nb_streams; TYPE_4__** streams; } ;
struct TYPE_6__ {scalar_t__ codec_type; scalar_t__ codec_id; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_GIF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int,int) ; 

__attribute__((used)) static int gif_write_header(AVFormatContext *s)
{
    if (s->nb_streams != 1 ||
        s->streams[0]->codecpar->codec_type != AVMEDIA_TYPE_VIDEO ||
        s->streams[0]->codecpar->codec_id   != AV_CODEC_ID_GIF) {
        av_log(s, AV_LOG_ERROR,
               "GIF muxer supports only a single video GIF stream.\n");
        return AVERROR(EINVAL);
    }

    avpriv_set_pts_info(s->streams[0], 64, 1, 100);

    return 0;
}