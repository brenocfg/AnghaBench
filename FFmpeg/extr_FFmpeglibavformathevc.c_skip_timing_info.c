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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void skip_timing_info(GetBitContext *gb)
{
    skip_bits_long(gb, 32); // num_units_in_tick
    skip_bits_long(gb, 32); // time_scale

    if (get_bits1(gb))          // poc_proportional_to_timing_flag
        get_ue_golomb_long(gb); // num_ticks_poc_diff_one_minus1
}