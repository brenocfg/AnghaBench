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
 int APR_NUMSIG ; 
 char const** signal_description ; 

const char *apr_signal_description_get(int signum)
{
    return
        (signum >= 0 && signum < APR_NUMSIG)
        ? signal_description[signum]
        : "unknown signal (number)";
}