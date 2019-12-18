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
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int* coeff_get_bits ; 
 int /*<<< orphan*/ ** coeff_tables ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int* zero_run_base ; 
 int* zero_run_get_bits ; 

__attribute__((used)) static inline int get_coeff(GetBitContext *gb, int token, int16_t *coeff)
{
    int bits_to_get, zero_run;

    bits_to_get = coeff_get_bits[token];
    if (bits_to_get)
        bits_to_get = get_bits(gb, bits_to_get);
    *coeff = coeff_tables[token][bits_to_get];

    zero_run = zero_run_base[token];
    if (zero_run_get_bits[token])
        zero_run += get_bits(gb, zero_run_get_bits[token]);

    return zero_run;
}