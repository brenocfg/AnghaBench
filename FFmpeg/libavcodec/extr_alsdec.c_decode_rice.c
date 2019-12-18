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
typedef  unsigned int int32_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_bits_left (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_long (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int get_unary (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int32_t decode_rice(GetBitContext *gb, unsigned int k)
{
    int max = get_bits_left(gb) - k;
    unsigned q = get_unary(gb, 0, max);
    int r   = k ? get_bits1(gb) : !(q & 1);

    if (k > 1) {
        q <<= (k - 1);
        q  += get_bits_long(gb, k - 1);
    } else if (!k) {
        q >>= 1;
    }
    return r ? q : ~q;
}