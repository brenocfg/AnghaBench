#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {int /*<<< orphan*/ ** outputs; int /*<<< orphan*/ ** inputs; TYPE_1__* priv; } ;
struct TYPE_11__ {int frames_count; int /*<<< orphan*/  next_pts; scalar_t__ status; } ;
typedef  TYPE_1__ FPSContext ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_WANTED (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_filter_set_ready (TYPE_2__*,int) ; 
 int ff_inlink_acknowledge_status (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ff_inlink_check_available_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int read_frame (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_eof_pts (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int write_frame (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    FPSContext   *s       = ctx->priv;
    AVFilterLink *inlink  = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];

    int ret;
    int again = 0;
    int64_t status_pts;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    /* No buffered status: normal operation */
    if (!s->status) {

        /* Read available input frames if we have room */
        while (s->frames_count < 2 && ff_inlink_check_available_frame(inlink)) {
            ret = read_frame(ctx, s, inlink, outlink);
            if (ret < 0)
                return ret;
        }

        /* We do not yet have enough frames to produce output */
        if (s->frames_count < 2) {
            /* Check if we've hit EOF (or otherwise that an error status is set) */
            ret = ff_inlink_acknowledge_status(inlink, &s->status, &status_pts);
            if (ret > 0)
                update_eof_pts(ctx, s, inlink, outlink, status_pts);

            if (!ret) {
                /* If someone wants us to output, we'd better ask for more input */
                FF_FILTER_FORWARD_WANTED(outlink, inlink);
                return 0;
            }
        }
    }

    /* Buffered frames are available, so generate an output frame */
    if (s->frames_count > 0) {
        ret = write_frame(ctx, s, outlink, &again);
        /* Couldn't generate a frame, so schedule us to perform another step */
        if (again)
            ff_filter_set_ready(ctx, 100);
        return ret;
    }

    /* No frames left, so forward the status */
    if (s->status && s->frames_count == 0) {
        ff_outlink_set_status(outlink, s->status, s->next_pts);
        return 0;
    }

    return FFERROR_NOT_READY;
}