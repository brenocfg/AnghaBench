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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_efuse_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int esp_efuse_utility_read_reg (int /*<<< orphan*/ ,unsigned int) ; 
 int get_mask (int,int /*<<< orphan*/ ) ; 

esp_err_t esp_efuse_utility_fill_buff(unsigned int num_reg, esp_efuse_block_t efuse_block, int bit_start, int bit_count, void* arr_out, int* bits_counter)
{
    uint8_t* blob = (uint8_t *) arr_out;
    uint32_t reg = esp_efuse_utility_read_reg(efuse_block, num_reg);
    uint64_t reg_of_aligned_bits = (reg >> bit_start) & get_mask(bit_count, 0);

    int shift_bit = (*bits_counter) % 8;
    if (shift_bit != 0) {
        blob[(*bits_counter) / 8] |= (uint8_t)(reg_of_aligned_bits << shift_bit);
        shift_bit = ((8 - shift_bit) < bit_count) ? (8 - shift_bit) : bit_count;
        (*bits_counter) += shift_bit;
        bit_count -= shift_bit;
    }

    int sum_shift = 0;
    while (bit_count > 0) {
        sum_shift += shift_bit;
        blob[(*bits_counter) / 8] |= (uint8_t)(reg_of_aligned_bits >> sum_shift);
        shift_bit = (bit_count > 8) ? 8 : bit_count;
        (*bits_counter) += shift_bit;
        bit_count -= shift_bit;
    };
    return ESP_OK;
}