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
typedef  int int16_t ;
struct TYPE_3__ {size_t step_index; int predictor; } ;
typedef  TYPE_1__ ADPCMChannelStatus ;

/* Variables and functions */
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int av_clip_intp2 (int,int) ; 
 int* ff_adpcm_index_table ; 
 int* ff_adpcm_oki_step_table ; 

__attribute__((used)) static inline int16_t adpcm_ima_oki_expand_nibble(ADPCMChannelStatus *c, int nibble)
{
    int step_index, predictor, sign, delta, diff, step;

    step = ff_adpcm_oki_step_table[c->step_index];
    step_index = c->step_index + ff_adpcm_index_table[(unsigned)nibble];
    step_index = av_clip(step_index, 0, 48);

    sign = nibble & 8;
    delta = nibble & 7;
    diff = ((2 * delta + 1) * step) >> 3;
    predictor = c->predictor;
    if (sign) predictor -= diff;
    else predictor += diff;

    c->predictor = av_clip_intp2(predictor, 11);
    c->step_index = step_index;

    return c->predictor * 16;
}