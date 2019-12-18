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
 scalar_t__ get_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_group3_syncmarker(GetBitContext *gb, int srcsize)
{
    unsigned int state = -1;
    srcsize -= get_bits_count(gb);
    while (srcsize-- > 0) {
        state += state + get_bits1(gb);
        if ((state & 0xFFF) == 1)
            return 0;
    }
    return -1;
}