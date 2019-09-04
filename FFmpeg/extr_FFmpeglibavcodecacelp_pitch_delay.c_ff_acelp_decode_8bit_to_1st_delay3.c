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

int ff_acelp_decode_8bit_to_1st_delay3(int ac_index)
{
    ac_index += 58;
    if(ac_index > 254)
        ac_index = 3 * ac_index - 510;
    return ac_index;
}