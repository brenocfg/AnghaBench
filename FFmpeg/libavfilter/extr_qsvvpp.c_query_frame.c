#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  Info; } ;
typedef  TYPE_3__ mfxFrameSurface1 ;
struct TYPE_23__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  hw_frames_ctx; int /*<<< orphan*/ * src; } ;
struct TYPE_22__ {TYPE_3__* surface; TYPE_3__ surface_internal; TYPE_10__* frame; } ;
struct TYPE_18__ {int /*<<< orphan*/  Out; } ;
struct TYPE_19__ {TYPE_1__ vpp; } ;
struct TYPE_21__ {TYPE_2__ vpp_param; int /*<<< orphan*/  out_mem_mode; int /*<<< orphan*/  out_frame_list; } ;
struct TYPE_17__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__* data; } ;
typedef  TYPE_4__ QSVVPPContext ;
typedef  TYPE_5__ QSVFrame ;
typedef  TYPE_6__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  FFALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IS_SYSTEM_MEMORY (int /*<<< orphan*/ ) ; 
 TYPE_10__* av_frame_alloc () ; 
 int av_hwframe_get_buffer (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clear_unused_frames (int /*<<< orphan*/ ) ; 
 TYPE_10__* ff_get_video_buffer (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* get_free_frame (int /*<<< orphan*/ *) ; 
 int map_frame_to_surface (TYPE_10__*,TYPE_3__*) ; 

__attribute__((used)) static QSVFrame *query_frame(QSVVPPContext *s, AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    QSVFrame        *out_frame;
    int              ret;

    clear_unused_frames(s->out_frame_list);

    out_frame = get_free_frame(&s->out_frame_list);
    if (!out_frame)
        return NULL;

    /* For video memory, get a hw frame;
     * For system memory, get a sw frame and map it into a mfx_surface. */
    if (!IS_SYSTEM_MEMORY(s->out_mem_mode)) {
        out_frame->frame = av_frame_alloc();
        if (!out_frame->frame)
            return NULL;

        ret = av_hwframe_get_buffer(outlink->hw_frames_ctx, out_frame->frame, 0);
        if (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Can't allocate a surface.\n");
            return NULL;
        }

        out_frame->surface = (mfxFrameSurface1 *)out_frame->frame->data[3];
    } else {
        /* Get a frame with aligned dimensions.
         * Libmfx need system memory being 128x64 aligned */
        out_frame->frame = ff_get_video_buffer(outlink,
                                               FFALIGN(outlink->w, 128),
                                               FFALIGN(outlink->h, 64));
        if (!out_frame->frame)
            return NULL;

        out_frame->frame->width  = outlink->w;
        out_frame->frame->height = outlink->h;

        ret = map_frame_to_surface(out_frame->frame,
                                  &out_frame->surface_internal);
        if (ret < 0)
            return NULL;

        out_frame->surface = &out_frame->surface_internal;
    }

    out_frame->surface->Info = s->vpp_param.vpp.Out;

    return out_frame;
}