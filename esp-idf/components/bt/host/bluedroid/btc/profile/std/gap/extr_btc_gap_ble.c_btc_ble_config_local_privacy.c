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
typedef  int /*<<< orphan*/  tBTA_SET_LOCAL_PRIVACY_CBACK ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmBleConfigLocalPrivacy (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btc_ble_config_local_privacy(bool privacy_enable, tBTA_SET_LOCAL_PRIVACY_CBACK *set_local_privacy_cback)
{
    BTA_DmBleConfigLocalPrivacy(privacy_enable, set_local_privacy_cback);
}