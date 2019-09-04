#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/ * inputs; TYPE_3__* priv; TYPE_5__** outputs; } ;
struct TYPE_24__ {scalar_t__ request_samples; int channels; int /*<<< orphan*/  format; } ;
struct TYPE_23__ {scalar_t__ nb_samples; int /*<<< orphan*/  extended_data; int /*<<< orphan*/  pts; } ;
struct TYPE_21__ {TYPE_1__* next; } ;
struct TYPE_22__ {int allocated_samples; TYPE_4__* out; TYPE_2__ root; } ;
struct TYPE_20__ {TYPE_4__* frame; } ;
typedef  TYPE_3__ FifoContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (scalar_t__,scalar_t__) ; 
 TYPE_4__* av_frame_clone (TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_samples_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_samples_set_silence (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_offset (TYPE_5__*,TYPE_4__*,int) ; 
 int calc_ptr_alignment (TYPE_4__*) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* ff_get_audio_buffer (TYPE_5__*,int) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_pop (TYPE_3__*) ; 

__attribute__((used)) static int return_audio_frame(AVFilterContext *ctx)
{
    AVFilterLink *link = ctx->outputs[0];
    FifoContext *s = ctx->priv;
    AVFrame *head = s->root.next ? s->root.next->frame : NULL;
    AVFrame *out;
    int ret;

    /* if head is NULL then we're flushing the remaining samples in out */
    if (!head && !s->out)
        return AVERROR_EOF;

    if (!s->out &&
        head->nb_samples >= link->request_samples &&
        calc_ptr_alignment(head) >= 32) {
        if (head->nb_samples == link->request_samples) {
            out = head;
            queue_pop(s);
        } else {
            out = av_frame_clone(head);
            if (!out)
                return AVERROR(ENOMEM);

            out->nb_samples = link->request_samples;
            buffer_offset(link, head, link->request_samples);
        }
    } else {
        int nb_channels = link->channels;

        if (!s->out) {
            s->out = ff_get_audio_buffer(link, link->request_samples);
            if (!s->out)
                return AVERROR(ENOMEM);

            s->out->nb_samples = 0;
            s->out->pts                   = head->pts;
            s->allocated_samples          = link->request_samples;
        } else if (link->request_samples != s->allocated_samples) {
            av_log(ctx, AV_LOG_ERROR, "request_samples changed before the "
                   "buffer was returned.\n");
            return AVERROR(EINVAL);
        }

        while (s->out->nb_samples < s->allocated_samples) {
            int len;

            if (!s->root.next) {
                ret = ff_request_frame(ctx->inputs[0]);
                if (ret == AVERROR_EOF) {
                    av_samples_set_silence(s->out->extended_data,
                                           s->out->nb_samples,
                                           s->allocated_samples -
                                           s->out->nb_samples,
                                           nb_channels, link->format);
                    s->out->nb_samples = s->allocated_samples;
                    break;
                } else if (ret < 0)
                    return ret;
                if (!s->root.next)
                    return 0;
            }
            head = s->root.next->frame;

            len = FFMIN(s->allocated_samples - s->out->nb_samples,
                        head->nb_samples);

            av_samples_copy(s->out->extended_data, head->extended_data,
                            s->out->nb_samples, 0, len, nb_channels,
                            link->format);
            s->out->nb_samples += len;

            if (len == head->nb_samples) {
                av_frame_free(&head);
                queue_pop(s);
            } else {
                buffer_offset(link, head, len);
            }
        }
        out = s->out;
        s->out = NULL;
    }
    return ff_filter_frame(link, out);
}