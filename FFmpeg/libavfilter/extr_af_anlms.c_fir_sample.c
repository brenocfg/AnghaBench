#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int order; int /*<<< orphan*/  kernel_size; TYPE_1__* fdsp; } ;
struct TYPE_4__ {float (* scalarproduct_float ) (float*,float*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ AudioNLMSContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (float*,float*,int const) ; 
 float stub1 (float*,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float fir_sample(AudioNLMSContext *s, float sample, float *delay,
                        float *coeffs, float *tmp, int *offset)
{
    const int order = s->order;
    float output;

    delay[*offset] = sample;

    memcpy(tmp, coeffs + order - *offset, order * sizeof(float));

    output = s->fdsp->scalarproduct_float(delay, tmp, s->kernel_size);

    if (--(*offset) < 0)
        *offset = order - 1;

    return output;
}