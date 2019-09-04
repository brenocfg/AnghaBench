#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ hw_frames_ctx; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw_frames_ctx; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ InputFilter ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_ref (scalar_t__) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

int ifilter_parameters_from_frame(InputFilter *ifilter, const AVFrame *frame)
{
    av_buffer_unref(&ifilter->hw_frames_ctx);

    ifilter->format = frame->format;

    ifilter->width               = frame->width;
    ifilter->height              = frame->height;
    ifilter->sample_aspect_ratio = frame->sample_aspect_ratio;

    ifilter->sample_rate         = frame->sample_rate;
    ifilter->channels            = frame->channels;
    ifilter->channel_layout      = frame->channel_layout;

    if (frame->hw_frames_ctx) {
        ifilter->hw_frames_ctx = av_buffer_ref(frame->hw_frames_ctx);
        if (!ifilter->hw_frames_ctx)
            return AVERROR(ENOMEM);
    }

    return 0;
}