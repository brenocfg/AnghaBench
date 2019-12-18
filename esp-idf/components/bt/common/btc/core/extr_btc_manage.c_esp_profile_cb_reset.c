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
 int BTC_PID_NUM ; 
 int /*<<< orphan*/ ** btc_profile_cb_tab ; 

void esp_profile_cb_reset(void)
{
    int i;

    for (i = 0; i < BTC_PID_NUM; i++) {
        btc_profile_cb_tab[i] = NULL;
    }
}