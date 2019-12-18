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
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 unsigned int av_log2 (int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static void encode_codeword(PutBitContext *pb, int val, int codebook)
{
    unsigned int rice_order, exp_order, switch_bits, first_exp, exp, zeros;

    /* number of bits to switch between rice and exp golomb */
    switch_bits = codebook & 3;
    rice_order  = codebook >> 5;
    exp_order   = (codebook >> 2) & 7;

    first_exp = ((switch_bits + 1) << rice_order);

    if (val >= first_exp) { /* exp golomb */
        val -= first_exp;
        val += (1 << exp_order);
        exp = av_log2(val);
        zeros = exp - exp_order + switch_bits + 1;
        put_bits(pb, zeros, 0);
        put_bits(pb, exp + 1, val);
    } else if (rice_order) {
        put_bits(pb, (val >> rice_order), 0);
        put_bits(pb, 1, 1);
        put_sbits(pb, rice_order, val);
    } else {
        put_bits(pb, val, 0);
        put_bits(pb, 1, 1);
    }
}