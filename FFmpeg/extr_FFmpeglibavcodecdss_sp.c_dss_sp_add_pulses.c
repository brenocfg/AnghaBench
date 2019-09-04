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
struct DssSpSubframe {size_t* pulse_pos; size_t gain; size_t* pulse_val; } ;
typedef  int int32_t ;

/* Variables and functions */
 int* dss_sp_fixed_cb_gain ; 
 int* dss_sp_pulse_val ; 

__attribute__((used)) static void dss_sp_add_pulses(int32_t *vector_buf,
                              const struct DssSpSubframe *sf)
{
    int i;

    for (i = 0; i < 7; i++)
        vector_buf[sf->pulse_pos[i]] += (dss_sp_fixed_cb_gain[sf->gain] *
                                         dss_sp_pulse_val[sf->pulse_val[i]] +
                                         0x4000) >> 15;
}