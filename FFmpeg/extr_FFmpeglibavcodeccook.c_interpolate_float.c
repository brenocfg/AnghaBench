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
struct TYPE_3__ {int gain_size_factor; float* gain_table; } ;
typedef  TYPE_1__ COOKContext ;

/* Variables and functions */
 float* pow2tab ; 

__attribute__((used)) static void interpolate_float(COOKContext *q, float *buffer,
                              int gain_index, int gain_index_next)
{
    int i;
    float fc1, fc2;
    fc1 = pow2tab[gain_index + 63];

    if (gain_index == gain_index_next) {             // static gain
        for (i = 0; i < q->gain_size_factor; i++)
            buffer[i] *= fc1;
    } else {                                        // smooth gain
        fc2 = q->gain_table[11 + (gain_index_next - gain_index)];
        for (i = 0; i < q->gain_size_factor; i++) {
            buffer[i] *= fc1;
            fc1       *= fc2;
        }
    }
}