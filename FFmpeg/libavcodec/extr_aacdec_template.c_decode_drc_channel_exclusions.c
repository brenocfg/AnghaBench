#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* exclude_mask; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ DynamicRangeControl ;

/* Variables and functions */
 int MAX_CHANNELS ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_drc_channel_exclusions(DynamicRangeControl *che_drc,
                                         GetBitContext *gb)
{
    int i;
    int num_excl_chan = 0;

    do {
        for (i = 0; i < 7; i++)
            che_drc->exclude_mask[num_excl_chan++] = get_bits1(gb);
    } while (num_excl_chan < MAX_CHANNELS - 7 && get_bits1(gb));

    return num_excl_chan / 7;
}