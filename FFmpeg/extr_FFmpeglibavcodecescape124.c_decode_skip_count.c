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
 int get_bits (int /*<<< orphan*/ *,int) ; 
 unsigned int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned decode_skip_count(GetBitContext* gb)
{
    unsigned value;
    // This function reads a maximum of 23 bits,
    // which is within the padding space
    if (get_bits_left(gb) < 1)
        return -1;
    value = get_bits1(gb);
    if (!value)
        return value;

    value += get_bits(gb, 3);
    if (value != (1 + ((1 << 3) - 1)))
        return value;

    value += get_bits(gb, 7);
    if (value != (1 + ((1 << 3) - 1)) + ((1 << 7) - 1))
        return value;

    return value + get_bits(gb, 12);
}