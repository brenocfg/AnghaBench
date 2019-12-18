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
typedef  size_t tSMP_STATE ;

/* Variables and functions */
 size_t SMP_STATE_MAX ; 
 char** smp_state_name ; 

const char *smp_get_state_name(tSMP_STATE state)
{
    const char *p_str = smp_state_name[SMP_STATE_MAX];

    if (state < SMP_STATE_MAX) {
        p_str = smp_state_name[state];
    }
    return p_str;
}