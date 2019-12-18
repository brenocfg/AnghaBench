#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_11__ {int request_channel_layout; } ;
struct TYPE_10__ {int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_9__ {int nb_channels; int nb_programs; int /*<<< orphan*/ * end_gain; int /*<<< orphan*/ * begin_gain; int /*<<< orphan*/ * history; int /*<<< orphan*/ ** channels; TYPE_6__* avctx; } ;
typedef  TYPE_1__ DBEContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AV_CH_LAYOUT_NATIVE ; 
 int FRAME_SAMPLES ; 
 int /*<<< orphan*/  apply_gain (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 size_t* ch_reorder_4 ; 
 size_t* ch_reorder_6 ; 
 size_t* ch_reorder_8 ; 
 size_t* ch_reorder_n ; 
 int ff_get_buffer (TYPE_6__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transform (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*) ; 

__attribute__((used)) static int filter_frame(DBEContext *s, AVFrame *frame)
{
    const uint8_t *reorder;
    int ch, ret;

    if (s->nb_channels == 4)
        reorder = ch_reorder_4;
    else if (s->nb_channels == 6)
        reorder = ch_reorder_6;
    else if (s->nb_programs == 1 && !(s->avctx->request_channel_layout & AV_CH_LAYOUT_NATIVE))
        reorder = ch_reorder_8;
    else
        reorder = ch_reorder_n;

    frame->nb_samples = FRAME_SAMPLES;
    if ((ret = ff_get_buffer(s->avctx, frame, 0)) < 0)
        return ret;

    for (ch = 0; ch < s->nb_channels; ch++) {
        float *output = (float *)frame->extended_data[reorder[ch]];
        transform(s, &s->channels[0][ch], s->history[ch], output);
        transform(s, &s->channels[1][ch], s->history[ch], output + FRAME_SAMPLES / 2);
        apply_gain(s, s->begin_gain[ch], s->end_gain[ch], output);
    }

    return 0;
}