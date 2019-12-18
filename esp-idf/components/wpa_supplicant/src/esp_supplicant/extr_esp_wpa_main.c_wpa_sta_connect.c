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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_ASSERT (int) ; 
 int wpa_config_bss (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_config_profile () ; 

void  wpa_sta_connect(uint8_t *bssid)
{
    int ret = 0;
    wpa_config_profile();
    ret = wpa_config_bss(bssid);
    WPA_ASSERT(ret == 0);
}