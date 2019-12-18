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
typedef  size_t tSMP_EVENT ;

/* Variables and functions */
 size_t SMP_MAX_EVT ; 
 char** smp_event_name ; 

const char *smp_get_event_name(tSMP_EVENT event)
{
    const char *p_str = smp_event_name[SMP_MAX_EVT];

    if (event <= SMP_MAX_EVT) {
        p_str = smp_event_name[event - 1];
    }
    return p_str;
}