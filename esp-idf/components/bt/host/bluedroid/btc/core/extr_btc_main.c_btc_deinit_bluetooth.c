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
 int /*<<< orphan*/  BTC_MAIN_DEINIT_FUTURE ; 
 int /*<<< orphan*/  FUTURE_SUCCESS ; 
 int /*<<< orphan*/  bta_dm_sm_deinit () ; 
 int /*<<< orphan*/  bta_gattc_deinit () ; 
 int /*<<< orphan*/  bta_gatts_deinit () ; 
 int /*<<< orphan*/  btc_config_clean_up () ; 
 int /*<<< orphan*/  btc_gap_ble_deinit () ; 
 int /*<<< orphan*/ * btc_main_get_future_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bte_main_shutdown () ; 
 int /*<<< orphan*/  future_ready (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_alarm_deinit () ; 
 int /*<<< orphan*/  osi_alarm_delete_mux () ; 

__attribute__((used)) static void btc_deinit_bluetooth(void)
{
#if (BLE_INCLUDED == TRUE)
    btc_gap_ble_deinit();
#endif  ///BLE_INCLUDED == TRUE
    bta_dm_sm_deinit();
#if (GATTC_INCLUDED)
    bta_gattc_deinit();
#endif /* #if (GATTC_INCLUDED) */
#if (GATTS_INCLUDED)
    bta_gatts_deinit();
#endif /* #if (GATTS_INCLUDED) */
    bte_main_shutdown();
#if (SMP_INCLUDED)
    btc_config_clean_up();
#endif
    osi_alarm_deinit();
    osi_alarm_delete_mux();
    future_ready(*btc_main_get_future_p(BTC_MAIN_DEINIT_FUTURE), FUTURE_SUCCESS);
}