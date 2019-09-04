#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_34__ {TYPE_3__* priv; TYPE_6__** outputs; } ;
struct TYPE_33__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  format; TYPE_7__* dst; } ;
struct TYPE_32__ {int /*<<< orphan*/  linesize; scalar_t__ data; scalar_t__ repeat_pict; int /*<<< orphan*/  top_field_first; scalar_t__ interlaced_frame; } ;
struct TYPE_31__ {scalar_t__ planes; } ;
struct TYPE_30__ {int /*<<< orphan*/  planewidth; } ;
struct TYPE_29__ {int length; TYPE_1__* buffer; } ;
struct TYPE_28__ {scalar_t__ planes; } ;
typedef  TYPE_2__ PullupFrame ;
typedef  TYPE_3__ PullupContext ;
typedef  TYPE_4__ PullupBuffer ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterLink ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_5__**) ; 
 int /*<<< orphan*/  av_image_copy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int ff_filter_frame (TYPE_6__*,TYPE_5__*) ; 
 TYPE_5__* ff_get_video_buffer (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* pullup_get_buffer (TYPE_3__*,int) ; 
 TYPE_2__* pullup_get_frame (TYPE_3__*) ; 
 int /*<<< orphan*/  pullup_pack_frame (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pullup_release_buffer (TYPE_4__*,int) ; 
 int /*<<< orphan*/  pullup_release_frame (TYPE_2__*) ; 
 int /*<<< orphan*/  pullup_submit_field (TYPE_3__*,TYPE_4__*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    PullupContext *s = ctx->priv;
    PullupBuffer *b;
    PullupFrame *f;
    AVFrame *out;
    int p, ret = 0;

    b = pullup_get_buffer(s, 2);
    if (!b) {
        av_log(ctx, AV_LOG_WARNING, "Could not get buffer!\n");
        f = pullup_get_frame(s);
        pullup_release_frame(f);
        goto end;
    }

    av_image_copy(b->planes, s->planewidth,
                  (const uint8_t**)in->data, in->linesize,
                  inlink->format, inlink->w, inlink->h);

    p = in->interlaced_frame ? !in->top_field_first : 0;
    pullup_submit_field(s, b, p  );
    pullup_submit_field(s, b, p^1);

    if (in->repeat_pict)
        pullup_submit_field(s, b, p);

    pullup_release_buffer(b, 2);

    f = pullup_get_frame(s);
    if (!f)
        goto end;

    if (f->length < 2) {
        pullup_release_frame(f);
        f = pullup_get_frame(s);
        if (!f)
            goto end;
        if (f->length < 2) {
            pullup_release_frame(f);
            if (!in->repeat_pict)
                goto end;
            f = pullup_get_frame(s);
            if (!f)
                goto end;
            if (f->length < 2) {
                pullup_release_frame(f);
                goto end;
            }
        }
    }

    /* If the frame isn't already exportable... */
    if (!f->buffer)
        pullup_pack_frame(s, f);

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    av_frame_copy_props(out, in);

    av_image_copy(out->data, out->linesize,
                  (const uint8_t**)f->buffer->planes, s->planewidth,
                  inlink->format, inlink->w, inlink->h);

    ret = ff_filter_frame(outlink, out);
    pullup_release_frame(f);
end:
    av_frame_free(&in);
    return ret;
}