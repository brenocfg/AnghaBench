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
 int /*<<< orphan*/  btc_config_init () ; 
 int /*<<< orphan*/  btc_dm_load_ble_local_keys () ; 
 int /*<<< orphan*/  btc_init_callback ; 
 int /*<<< orphan*/  bte_main_boot_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_alarm_create_mux () ; 
 int /*<<< orphan*/  osi_alarm_init () ; 

__attribute__((used)) static void btc_init_bluetooth(void)
{
    osi_alarm_create_mux();
    osi_alarm_init();
    bte_main_boot_entry(btc_init_callback);
#if (SMP_INCLUDED)
    btc_config_init();

#if (BLE_INCLUDED == TRUE)
    //load the ble local key which has been stored in the flash
    btc_dm_load_ble_local_keys();
#endif  ///BLE_INCLUDED == TRUE
#endif /* #if (SMP_INCLUDED) */
}