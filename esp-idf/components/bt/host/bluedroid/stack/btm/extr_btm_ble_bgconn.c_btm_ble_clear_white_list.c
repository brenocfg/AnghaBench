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
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  background_connections_clear () ; 
 int /*<<< orphan*/  btsnd_hcic_ble_clear_white_list () ; 

void btm_ble_clear_white_list (void)
{
    BTM_TRACE_EVENT ("btm_ble_clear_white_list");
    btsnd_hcic_ble_clear_white_list();
    background_connections_clear();
}