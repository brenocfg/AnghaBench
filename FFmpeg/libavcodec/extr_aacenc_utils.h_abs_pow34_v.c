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
 float fabsf (float const) ; 
 float sqrtf (float) ; 

__attribute__((used)) static inline void abs_pow34_v(float *out, const float *in, const int size)
{
    int i;
    for (i = 0; i < size; i++) {
        float a = fabsf(in[i]);
        out[i] = sqrtf(a * sqrtf(a));
    }
}