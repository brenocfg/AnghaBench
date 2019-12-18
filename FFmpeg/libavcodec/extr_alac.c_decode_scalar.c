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
 unsigned int get_bits_long (int /*<<< orphan*/ *,int) ; 
 unsigned int get_unary_0_9 (int /*<<< orphan*/ *) ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline unsigned int decode_scalar(GetBitContext *gb, int k, int bps)
{
    unsigned int x = get_unary_0_9(gb);

    if (x > 8) { /* RICE THRESHOLD */
        /* use alternative encoding */
        x = get_bits_long(gb, bps);
    } else if (k != 1) {
        int extrabits = show_bits(gb, k);

        /* multiply x by 2^k - 1, as part of their strange algorithm */
        x = (x << k) - x;

        if (extrabits > 1) {
            x += extrabits - 1;
            skip_bits(gb, k);
        } else
            skip_bits(gb, k - 1);
    }
    return x;
}