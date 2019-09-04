#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t nb_samples; int /*<<< orphan*/ * extended_data; int /*<<< orphan*/  format; int /*<<< orphan*/  channel_layout; } ;
struct TYPE_10__ {int channels; TYPE_1__* avctx; } ;
struct TYPE_9__ {size_t frame_size; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  sample_fmt; } ;
typedef  TYPE_2__ OpusEncContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 TYPE_3__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 scalar_t__ av_frame_get_buffer (TYPE_3__*,int) ; 
 size_t av_get_bytes_per_sample (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static AVFrame *spawn_empty_frame(OpusEncContext *s)
{
    AVFrame *f = av_frame_alloc();
    if (!f)
        return NULL;
    f->format         = s->avctx->sample_fmt;
    f->nb_samples     = s->avctx->frame_size;
    f->channel_layout = s->avctx->channel_layout;
    if (av_frame_get_buffer(f, 4)) {
        av_frame_free(&f);
        return NULL;
    }
    for (int i = 0; i < s->channels; i++) {
        size_t bps = av_get_bytes_per_sample(f->format);
        memset(f->extended_data[i], 0, bps*f->nb_samples);
    }
    return f;
}