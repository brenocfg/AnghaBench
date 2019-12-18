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
struct TYPE_3__ {int wifi_pd_en; int dig_dbias_wak; int /*<<< orphan*/  rtc_dbias_slp; int /*<<< orphan*/  rtc_dbias_wak; int /*<<< orphan*/  dig_dbias_slp; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ rtc_sleep_config_t ;
typedef  int /*<<< orphan*/  pm_sw_reject_t ;
typedef  int pm_sleep_mode_t ;

/* Variables and functions */
#define  PM_LIGHT_SLEEP 128 
 int /*<<< orphan*/  PM_SW_NOREJECT ; 
 int /*<<< orphan*/  PM_SW_REJECT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ pm_check_mac_idle () ; 
 int /*<<< orphan*/  pm_mac_deinit () ; 
 int /*<<< orphan*/  pm_mac_init () ; 
 int /*<<< orphan*/  rtc_sleep_init (TYPE_1__) ; 

pm_sw_reject_t pm_set_sleep_mode(pm_sleep_mode_t sleep_mode, void(*pmac_save_params)(void))
{
    (void) pmac_save_params; /* unused */

    pm_mac_deinit();
    if (pm_check_mac_idle()) {
        pm_mac_init();
        return PM_SW_REJECT;
    }

    rtc_sleep_config_t cfg = { 0 };

    switch (sleep_mode) {
        case PM_LIGHT_SLEEP:
            cfg.wifi_pd_en = 1;
            cfg.dig_dbias_wak = 4;
            cfg.dig_dbias_slp = 0;
            cfg.rtc_dbias_wak = 0;
            cfg.rtc_dbias_slp = 0;
            rtc_sleep_init(cfg);
            break;

        default:
            assert(0 && "unsupported sleep mode");
    }
    return PM_SW_NOREJECT;
}