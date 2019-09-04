#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_4__** outputs; TYPE_1__* priv; } ;
struct TYPE_21__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_20__ {scalar_t__ pts; } ;
struct TYPE_19__ {scalar_t__ type; int /*<<< orphan*/  view; } ;
struct TYPE_18__ {scalar_t__ format; scalar_t__ double_pts; TYPE_3__** input_views; } ;
typedef  TYPE_1__ FramepackContext ;
typedef  TYPE_2__ AVStereo3D ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ AV_STEREO3D_FRAMESEQUENCE ; 
 int /*<<< orphan*/  AV_STEREO3D_VIEW_LEFT ; 
 int /*<<< orphan*/  AV_STEREO3D_VIEW_RIGHT ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t LEFT ; 
 int av_frame_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 TYPE_2__* av_stereo3d_create_side_data (TYPE_3__*) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* ff_get_video_buffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spatial_frame_pack (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static int try_push_frame(AVFilterContext *ctx)
{
    FramepackContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVStereo3D *stereo;
    int ret, i;

    if (!(s->input_views[0] && s->input_views[1]))
        return 0;
    if (s->format == AV_STEREO3D_FRAMESEQUENCE) {
        if (s->double_pts == AV_NOPTS_VALUE)
            s->double_pts = s->input_views[LEFT]->pts;

        for (i = 0; i < 2; i++) {
            // set correct timestamps
            s->input_views[i]->pts = s->double_pts++;

            // set stereo3d side data
            stereo = av_stereo3d_create_side_data(s->input_views[i]);
            if (!stereo)
                return AVERROR(ENOMEM);
            stereo->type = s->format;
            stereo->view = i == LEFT ? AV_STEREO3D_VIEW_LEFT
                                     : AV_STEREO3D_VIEW_RIGHT;

            // filter the frame and immediately relinquish its pointer
            ret = ff_filter_frame(outlink, s->input_views[i]);
            s->input_views[i] = NULL;
            if (ret < 0)
                return ret;
        }
        return ret;
    } else {
        AVFrame *dst = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!dst)
            return AVERROR(ENOMEM);

        spatial_frame_pack(outlink, dst);

        // get any property from the original frame
        ret = av_frame_copy_props(dst, s->input_views[LEFT]);
        if (ret < 0) {
            av_frame_free(&dst);
            return ret;
        }

        for (i = 0; i < 2; i++)
            av_frame_free(&s->input_views[i]);

        // set stereo3d side data
        stereo = av_stereo3d_create_side_data(dst);
        if (!stereo) {
            av_frame_free(&dst);
            return AVERROR(ENOMEM);
        }
        stereo->type = s->format;

        return ff_filter_frame(outlink, dst);
    }
}