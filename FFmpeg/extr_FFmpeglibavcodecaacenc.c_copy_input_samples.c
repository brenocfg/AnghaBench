#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_6__ {size_t* reorder_map; int channels; int /*<<< orphan*/ ** planar_samples; } ;
struct TYPE_5__ {int nb_samples; int /*<<< orphan*/ ** extended_data; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AACEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void copy_input_samples(AACEncContext *s, const AVFrame *frame)
{
    int ch;
    int end = 2048 + (frame ? frame->nb_samples : 0);
    const uint8_t *channel_map = s->reorder_map;

    /* copy and remap input samples */
    for (ch = 0; ch < s->channels; ch++) {
        /* copy last 1024 samples of previous frame to the start of the current frame */
        memcpy(&s->planar_samples[ch][1024], &s->planar_samples[ch][2048], 1024 * sizeof(s->planar_samples[0][0]));

        /* copy new samples and zero any remaining samples */
        if (frame) {
            memcpy(&s->planar_samples[ch][2048],
                   frame->extended_data[channel_map[ch]],
                   frame->nb_samples * sizeof(s->planar_samples[0][0]));
        }
        memset(&s->planar_samples[ch][end], 0,
               (3072 - end) * sizeof(s->planar_samples[0][0]));
    }
}