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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  raw ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_BLK2 ; 
 scalar_t__ EFUSE_CODING_SCHEME_NONE ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  REG_WRITE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bootloader_fill_random (scalar_t__*,int) ; 
 int /*<<< orphan*/  bzero (scalar_t__*,int) ; 
 scalar_t__ esp_efuse_get_coding_scheme (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_efuse_utility_apply_34_encoding (scalar_t__*,scalar_t__*,int) ; 

void esp_efuse_write_random_key(uint32_t blk_wdata0_reg)
{
    uint32_t buf[8];
    uint8_t raw[24];

    if (esp_efuse_get_coding_scheme(EFUSE_BLK2) == EFUSE_CODING_SCHEME_NONE) {
        bootloader_fill_random(buf, sizeof(buf));
    } else { // 3/4 Coding Scheme
        bootloader_fill_random(raw, sizeof(raw));
        esp_err_t r = esp_efuse_utility_apply_34_encoding(raw, buf, sizeof(raw));
        (void) r;
        assert(r == ESP_OK);
    }

    ESP_LOGV(TAG, "Writing random values to address 0x%08x", blk_wdata0_reg);
    for (int i = 0; i < 8; i++) {
        ESP_LOGV(TAG, "EFUSE_BLKx_WDATA%d_REG = 0x%08x", i, buf[i]);
        REG_WRITE(blk_wdata0_reg + 4*i, buf[i]);
    }
    bzero(buf, sizeof(buf));
    bzero(raw, sizeof(raw));
}