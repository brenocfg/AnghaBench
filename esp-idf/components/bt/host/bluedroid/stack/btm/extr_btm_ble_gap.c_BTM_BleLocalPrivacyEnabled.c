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
struct TYPE_3__ {scalar_t__ privacy_mode; } ;
struct TYPE_4__ {TYPE_1__ ble_ctr_cb; } ;
typedef  int BOOLEAN ;

/* Variables and functions */
 scalar_t__ BTM_PRIVACY_NONE ; 
 TYPE_2__ btm_cb ; 

BOOLEAN BTM_BleLocalPrivacyEnabled(void)
{
#if BLE_PRIVACY_SPT == TRUE
    return (btm_cb.ble_ctr_cb.privacy_mode != BTM_PRIVACY_NONE);
#else
    return false;
#endif
}