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
typedef  int int16_t ;

/* Variables and functions */
 int SUBFRAME_SIZE ; 
 int /*<<< orphan*/  ff_celp_convolve_circ (int*,int const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * phase_filter ; 

__attribute__((used)) static void g729d_get_new_exc(
        int16_t* out,
        const int16_t* in,
        const int16_t* fc_cur,
        int dstate,
        int gain_code,
        int subframe_size)
{
    int i;
    int16_t fc_new[SUBFRAME_SIZE];

    ff_celp_convolve_circ(fc_new, fc_cur, phase_filter[dstate], subframe_size);

    for (i = 0; i < subframe_size; i++) {
        out[i]  = in[i];
        out[i] -= (gain_code * fc_cur[i] + 0x2000) >> 14;
        out[i] += (gain_code * fc_new[i] + 0x2000) >> 14;
    }
}