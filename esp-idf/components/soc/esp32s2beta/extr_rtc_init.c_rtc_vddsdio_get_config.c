#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int drefh; int drefm; int drefl; int force; int enable; int tieh; } ;
typedef  TYPE_1__ rtc_vddsdio_config_t ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  EFUSE_RD_REPEAT_DATA0_REG ; 
 int /*<<< orphan*/  EFUSE_RD_REPEAT_DATA1_REG ; 
 int EFUSE_SDIO_DREFH_M ; 
 int EFUSE_SDIO_DREFH_S ; 
 int EFUSE_SDIO_DREFL_M ; 
 int EFUSE_SDIO_DREFL_S ; 
 int EFUSE_SDIO_DREFM_M ; 
 int EFUSE_SDIO_DREFM_S ; 
 int EFUSE_SDIO_FORCE ; 
 int EFUSE_SDIO_TIEH_M ; 
 int EFUSE_SDIO_TIEH_S ; 
 int EFUSE_SDIO_XPD_M ; 
 int EFUSE_SDIO_XPD_S ; 
 int /*<<< orphan*/  GPIO_STRAP_REG ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int RTC_CNTL_DREFH_SDIO_M ; 
 int RTC_CNTL_DREFH_SDIO_S ; 
 int RTC_CNTL_DREFL_SDIO_M ; 
 int RTC_CNTL_DREFL_SDIO_S ; 
 int RTC_CNTL_DREFM_SDIO_M ; 
 int RTC_CNTL_DREFM_SDIO_S ; 
 int /*<<< orphan*/  RTC_CNTL_SDIO_CONF_REG ; 
 int RTC_CNTL_SDIO_FORCE ; 
 int RTC_CNTL_SDIO_TIEH_M ; 
 int RTC_CNTL_SDIO_TIEH_S ; 
 int RTC_CNTL_XPD_SDIO_REG_M ; 
 int RTC_CNTL_XPD_SDIO_REG_S ; 
 int RTC_VDDSDIO_TIEH_1_8V ; 
 int RTC_VDDSDIO_TIEH_3_3V ; 

rtc_vddsdio_config_t rtc_vddsdio_get_config(void)
{
    rtc_vddsdio_config_t result;
    uint32_t sdio_conf_reg = REG_READ(RTC_CNTL_SDIO_CONF_REG);
    result.drefh = (sdio_conf_reg & RTC_CNTL_DREFH_SDIO_M) >> RTC_CNTL_DREFH_SDIO_S;
    result.drefm = (sdio_conf_reg & RTC_CNTL_DREFM_SDIO_M) >> RTC_CNTL_DREFM_SDIO_S;
    result.drefl = (sdio_conf_reg & RTC_CNTL_DREFL_SDIO_M) >> RTC_CNTL_DREFL_SDIO_S;
    if (sdio_conf_reg & RTC_CNTL_SDIO_FORCE) {
        // Get configuration from RTC
        result.force = 1;
        result.enable = (sdio_conf_reg & RTC_CNTL_XPD_SDIO_REG_M) >> RTC_CNTL_XPD_SDIO_REG_S;
        result.tieh = (sdio_conf_reg & RTC_CNTL_SDIO_TIEH_M) >> RTC_CNTL_SDIO_TIEH_S;
        return result;
    } else {
        result.force = 0;
    }
    uint32_t efuse_reg = REG_READ(EFUSE_RD_REPEAT_DATA1_REG);
    if (efuse_reg & EFUSE_SDIO_FORCE) {
        // Get configuration from EFUSE
        result.enable = (efuse_reg & EFUSE_SDIO_XPD_M) >> EFUSE_SDIO_XPD_S;
        result.tieh = (efuse_reg & EFUSE_SDIO_TIEH_M) >> EFUSE_SDIO_TIEH_S;

        result.drefm = (efuse_reg & EFUSE_SDIO_DREFM_M) >> EFUSE_SDIO_DREFM_S;
        result.drefl = (efuse_reg & EFUSE_SDIO_DREFL_M) >> EFUSE_SDIO_DREFL_S;

        efuse_reg = REG_READ(EFUSE_RD_REPEAT_DATA0_REG);
        result.drefh = (efuse_reg & EFUSE_SDIO_DREFH_M) >> EFUSE_SDIO_DREFH_S;

        return result;
    }

    // Otherwise, VDD_SDIO is controlled by bootstrapping pin
    uint32_t strap_reg = REG_READ(GPIO_STRAP_REG);
    result.tieh = (strap_reg & BIT(5)) ? RTC_VDDSDIO_TIEH_1_8V : RTC_VDDSDIO_TIEH_3_3V;
    result.enable = 1;
    return result;
}