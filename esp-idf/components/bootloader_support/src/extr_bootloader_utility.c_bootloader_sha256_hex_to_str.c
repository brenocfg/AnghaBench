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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 

esp_err_t bootloader_sha256_hex_to_str(char *out_str, const uint8_t *in_array_hex, size_t len)
{
    if (out_str == NULL || in_array_hex == NULL || len == 0) {
        return ESP_ERR_INVALID_ARG;
    }
    for (int i = 0; i < len; i++) {
        for (int shift = 0; shift < 2; shift++) {
            uint8_t nibble = (in_array_hex[i] >> (shift ? 0 : 4)) & 0x0F;
            if (nibble < 10) {
                out_str[i * 2 + shift] = '0' + nibble;
            } else {
                out_str[i * 2 + shift] = 'a' + nibble - 10;
            }
        }
    }
    return ESP_OK;
}