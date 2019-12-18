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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EFUSE_CHIP_VER_PKG ; 
 int /*<<< orphan*/  esp_efuse_read_field_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

uint32_t esp_efuse_get_pkg_ver(void)
{
    uint32_t pkg_ver = 0;
    esp_efuse_read_field_blob(ESP_EFUSE_CHIP_VER_PKG, &pkg_ver, 3);
    return pkg_ver;
}