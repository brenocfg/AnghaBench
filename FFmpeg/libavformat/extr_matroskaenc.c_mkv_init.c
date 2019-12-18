#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct AVFormatContext {int nb_streams; int avoid_negative_ts; TYPE_3__** streams; TYPE_2__* internal; } ;
struct TYPE_6__ {TYPE_1__* codecpar; } ;
struct TYPE_5__ {int avoid_negative_ts_use_pts; } ;
struct TYPE_4__ {scalar_t__ codec_id; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_PATCHWELCOME ; 
 scalar_t__ AV_CODEC_ID_ATRAC3 ; 
 scalar_t__ AV_CODEC_ID_COOK ; 
 scalar_t__ AV_CODEC_ID_RA_288 ; 
 scalar_t__ AV_CODEC_ID_RV10 ; 
 scalar_t__ AV_CODEC_ID_RV20 ; 
 scalar_t__ AV_CODEC_ID_SIPR ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int MAX_TRACKS ; 
 int /*<<< orphan*/  av_log (struct AVFormatContext*,int /*<<< orphan*/ ,char*,int) ; 
 int avcodec_get_name (scalar_t__) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 

__attribute__((used)) static int mkv_init(struct AVFormatContext *s)
{
    int i;

    if (s->nb_streams > MAX_TRACKS) {
        av_log(s, AV_LOG_ERROR,
               "At most %d streams are supported for muxing in Matroska\n",
               MAX_TRACKS);
        return AVERROR(EINVAL);
    }

    for (i = 0; i < s->nb_streams; i++) {
        if (s->streams[i]->codecpar->codec_id == AV_CODEC_ID_ATRAC3 ||
            s->streams[i]->codecpar->codec_id == AV_CODEC_ID_COOK ||
            s->streams[i]->codecpar->codec_id == AV_CODEC_ID_RA_288 ||
            s->streams[i]->codecpar->codec_id == AV_CODEC_ID_SIPR ||
            s->streams[i]->codecpar->codec_id == AV_CODEC_ID_RV10 ||
            s->streams[i]->codecpar->codec_id == AV_CODEC_ID_RV20) {
            av_log(s, AV_LOG_ERROR,
                   "The Matroska muxer does not yet support muxing %s\n",
                   avcodec_get_name(s->streams[i]->codecpar->codec_id));
            return AVERROR_PATCHWELCOME;
        }
    }

    if (s->avoid_negative_ts < 0) {
        s->avoid_negative_ts = 1;
        s->internal->avoid_negative_ts_use_pts = 1;
    }

    for (i = 0; i < s->nb_streams; i++) {
        // ms precision is the de-facto standard timescale for mkv files
        avpriv_set_pts_info(s->streams[i], 64, 1, 1000);
    }

    return 0;
}