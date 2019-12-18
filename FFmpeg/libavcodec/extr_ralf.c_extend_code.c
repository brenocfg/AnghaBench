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
 unsigned int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_ue_golomb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int extend_code(GetBitContext *gb, int val, int range, int bits)
{
    if (val == 0) {
        val = -range - get_ue_golomb(gb);
    } else if (val == range * 2) {
        val =  range + get_ue_golomb(gb);
    } else {
        val -= range;
    }
    if (bits)
        val = ((unsigned)val << bits) | get_bits(gb, bits);
    return val;
}