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

int ff_acelp_decode_5_6_bit_to_2nd_delay3(
        int ac_index,
        int pitch_delay_min)
{
        return 3 * pitch_delay_min + ac_index - 2;
}