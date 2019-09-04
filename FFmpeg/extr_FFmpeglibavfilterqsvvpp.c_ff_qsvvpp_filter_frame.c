#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_18__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxSyncPoint ;
struct TYPE_27__ {TYPE_4__** outputs; } ;
struct TYPE_26__ {int /*<<< orphan*/  time_base; TYPE_5__* dst; } ;
struct TYPE_25__ {TYPE_10__* frame; TYPE_18__* surface; } ;
struct TYPE_24__ {int (* filter_frame ) (TYPE_4__*,TYPE_10__*) ;int /*<<< orphan*/  session; } ;
struct TYPE_23__ {int /*<<< orphan*/  TimeStamp; } ;
struct TYPE_22__ {TYPE_1__ Data; } ;
struct TYPE_21__ {int /*<<< orphan*/  pts; } ;
typedef  TYPE_2__ QSVVPPContext ;
typedef  TYPE_3__ QSVFrame ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FF_INLINK_IDX (TYPE_4__*) ; 
 scalar_t__ MFXVideoCORE_SyncOperation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MFXVideoVPP_RunFrameVPPAsync (int /*<<< orphan*/ ,TYPE_18__*,TYPE_18__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MFX_ERR_MORE_DATA ; 
 int MFX_ERR_MORE_SURFACE ; 
 int MFX_WRN_DEVICE_BUSY ; 
 int /*<<< orphan*/  av_frame_free (TYPE_10__**) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_usleep (int) ; 
 int /*<<< orphan*/  default_tb ; 
 TYPE_3__* query_frame (TYPE_2__*,TYPE_4__*) ; 
 int stub1 (TYPE_4__*,TYPE_10__*) ; 
 TYPE_3__* submit_frame (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ; 

int ff_qsvvpp_filter_frame(QSVVPPContext *s, AVFilterLink *inlink, AVFrame *picref)
{
    AVFilterContext  *ctx     = inlink->dst;
    AVFilterLink     *outlink = ctx->outputs[0];
    mfxSyncPoint      sync;
    QSVFrame         *in_frame, *out_frame;
    int               ret, filter_ret;

    in_frame = submit_frame(s, inlink, picref);
    if (!in_frame) {
        av_log(ctx, AV_LOG_ERROR, "Failed to submit frame on input[%d]\n",
               FF_INLINK_IDX(inlink));
        return AVERROR(ENOMEM);
    }

    do {
        out_frame = query_frame(s, outlink);
        if (!out_frame) {
            av_log(ctx, AV_LOG_ERROR, "Failed to query an output frame.\n");
            return AVERROR(ENOMEM);
        }

        do {
            ret = MFXVideoVPP_RunFrameVPPAsync(s->session, in_frame->surface,
                                               out_frame->surface, NULL, &sync);
            if (ret == MFX_WRN_DEVICE_BUSY)
                av_usleep(500);
        } while (ret == MFX_WRN_DEVICE_BUSY);

        if (ret < 0 && ret != MFX_ERR_MORE_SURFACE) {
            /* Ignore more_data error */
            if (ret == MFX_ERR_MORE_DATA)
                ret = AVERROR(EAGAIN);
            break;
        }

        if (MFXVideoCORE_SyncOperation(s->session, sync, 1000) < 0)
            av_log(ctx, AV_LOG_WARNING, "Sync failed.\n");

        out_frame->frame->pts = av_rescale_q(out_frame->surface->Data.TimeStamp,
                                             default_tb, outlink->time_base);

        filter_ret = s->filter_frame(outlink, out_frame->frame);
        if (filter_ret < 0) {
            av_frame_free(&out_frame->frame);
            ret = filter_ret;
            break;
        }
        out_frame->frame = NULL;
    } while(ret == MFX_ERR_MORE_SURFACE);

    return ret;
}