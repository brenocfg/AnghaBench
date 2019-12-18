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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int get_mask (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t fill_reg(int bit_start_in_reg, int bit_count_in_reg, uint8_t* blob, int* filled_bits_blob)
{
    uint32_t reg_to_write = 0;
    uint32_t temp_blob_32;
    int shift_bit = (*filled_bits_blob) % 8;
    if (shift_bit != 0) {
        temp_blob_32 = blob[(*filled_bits_blob) / 8] >> shift_bit;
        shift_bit = ((8 - shift_bit) < bit_count_in_reg) ? (8 - shift_bit) : bit_count_in_reg;
        reg_to_write = temp_blob_32 & get_mask(shift_bit, 0);
        (*filled_bits_blob) += shift_bit;
        bit_count_in_reg -= shift_bit;
    }

    int shift_reg = shift_bit;
    while (bit_count_in_reg > 0) {
        temp_blob_32 = blob[(*filled_bits_blob) / 8];
        shift_bit = (bit_count_in_reg > 8) ? 8 : bit_count_in_reg;
        reg_to_write |= (temp_blob_32 & get_mask(shift_bit, 0)) << shift_reg;
        (*filled_bits_blob) += shift_bit;
        bit_count_in_reg -= shift_bit;
        shift_reg += 8;
    };
    return reg_to_write << bit_start_in_reg;
}