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
typedef  int /*<<< orphan*/  RangeCoder ;
typedef  int /*<<< orphan*/  Model ;

/* Variables and functions */
 int rac_get_bit (int /*<<< orphan*/ *) ; 
 int rac_get_bits (int /*<<< orphan*/ *,int) ; 
 int rac_get_model_sym (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_coeff(RangeCoder *c, Model *m)
{
    int val, sign;

    val = rac_get_model_sym(c, m);
    if (val) {
        sign = rac_get_bit(c);
        if (val > 1) {
            val--;
            val = (1 << val) + rac_get_bits(c, val);
        }
        if (!sign)
            val = -val;
    }

    return val;
}