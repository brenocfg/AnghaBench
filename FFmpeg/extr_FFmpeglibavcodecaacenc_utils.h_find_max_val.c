#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 float FFMAX (float,float const) ; 

__attribute__((used)) static inline float find_max_val(int group_len, int swb_size, const float *scaled)
{
    float maxval = 0.0f;
    int w2, i;
    for (w2 = 0; w2 < group_len; w2++) {
        for (i = 0; i < swb_size; i++) {
            maxval = FFMAX(maxval, scaled[w2*128+i]);
        }
    }
    return maxval;
}