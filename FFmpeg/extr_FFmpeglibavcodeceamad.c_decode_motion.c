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
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_motion(GetBitContext *gb)
{
    int value = 0;
    if (get_bits1(gb)) {
        if (get_bits1(gb))
            value = -17;
        value += get_bits(gb, 4) + 1;
    }
    return value;
}