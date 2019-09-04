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

int ff_acelp_decode_9bit_to_1st_delay6(int ac_index)
{
    if(ac_index < 463)
        return ac_index + 105;
    else
        return 6 * (ac_index - 368);
}