#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* codecpar; } ;
struct TYPE_4__ {int channels; int /*<<< orphan*/  channel_layout; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int set_channels(AVFormatContext *avctx, AVStream *st, int channels)
{
    if (channels <= 0) {
        av_log(avctx, AV_LOG_ERROR, "Channel count %d invalid.\n", channels);
        return AVERROR_INVALIDDATA;
    }
    st->codecpar->channels       = channels;
    st->codecpar->channel_layout = (st->codecpar->channels == 1) ? AV_CH_LAYOUT_MONO
                                                                 : AV_CH_LAYOUT_STEREO;
    return 0;
}