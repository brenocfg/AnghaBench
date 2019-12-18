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
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_skip_count(GetBitContext* gb)
{
    int value;

    if (get_bits_left(gb) < 1+3)
        return -1;

    value = get_bits1(gb);
    if (value)
        return 0;

    value = get_bits(gb, 3);
    if (value)
        return value;

    value = get_bits(gb, 8);
    if (value)
        return value + 7;

    value = get_bits(gb, 15);
    if (value)
        return value + 262;

    return -1;
}