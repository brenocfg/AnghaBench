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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_19__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_18__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* dst; } ;
struct TYPE_17__ {scalar_t__ top_field_first; int height; int* linesize; int /*<<< orphan*/ ** data; scalar_t__ interlaced_frame; } ;
struct TYPE_16__ {scalar_t__ dst_tff; int* line_size; } ;
typedef  TYPE_1__ FieldOrderContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,char*) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext   *ctx     = inlink->dst;
    FieldOrderContext *s       = ctx->priv;
    AVFilterLink      *outlink = ctx->outputs[0];
    int h, plane, src_line_step, dst_line_step, line_size, line;
    uint8_t *dst, *src;
    AVFrame *out;

    if (!frame->interlaced_frame ||
        frame->top_field_first == s->dst_tff) {
        av_log(ctx, AV_LOG_VERBOSE,
               "Skipping %s.\n",
               frame->interlaced_frame ?
               "frame with same field order" : "progressive frame");
        return ff_filter_frame(outlink, frame);
    }

    if (av_frame_is_writable(frame)) {
        out = frame;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&frame);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, frame);
    }

    av_log(ctx, AV_LOG_TRACE,
            "picture will move %s one line\n",
            s->dst_tff ? "up" : "down");
    h = frame->height;
    for (plane = 0; plane < 4 && frame->data[plane] && frame->linesize[plane]; plane++) {
        dst_line_step = out->linesize[plane] * (h > 2);
        src_line_step = frame->linesize[plane] * (h > 2);
        line_size = s->line_size[plane];
        dst = out->data[plane];
        src = frame->data[plane];
        if (s->dst_tff) {
            /** Move every line up one line, working from
             *  the top to the bottom of the frame.
             *  The original top line is lost.
             *  The new last line is created as a copy of the
             *  penultimate line from that field. */
            for (line = 0; line < h; line++) {
                if (1 + line < frame->height) {
                    memcpy(dst, src + src_line_step, line_size);
                } else {
                    memcpy(dst, src - 2 * src_line_step, line_size);
                }
                dst += dst_line_step;
                src += src_line_step;
            }
        } else {
            /** Move every line down one line, working from
             *  the bottom to the top of the frame.
             *  The original bottom line is lost.
             *  The new first line is created as a copy of the
             *  second line from that field. */
            dst += (h - 1) * dst_line_step;
            src += (h - 1) * src_line_step;
            for (line = h - 1; line >= 0 ; line--) {
                if (line > 0) {
                    memcpy(dst, src - src_line_step, line_size);
                } else {
                    memcpy(dst, src + 2 * src_line_step, line_size);
                }
                dst -= dst_line_step;
                src -= src_line_step;
            }
        }
    }
    out->top_field_first = s->dst_tff;

    if (frame != out)
        av_frame_free(&frame);
    return ff_filter_frame(outlink, out);
}