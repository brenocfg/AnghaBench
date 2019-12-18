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
typedef  size_t btc_pid_t ;

/* Variables and functions */
 size_t BTC_PID_NUM ; 
 void** btc_profile_cb_tab ; 

void *btc_profile_cb_get(btc_pid_t profile_id)
{
    if (profile_id < 0 || profile_id >= BTC_PID_NUM) {
        return NULL;
    }

    return btc_profile_cb_tab[profile_id];
}