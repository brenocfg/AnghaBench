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
struct TYPE_3__ {int step; int /*<<< orphan*/  predictor; } ;
typedef  TYPE_1__ ADPCMChannelStatus ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int16_t adpcm_sbpro_expand_nibble(ADPCMChannelStatus *c, int8_t nibble, int size, int shift)
{
    int sign, delta, diff;

    sign = nibble & (1<<(size-1));
    delta = nibble & ((1<<(size-1))-1);
    diff = delta << (7 + c->step + shift);

    /* clamp result */
    c->predictor = av_clip(c->predictor + (sign ? -diff : diff), -16384,16256);

    /* calculate new step */
    if (delta >= (2*size - 3) && c->step < 3)
        c->step++;
    else if (delta == 0 && c->step > 0)
        c->step--;

    return (int16_t) c->predictor;
}