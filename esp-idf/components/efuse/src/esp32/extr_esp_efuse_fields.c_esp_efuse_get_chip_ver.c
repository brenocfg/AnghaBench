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
 int /*<<< orphan*/  APB_CTRL_DATE_REG ; 
 int /*<<< orphan*/  ESP_EFUSE_CHIP_VER_REV1 ; 
 int /*<<< orphan*/  ESP_EFUSE_CHIP_VER_REV2 ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_efuse_read_field_blob (int /*<<< orphan*/ ,int*,int) ; 

uint8_t esp_efuse_get_chip_ver(void)
{
    uint8_t eco_bit0, eco_bit1, eco_bit2;
    esp_efuse_read_field_blob(ESP_EFUSE_CHIP_VER_REV1, &eco_bit0, 1);
    esp_efuse_read_field_blob(ESP_EFUSE_CHIP_VER_REV2, &eco_bit1, 1);
    eco_bit2 = (REG_READ(APB_CTRL_DATE_REG) & 0x80000000) >> 31;
    uint32_t combine_value = (eco_bit2 << 2) | (eco_bit1 << 1) | eco_bit0;
    uint8_t chip_ver = 0;
    switch (combine_value) {
    case 0:
        chip_ver = 0;
        break;
    case 1:
        chip_ver = 1;
        break;
    case 3:
        chip_ver = 2;
        break;
    case 7:
        chip_ver = 3;
        break;
    default:
        chip_ver = 0;
        break;
    }
    return chip_ver;
}