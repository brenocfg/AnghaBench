#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* apply_unsharp ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ UnsharpContext ;
struct TYPE_9__ {TYPE_2__** outputs; TYPE_1__* priv; } ;
struct TYPE_8__ {TYPE_3__* dst; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int ff_filter_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_get_video_buffer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *link, AVFrame *in)
{
    UnsharpContext *s = link->dst->priv;
    AVFilterLink *outlink   = link->dst->outputs[0];
    AVFrame *out;
    int ret = 0;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);

    ret = s->apply_unsharp(link->dst, in, out);

    av_frame_free(&in);

    if (ret < 0) {
        av_frame_free(&out);
        return ret;
    }
    return ff_filter_frame(outlink, out);
}