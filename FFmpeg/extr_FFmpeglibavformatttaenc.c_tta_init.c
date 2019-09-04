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
struct TYPE_10__ {TYPE_3__* codecpar; } ;
struct TYPE_9__ {scalar_t__ codec_id; int extradata_size; int sample_rate; scalar_t__ extradata; } ;
struct TYPE_8__ {int nb_streams; TYPE_5__** streams; TYPE_1__* priv_data; } ;
struct TYPE_7__ {int frame_size; } ;
typedef  TYPE_1__ TTAMuxContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_TTA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_5__*,int,int,int) ; 

__attribute__((used)) static int tta_init(AVFormatContext *s)
{
    TTAMuxContext *tta = s->priv_data;
    AVCodecParameters *par;

    if (s->nb_streams != 1) {
        av_log(s, AV_LOG_ERROR, "Only one stream is supported\n");
        return AVERROR(EINVAL);
    }
    par = s->streams[0]->codecpar;

    if (par->codec_id != AV_CODEC_ID_TTA) {
        av_log(s, AV_LOG_ERROR, "Unsupported codec\n");
        return AVERROR(EINVAL);
    }
    if (par->extradata && par->extradata_size < 22) {
        av_log(s, AV_LOG_ERROR, "Invalid TTA extradata\n");
        return AVERROR_INVALIDDATA;
    }

    /* Prevent overflow */
    if (par->sample_rate > 0x7FFFFFu) {
        av_log(s, AV_LOG_ERROR, "Sample rate too large\n");
        return AVERROR(EINVAL);
    }
    tta->frame_size = par->sample_rate * 256 / 245;
    avpriv_set_pts_info(s->streams[0], 64, 1, par->sample_rate);

    return 0;
}