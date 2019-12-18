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
 int INT_MAX ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_run_8bit(GetBitContext *gb, int *color)
{
    int len;
    int has_run = get_bits1(gb);
    *color = get_bits(gb, 2 + 6*get_bits1(gb));
    if (has_run) {
        if (get_bits1(gb)) {
            len = get_bits(gb, 7);
            if (len == 0)
                len = INT_MAX;
            else
                len += 9;
        } else
            len = get_bits(gb, 3) + 2;
    } else
        len = 1;
    return len;
}