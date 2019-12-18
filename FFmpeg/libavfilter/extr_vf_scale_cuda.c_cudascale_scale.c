#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_2__* priv; } ;
struct TYPE_18__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  hw_frames_ctx; } ;
struct TYPE_17__ {TYPE_1__* planes_out; TYPE_3__* frame; TYPE_3__* tmp_frame; } ;
struct TYPE_16__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ CUDAScaleContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int av_frame_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_move_ref (TYPE_3__*,TYPE_3__*) ; 
 int av_hwframe_get_buffer (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int scalecuda_resize (TYPE_4__*,TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static int cudascale_scale(AVFilterContext *ctx, AVFrame *out, AVFrame *in)
{
    CUDAScaleContext *s = ctx->priv;
    AVFrame *src = in;
    int ret;

    ret = scalecuda_resize(ctx, s->frame, src);
    if (ret < 0)
        return ret;

    src = s->frame;
    ret = av_hwframe_get_buffer(src->hw_frames_ctx, s->tmp_frame, 0);
    if (ret < 0)
        return ret;

    av_frame_move_ref(out, s->frame);
    av_frame_move_ref(s->frame, s->tmp_frame);

    s->frame->width  = s->planes_out[0].width;
    s->frame->height = s->planes_out[0].height;

    ret = av_frame_copy_props(out, in);
    if (ret < 0)
        return ret;

    return 0;
}