#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int channels; size_t num_blocks; size_t* channel_map; int /*<<< orphan*/ ** planar_samples; } ;
typedef  int /*<<< orphan*/  SampleType ;
typedef  TYPE_1__ AC3EncodeContext ;

/* Variables and functions */
 size_t AC3_BLOCK_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void copy_input_samples(AC3EncodeContext *s, SampleType **samples)
{
    int ch;

    /* copy and remap input samples */
    for (ch = 0; ch < s->channels; ch++) {
        /* copy last 256 samples of previous frame to the start of the current frame */
        memcpy(&s->planar_samples[ch][0], &s->planar_samples[ch][AC3_BLOCK_SIZE * s->num_blocks],
               AC3_BLOCK_SIZE * sizeof(s->planar_samples[0][0]));

        /* copy new samples for current frame */
        memcpy(&s->planar_samples[ch][AC3_BLOCK_SIZE],
               samples[s->channel_map[ch]],
               AC3_BLOCK_SIZE * s->num_blocks * sizeof(s->planar_samples[0][0]));
    }
}