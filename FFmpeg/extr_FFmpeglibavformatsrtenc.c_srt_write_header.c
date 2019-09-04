#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {int nb_streams; TYPE_5__** streams; TYPE_2__* priv_data; } ;
struct TYPE_8__ {int index; } ;
struct TYPE_7__ {scalar_t__ codec_type; scalar_t__ codec_id; } ;
typedef  TYPE_2__ SRTContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 scalar_t__ AV_CODEC_ID_SUBRIP ; 
 scalar_t__ AV_CODEC_ID_TEXT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avcodec_get_name (scalar_t__) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_5__*,int,int,int) ; 

__attribute__((used)) static int srt_write_header(AVFormatContext *avf)
{
    SRTContext *srt = avf->priv_data;

    if (avf->nb_streams != 1 ||
        avf->streams[0]->codecpar->codec_type != AVMEDIA_TYPE_SUBTITLE) {
        av_log(avf, AV_LOG_ERROR,
               "SRT supports only a single subtitles stream.\n");
        return AVERROR(EINVAL);
    }
    if (avf->streams[0]->codecpar->codec_id != AV_CODEC_ID_TEXT &&
        avf->streams[0]->codecpar->codec_id != AV_CODEC_ID_SUBRIP) {
        av_log(avf, AV_LOG_ERROR,
               "Unsupported subtitles codec: %s\n",
               avcodec_get_name(avf->streams[0]->codecpar->codec_id));
        return AVERROR(EINVAL);
    }
    avpriv_set_pts_info(avf->streams[0], 64, 1, 1000);
    srt->index = 1;
    return 0;
}