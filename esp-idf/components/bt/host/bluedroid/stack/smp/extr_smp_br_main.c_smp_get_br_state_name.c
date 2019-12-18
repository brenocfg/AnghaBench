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
typedef  size_t tSMP_BR_STATE ;

/* Variables and functions */
 size_t SMP_BR_STATE_MAX ; 
 char** smp_br_state_name ; 

const char *smp_get_br_state_name(tSMP_BR_STATE br_state)
{
    const char *p_str = smp_br_state_name[SMP_BR_STATE_MAX];

    if (br_state < SMP_BR_STATE_MAX) {
        p_str = smp_br_state_name[br_state];
    }

    return p_str;
}