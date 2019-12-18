#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int status_out; int /*<<< orphan*/  frame_count_out; int /*<<< orphan*/  max_samples; scalar_t__ min_samples; int /*<<< orphan*/  fifo; int /*<<< orphan*/ * dst; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_1__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  ff_avfilter_link_set_out_status (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int ff_filter_frame_framed (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_filter_set_ready (int /*<<< orphan*/ *,int) ; 
 int ff_framequeue_queued_frames (int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_frame (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int ff_inlink_consume_samples (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  filter_unblock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ff_filter_frame_to_filter(AVFilterLink *link)
{
    AVFrame *frame = NULL;
    AVFilterContext *dst = link->dst;
    int ret;

    av_assert1(ff_framequeue_queued_frames(&link->fifo));
    ret = link->min_samples ?
          ff_inlink_consume_samples(link, link->min_samples, link->max_samples, &frame) :
          ff_inlink_consume_frame(link, &frame);
    av_assert1(ret);
    if (ret < 0) {
        av_assert1(!frame);
        return ret;
    }
    /* The filter will soon have received a new frame, that may allow it to
       produce one or more: unblock its outputs. */
    filter_unblock(dst);
    /* AVFilterPad.filter_frame() expect frame_count_out to have the value
       before the frame; ff_filter_frame_framed() will re-increment it. */
    link->frame_count_out--;
    ret = ff_filter_frame_framed(link, frame);
    if (ret < 0 && ret != link->status_out) {
        ff_avfilter_link_set_out_status(link, ret, AV_NOPTS_VALUE);
    } else {
        /* Run once again, to see if several frames were available, or if
           the input status has also changed, or any other reason. */
        ff_filter_set_ready(dst, 300);
    }
    return ret;
}