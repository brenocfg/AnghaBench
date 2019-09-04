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
 int get_sbits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void read_uncoded_coeff(GetBitContext *gb, int *dst, unsigned int elements,
                               int coeff_bits, int is_signed, int offset)
{
    int i;

    for (i = 0; i < elements; i++) {
        dst[i] = (is_signed ? get_sbits(gb, coeff_bits) : get_bits(gb, coeff_bits)) + offset;
    }
}