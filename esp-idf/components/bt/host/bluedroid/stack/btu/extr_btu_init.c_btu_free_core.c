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
 int /*<<< orphan*/  SMP_Free () ; 
 int /*<<< orphan*/  btm_ble_free () ; 
 int /*<<< orphan*/  btm_free () ; 
 int /*<<< orphan*/  gatt_free () ; 
 int /*<<< orphan*/  l2c_free () ; 
 int /*<<< orphan*/  sdp_deinit () ; 

void btu_free_core(void)
{
    // Free the mandatory core stack components
    l2c_free();

#if (defined(SDP_INCLUDED) && SDP_INCLUDED == TRUE)
    sdp_deinit();
#endif

#if BLE_INCLUDED == TRUE
#if (defined(GATT_INCLUDED) && GATT_INCLUDED == true)
    gatt_free();
#endif
#if SMP_INCLUDED == TRUE
    SMP_Free();
#endif
    btm_ble_free();
#endif
    btm_free();
}