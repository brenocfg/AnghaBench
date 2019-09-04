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
 float M_PI ; 
 float cosf (float) ; 

__attribute__((used)) static inline void get_lfe(int output_lfe, int n, float lowcut, float highcut,
                           float *lfe_mag, float *mag_total, int lfe_mode)
{
    if (output_lfe && n < highcut) {
        *lfe_mag    = n < lowcut ? 1.f : .5f*(1.f+cosf(M_PI*(lowcut-n)/(lowcut-highcut)));
        *lfe_mag   *= *mag_total;
        if (lfe_mode)
            *mag_total -= *lfe_mag;
    } else {
        *lfe_mag = 0.f;
    }
}