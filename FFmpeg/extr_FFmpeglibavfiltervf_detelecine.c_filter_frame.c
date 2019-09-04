#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_3__* priv; TYPE_5__** outputs; } ;
struct TYPE_21__ {int /*<<< orphan*/  frame_count_in; TYPE_6__* dst; } ;
struct TYPE_20__ {scalar_t__ pts; int* linesize; scalar_t__* data; } ;
struct TYPE_18__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_19__ {scalar_t__ start_time; int nskip_fields; int nb_planes; int* planeheight; int occupied; int init_len; int* pattern; size_t pattern_pos; int first_field; TYPE_2__ ts_unit; TYPE_15__** frame; int /*<<< orphan*/ * stride; TYPE_1__* temp; } ;
struct TYPE_17__ {int* linesize; scalar_t__* data; } ;
struct TYPE_16__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_3__ DetelecineContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_4__* av_frame_clone (TYPE_15__*) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__,int,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ av_rescale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *inpicref)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    DetelecineContext *s = ctx->priv;
    int i, len = 0, ret = 0, out = 0;

    if (s->start_time == AV_NOPTS_VALUE)
        s->start_time = inpicref->pts;

    if (s->nskip_fields >= 2) {
        s->nskip_fields -= 2;
        av_frame_free(&inpicref);
        return 0;
    } else if (s->nskip_fields >= 1) {
        for (i = 0; i < s->nb_planes; i++) {
            av_image_copy_plane(s->temp->data[i], s->temp->linesize[i],
                                inpicref->data[i], inpicref->linesize[i],
                                s->stride[i],
                                s->planeheight[i]);
        }
        s->occupied = 1;
        s->nskip_fields--;
        av_frame_free(&inpicref);
        return 0;
    }

    if (s->nskip_fields == 0) {
        len = s->init_len;
        s->init_len = 0;
        while(!len && s->pattern[s->pattern_pos]) {
            len = s->pattern[s->pattern_pos] - '0';
            s->pattern_pos++;
        }

        if (!s->pattern[s->pattern_pos])
            s->pattern_pos = 0;

        if(!len) { // do not output any field as the entire pattern is zero
            av_frame_free(&inpicref);
            return 0;
        }

        if (len == 1 && s->occupied) {
            s->occupied = 0;
            // output THIS image as-is
            for (i = 0; i < s->nb_planes; i++)
                av_image_copy_plane(s->frame[out]->data[i], s->frame[out]->linesize[i],
                                    s->temp->data[i], s->temp->linesize[i],
                                    s->stride[i],
                                    s->planeheight[i]);
            len = 0;
            while(!len && s->pattern[s->pattern_pos]) {
                len = s->pattern[s->pattern_pos] - '0';
                s->pattern_pos++;
            }

            if (!s->pattern[s->pattern_pos])
                s->pattern_pos = 0;

            s->occupied = 0;
            ++out;
        }

        if (s->occupied) {
            for (i = 0; i < s->nb_planes; i++) {
                // fill in the EARLIER field from the new pic
                av_image_copy_plane(s->frame[out]->data[i] + s->frame[out]->linesize[i] * s->first_field,
                                    s->frame[out]->linesize[i] * 2,
                                    inpicref->data[i] + inpicref->linesize[i] * s->first_field,
                                    inpicref->linesize[i] * 2,
                                    s->stride[i],
                                    (s->planeheight[i] - s->first_field + 1) / 2);
                // fill in the LATER field from the buffered pic
                av_image_copy_plane(s->frame[out]->data[i] + s->frame[out]->linesize[i] * !s->first_field,
                                    s->frame[out]->linesize[i] * 2,
                                    s->temp->data[i] + s->temp->linesize[i] * !s->first_field,
                                    s->temp->linesize[i] * 2,
                                    s->stride[i],
                                    (s->planeheight[i] - !s->first_field + 1) / 2);
            }

            s->occupied = 0;
            if (len <= 2) {
                for (i = 0; i < s->nb_planes; i++) {
                    av_image_copy_plane(s->temp->data[i], s->temp->linesize[i],
                                        inpicref->data[i], inpicref->linesize[i],
                                        s->stride[i],
                                        s->planeheight[i]);
                }
                s->occupied = 1;
            }
            ++out;
            len = (len >= 3) ? len - 3 : 0;
        } else {
            if (len >= 2) {
                // output THIS image as-is
                for (i = 0; i < s->nb_planes; i++)
                    av_image_copy_plane(s->frame[out]->data[i], s->frame[out]->linesize[i],
                                        inpicref->data[i], inpicref->linesize[i],
                                        s->stride[i],
                                        s->planeheight[i]);
                len -= 2;
                ++out;
            } else if (len == 1) {
                // output THIS image as-is
                for (i = 0; i < s->nb_planes; i++)
                    av_image_copy_plane(s->frame[out]->data[i], s->frame[out]->linesize[i],
                                        inpicref->data[i], inpicref->linesize[i],
                                        s->stride[i],
                                        s->planeheight[i]);

                for (i = 0; i < s->nb_planes; i++) {
                    av_image_copy_plane(s->temp->data[i], s->temp->linesize[i],
                                        inpicref->data[i], inpicref->linesize[i],
                                        s->stride[i],
                                        s->planeheight[i]);
                }
                s->occupied = 1;

                len--;
                ++out;
            }
        }

        if (len == 1 && s->occupied)
        {
            len--;
            s->occupied = 0;
        }
    }
    s->nskip_fields = len;

    for (i = 0; i < out; ++i) {
        AVFrame *frame = av_frame_clone(s->frame[i]);

        if (!frame) {
            av_frame_free(&inpicref);
            return AVERROR(ENOMEM);
        }

        av_frame_copy_props(frame, inpicref);
        frame->pts = ((s->start_time == AV_NOPTS_VALUE) ? 0 : s->start_time) +
                     av_rescale(outlink->frame_count_in, s->ts_unit.num,
                                s->ts_unit.den);
        ret = ff_filter_frame(outlink, frame);
    }

    av_frame_free(&inpicref);

    return ret;
}