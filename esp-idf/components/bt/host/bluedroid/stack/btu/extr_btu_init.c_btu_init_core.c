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
 int /*<<< orphan*/  SMP_Init () ; 
 int /*<<< orphan*/  btm_ble_init () ; 
 int /*<<< orphan*/  btm_init () ; 
 int /*<<< orphan*/  gatt_init () ; 
 int /*<<< orphan*/  l2c_init () ; 
 int /*<<< orphan*/  sdp_init () ; 

void btu_init_core(void)
{
    /* Initialize the mandatory core stack components */
    btm_init();

    l2c_init();

#if (defined(SDP_INCLUDED) && SDP_INCLUDED == TRUE)
    sdp_init();
#endif

#if BLE_INCLUDED == TRUE
#if (defined(GATT_INCLUDED) && GATT_INCLUDED == true)
    gatt_init();
#endif
#if (defined(SMP_INCLUDED) && SMP_INCLUDED == TRUE)
    SMP_Init();
#endif
    btm_ble_init();
#endif
}