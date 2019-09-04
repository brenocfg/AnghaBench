#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int index; } ;
struct TYPE_11__ {float framebits; scalar_t__ intensity_stereo; } ;
struct TYPE_9__ {int frames; int /*<<< orphan*/  framesize; } ;
struct TYPE_10__ {int max_steps; int buffered_steps; int avg_is_band; float lambda; int total_packets_out; scalar_t__ inflection_points_count; TYPE_2__ p; scalar_t__ steps_to_process; scalar_t__ cs_num; TYPE_1__* avctx; TYPE_5__** steps; } ;
struct TYPE_8__ {int bit_rate; int sample_rate; } ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;
typedef  int /*<<< orphan*/  OpusPsyStep ;
typedef  TYPE_3__ OpusPsyContext ;
typedef  TYPE_4__ CeltFrame ;

/* Variables and functions */
 int FF_BUFQUEUE_SIZE ; 
 int OPUS_BLOCK_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

void ff_opus_psy_postencode_update(OpusPsyContext *s, CeltFrame *f, OpusRangeCoder *rc)
{
    int i, frame_size = OPUS_BLOCK_SIZE(s->p.framesize);
    int steps_out = s->p.frames*(frame_size/120);
    void *tmp[FF_BUFQUEUE_SIZE];
    float ideal_fbits;

    for (i = 0; i < steps_out; i++)
        memset(s->steps[i], 0, sizeof(OpusPsyStep));

    for (i = 0; i < s->max_steps; i++)
        tmp[i] = s->steps[i];

    for (i = 0; i < s->max_steps; i++) {
        const int i_new = i - steps_out;
        s->steps[i_new < 0 ? s->max_steps + i_new : i_new] = tmp[i];
    }

    for (i = steps_out; i < s->buffered_steps; i++)
        s->steps[i]->index -= steps_out;

    ideal_fbits = s->avctx->bit_rate/(s->avctx->sample_rate/frame_size);

    for (i = 0; i < s->p.frames; i++) {
        s->avg_is_band += f[i].intensity_stereo;
        s->lambda *= ideal_fbits / f[i].framebits;
    }

    s->avg_is_band /= (s->p.frames + 1);

    s->cs_num = 0;
    s->steps_to_process = 0;
    s->buffered_steps -= steps_out;
    s->total_packets_out += s->p.frames;
    s->inflection_points_count = 0;
}