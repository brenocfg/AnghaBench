#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int enable; scalar_t__ tieh; int drefh; int drefm; int drefl; int force; } ;
typedef  TYPE_1__ rtc_vddsdio_config_t ;

/* Variables and functions */
 scalar_t__ RTC_VDDSDIO_TIEH_1_8V ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 
 TYPE_1__ rtc_vddsdio_get_config () ; 
 int /*<<< orphan*/  rtc_vddsdio_set_config (TYPE_1__) ; 

void bootloader_common_vddsdio_configure(void)
{
#if CONFIG_BOOTLOADER_VDDSDIO_BOOST_1_9V
    rtc_vddsdio_config_t cfg = rtc_vddsdio_get_config();
    if (cfg.enable == 1 && cfg.tieh == RTC_VDDSDIO_TIEH_1_8V) {    // VDDSDIO regulator is enabled @ 1.8V
        cfg.drefh = 3;
        cfg.drefm = 3;
        cfg.drefl = 3;
        cfg.force = 1;
        rtc_vddsdio_set_config(cfg);
        ets_delay_us(10); // wait for regulator to become stable
    }
#endif // CONFIG_BOOTLOADER_VDDSDIO_BOOST
}