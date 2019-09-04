#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ is_disabled; TYPE_4__** outputs; TYPE_2__* priv; } ;
struct TYPE_25__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_5__* dst; } ;
struct TYPE_24__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_23__ {scalar_t__ nb_next; scalar_t__ nb_prev; int nb_planes; int planesf; TYPE_3__* cur; TYPE_3__* prev; TYPE_3__* next; TYPE_1__* planes; } ;
struct TYPE_22__ {int /*<<< orphan*/  buffer_linesize; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  planeheight; int /*<<< orphan*/  planewidth; } ;
typedef  TYPE_1__ PlaneContext ;
typedef  TYPE_2__ FFTdnoizContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 size_t CURRENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t NEXT ; 
 size_t PREV ; 
 void* av_frame_clone (TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_3__*) ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  export_plane (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* ff_get_video_buffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_plane2d (TYPE_2__*,int) ; 
 int /*<<< orphan*/  filter_plane3d1 (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_plane3d2 (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  import_plane (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    FFTdnoizContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    int direct, plane;
    AVFrame *out;

    if (s->nb_next > 0 && s->nb_prev > 0) {
        av_frame_free(&s->prev);
        s->prev = s->cur;
        s->cur = s->next;
        s->next = in;

        if (!s->prev && s->cur) {
            s->prev = av_frame_clone(s->cur);
            if (!s->prev)
                return AVERROR(ENOMEM);
        }
        if (!s->cur)
            return 0;
    } else if (s->nb_next > 0) {
        av_frame_free(&s->cur);
        s->cur = s->next;
        s->next = in;

        if (!s->cur)
            return 0;
    } else if (s->nb_prev > 0) {
        av_frame_free(&s->prev);
        s->prev = s->cur;
        s->cur = in;

        if (!s->prev)
            s->prev = av_frame_clone(s->cur);
        if (!s->prev)
            return AVERROR(ENOMEM);
    } else {
        s->cur = in;
    }

    if (av_frame_is_writable(in) && s->nb_next == 0 && s->nb_prev == 0) {
        direct = 1;
        out = in;
    } else {
        direct = 0;
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out)
            return AVERROR(ENOMEM);
        av_frame_copy_props(out, s->cur);
    }

    for (plane = 0; plane < s->nb_planes; plane++) {
        PlaneContext *p = &s->planes[plane];

        if (!((1 << plane) & s->planesf) || ctx->is_disabled) {
            if (!direct)
                av_image_copy_plane(out->data[plane], out->linesize[plane],
                                    s->cur->data[plane], s->cur->linesize[plane],
                                    p->planewidth, p->planeheight);
            continue;
        }

        if (s->next) {
            import_plane(s, s->next->data[plane], s->next->linesize[plane],
                         p->buffer[NEXT], p->buffer_linesize, plane);
        }

        if (s->prev) {
            import_plane(s, s->prev->data[plane], s->prev->linesize[plane],
                         p->buffer[PREV], p->buffer_linesize, plane);
        }

        import_plane(s, s->cur->data[plane], s->cur->linesize[plane],
                     p->buffer[CURRENT], p->buffer_linesize, plane);

        if (s->next && s->prev) {
            filter_plane3d2(s, plane, p->buffer[PREV], p->buffer[NEXT]);
        } else if (s->next) {
            filter_plane3d1(s, plane, p->buffer[NEXT]);
        } else  if (s->prev) {
            filter_plane3d1(s, plane, p->buffer[PREV]);
        } else {
            filter_plane2d(s, plane);
        }

        export_plane(s, out->data[plane], out->linesize[plane],
                     p->buffer[CURRENT], p->buffer_linesize, plane);
    }

    if (s->nb_next == 0 && s->nb_prev == 0) {
        if (direct) {
            s->cur = NULL;
        } else {
            av_frame_free(&s->cur);
        }
    }
    return ff_filter_frame(outlink, out);
}