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
 unsigned int get_bits_long (int /*<<< orphan*/ *,int) ; 

unsigned int ff_wma_get_large_val(GetBitContext *gb)
{
    /** consumes up to 34 bits */
    int n_bits = 8;
    /** decode length */
    if (get_bits1(gb)) {
        n_bits += 8;
        if (get_bits1(gb)) {
            n_bits += 8;
            if (get_bits1(gb))
                n_bits += 7;
        }
    }
    return get_bits_long(gb, n_bits);
}