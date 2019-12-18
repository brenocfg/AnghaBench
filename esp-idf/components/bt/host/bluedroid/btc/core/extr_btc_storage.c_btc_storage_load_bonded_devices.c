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
typedef  int /*<<< orphan*/  bt_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc_in_fetch_bonded_devices (int) ; 

bt_status_t btc_storage_load_bonded_devices(void)
{
    bt_status_t status;
    status = btc_in_fetch_bonded_devices(1);
    BTC_TRACE_DEBUG("Storage load rslt %d\n", status);
    return status;
}