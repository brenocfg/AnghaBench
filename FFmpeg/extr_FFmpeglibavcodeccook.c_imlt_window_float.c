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
struct TYPE_5__ {int* previous; } ;
typedef  TYPE_1__ cook_gains ;
struct TYPE_6__ {int samples_per_channel; float* mlt_window; } ;
typedef  TYPE_2__ COOKContext ;

/* Variables and functions */
 float* pow2tab ; 

__attribute__((used)) static void imlt_window_float(COOKContext *q, float *inbuffer,
                              cook_gains *gains_ptr, float *previous_buffer)
{
    const float fc = pow2tab[gains_ptr->previous[0] + 63];
    int i;
    /* The weird thing here, is that the two halves of the time domain
     * buffer are swapped. Also, the newest data, that we save away for
     * next frame, has the wrong sign. Hence the subtraction below.
     * Almost sounds like a complex conjugate/reverse data/FFT effect.
     */

    /* Apply window and overlap */
    for (i = 0; i < q->samples_per_channel; i++)
        inbuffer[i] = inbuffer[i] * fc * q->mlt_window[i] -
                      previous_buffer[i] * q->mlt_window[q->samples_per_channel - 1 - i];
}