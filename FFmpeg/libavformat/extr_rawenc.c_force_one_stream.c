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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nb_streams; TYPE_3__* oformat; TYPE_2__** streams; } ;
struct TYPE_9__ {scalar_t__ audio_codec; scalar_t__ video_codec; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_1__* codecpar; } ;
struct TYPE_7__ {scalar_t__ codec_type; } ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int force_one_stream(AVFormatContext *s)
{
    if (s->nb_streams != 1) {
        av_log(s, AV_LOG_ERROR, "%s files have exactly one stream\n",
               s->oformat->name);
        return AVERROR(EINVAL);
    }
    if (   s->oformat->audio_codec != AV_CODEC_ID_NONE
        && s->streams[0]->codecpar->codec_type != AVMEDIA_TYPE_AUDIO) {
        av_log(s, AV_LOG_ERROR, "%s files have exactly one audio stream\n",
               s->oformat->name);
        return AVERROR(EINVAL);
    }
    if (   s->oformat->video_codec != AV_CODEC_ID_NONE
        && s->streams[0]->codecpar->codec_type != AVMEDIA_TYPE_VIDEO) {
        av_log(s, AV_LOG_ERROR, "%s files have exactly one video stream\n",
               s->oformat->name);
        return AVERROR(EINVAL);
    }
    return 0;
}