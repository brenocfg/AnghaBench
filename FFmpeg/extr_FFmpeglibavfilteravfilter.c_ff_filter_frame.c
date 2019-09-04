#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* filter; } ;
struct TYPE_15__ {scalar_t__ type; scalar_t__ format; scalar_t__ w; scalar_t__ h; scalar_t__ channels; scalar_t__ channel_layout; scalar_t__ sample_rate; TYPE_4__* dst; int /*<<< orphan*/  fifo; int /*<<< orphan*/  frame_count_in; scalar_t__ frame_wanted_out; scalar_t__ frame_blocked_in; } ;
struct TYPE_14__ {scalar_t__ format; scalar_t__ width; scalar_t__ height; scalar_t__ channels; scalar_t__ channel_layout; scalar_t__ sample_rate; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  FF_TPRINTF_START (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_filter_set_ready (TYPE_4__*,int) ; 
 int ff_framequeue_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ff_tlog (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ff_tlog_link (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ff_tlog_ref (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  filter_frame ; 
 int /*<<< orphan*/  filter_unblock (TYPE_4__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int ff_filter_frame(AVFilterLink *link, AVFrame *frame)
{
    int ret;
    FF_TPRINTF_START(NULL, filter_frame); ff_tlog_link(NULL, link, 1); ff_tlog(NULL, " "); ff_tlog_ref(NULL, frame, 1);

    /* Consistency checks */
    if (link->type == AVMEDIA_TYPE_VIDEO) {
        if (strcmp(link->dst->filter->name, "buffersink") &&
            strcmp(link->dst->filter->name, "format") &&
            strcmp(link->dst->filter->name, "idet") &&
            strcmp(link->dst->filter->name, "null") &&
            strcmp(link->dst->filter->name, "scale")) {
            av_assert1(frame->format                 == link->format);
            av_assert1(frame->width               == link->w);
            av_assert1(frame->height               == link->h);
        }
    } else {
        if (frame->format != link->format) {
            av_log(link->dst, AV_LOG_ERROR, "Format change is not supported\n");
            goto error;
        }
        if (frame->channels != link->channels) {
            av_log(link->dst, AV_LOG_ERROR, "Channel count change is not supported\n");
            goto error;
        }
        if (frame->channel_layout != link->channel_layout) {
            av_log(link->dst, AV_LOG_ERROR, "Channel layout change is not supported\n");
            goto error;
        }
        if (frame->sample_rate != link->sample_rate) {
            av_log(link->dst, AV_LOG_ERROR, "Sample rate change is not supported\n");
            goto error;
        }
    }

    link->frame_blocked_in = link->frame_wanted_out = 0;
    link->frame_count_in++;
    filter_unblock(link->dst);
    ret = ff_framequeue_add(&link->fifo, frame);
    if (ret < 0) {
        av_frame_free(&frame);
        return ret;
    }
    ff_filter_set_ready(link->dst, 300);
    return 0;

error:
    av_frame_free(&frame);
    return AVERROR_PATCHWELCOME;
}