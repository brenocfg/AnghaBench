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

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_BLK0_RDATA3_REG ; 
 int /*<<< orphan*/  EFUSE_RD_CHIP_CPU_FREQ_LOW ; 
 int /*<<< orphan*/  EFUSE_RD_CHIP_CPU_FREQ_RATED ; 
 scalar_t__ REG_GET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bootloader_clock_get_rated_freq_mhz()
{
    //Check if ESP32 is rated for a CPU frequency of 160MHz only
    if (REG_GET_BIT(EFUSE_BLK0_RDATA3_REG, EFUSE_RD_CHIP_CPU_FREQ_RATED) &&
        REG_GET_BIT(EFUSE_BLK0_RDATA3_REG, EFUSE_RD_CHIP_CPU_FREQ_LOW)) {
        return 160;
    }
    return 240;
}