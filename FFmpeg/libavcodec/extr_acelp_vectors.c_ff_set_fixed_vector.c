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
struct TYPE_3__ {int n; int* x; int no_repeat_mask; float* y; scalar_t__ pitch_lag; float pitch_fac; } ;
typedef  TYPE_1__ AMRFixed ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 

void ff_set_fixed_vector(float *out, const AMRFixed *in, float scale, int size)
{
    int i;

    for (i=0; i < in->n; i++) {
        int x   = in->x[i], repeats = !((in->no_repeat_mask >> i) & 1);
        float y = in->y[i] * scale;

        if (in->pitch_lag > 0)
            av_assert0(x < size);
            do {
                out[x] += y;
                y *= in->pitch_fac;
                x += in->pitch_lag;
            } while (x < size && repeats);
    }
}