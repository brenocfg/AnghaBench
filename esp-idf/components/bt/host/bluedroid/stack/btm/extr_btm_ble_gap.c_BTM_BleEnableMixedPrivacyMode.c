#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mixed_mode; } ;
struct TYPE_4__ {TYPE_1__ ble_ctr_cb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_2__ btm_cb ; 

void BTM_BleEnableMixedPrivacyMode(BOOLEAN mixed_on)
{

#if BLE_PRIVACY_SPT == TRUE
    btm_cb.ble_ctr_cb.mixed_mode = mixed_on;

    /* TODO: send VSC to enabled mixed mode */
#endif
}