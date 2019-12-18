#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_4__ selective_color_func_type ;
struct TYPE_20__ {int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; } ;
typedef  TYPE_5__ ThreadData ;
struct TYPE_23__ {TYPE_3__* internal; TYPE_6__* priv; TYPE_7__** outputs; } ;
struct TYPE_22__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_8__* dst; } ;
struct TYPE_21__ {size_t is_16bit; size_t correction_method; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* execute ) (TYPE_8__*,TYPE_4__ const,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_6__ SelectiveColorContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_7__ AVFilterLink ;
typedef  TYPE_8__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_copy_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 scalar_t__ av_frame_is_writable (int /*<<< orphan*/ *) ; 
 int ff_filter_frame (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_8__*) ; 
 int /*<<< orphan*/ * ff_get_video_buffer (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  selective_color_direct_absolute_16 135 
#define  selective_color_direct_absolute_8 134 
#define  selective_color_direct_relative_16 133 
#define  selective_color_direct_relative_8 132 
#define  selective_color_indirect_absolute_16 131 
#define  selective_color_indirect_absolute_8 130 
#define  selective_color_indirect_relative_16 129 
#define  selective_color_indirect_relative_8 128 
 int /*<<< orphan*/  stub1 (TYPE_8__*,TYPE_4__ const,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    int direct;
    AVFrame *out;
    ThreadData td;
    const SelectiveColorContext *s = ctx->priv;
    static const selective_color_func_type funcs[2][2][2] = {
        {
            {selective_color_indirect_absolute_8, selective_color_indirect_relative_8},
            {selective_color_direct_absolute_8,   selective_color_direct_relative_8},
        },{
            {selective_color_indirect_absolute_16, selective_color_indirect_relative_16},
            {selective_color_direct_absolute_16,   selective_color_direct_relative_16},
        }
    };

    if (av_frame_is_writable(in)) {
        direct = 1;
        out = in;
    } else {
        direct = 0;
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }

    td.in = in;
    td.out = out;
    ctx->internal->execute(ctx, funcs[s->is_16bit][direct][s->correction_method],
                           &td, NULL, FFMIN(inlink->h, ff_filter_get_nb_threads(ctx)));

    if (!direct)
        av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}