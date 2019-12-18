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
typedef  int int8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {size_t step_index; int predictor; } ;
typedef  TYPE_1__ ADPCMChannelStatus ;

/* Variables and functions */
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int av_clip_int16 (int) ; 
 int* ff_adpcm_index_table ; 
 int* ff_adpcm_step_table ; 

__attribute__((used)) static inline int16_t adpcm_ima_expand_nibble(ADPCMChannelStatus *c, int8_t nibble, int shift)
{
    int step_index;
    int predictor;
    int sign, delta, diff, step;

    step = ff_adpcm_step_table[c->step_index];
    step_index = c->step_index + ff_adpcm_index_table[(unsigned)nibble];
    step_index = av_clip(step_index, 0, 88);

    sign = nibble & 8;
    delta = nibble & 7;
    /* perform direct multiplication instead of series of jumps proposed by
     * the reference ADPCM implementation since modern CPUs can do the mults
     * quickly enough */
    diff = ((2 * delta + 1) * step) >> shift;
    predictor = c->predictor;
    if (sign) predictor -= diff;
    else predictor += diff;

    c->predictor = av_clip_int16(predictor);
    c->step_index = step_index;

    return (int16_t)c->predictor;
}