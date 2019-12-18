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
struct TYPE_3__ {int /*<<< orphan*/  no_disc_if_pair_fail; } ;
struct TYPE_4__ {TYPE_1__ devcb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ btm_cb ; 

void btm_ble_set_no_disc_if_pair_fail(BOOLEAN disable_disc )
{
    BTM_TRACE_DEBUG ("btm_ble_set_disc_enable_if_pair_fail disable_disc=%d", disable_disc);
    btm_cb.devcb.no_disc_if_pair_fail = disable_disc;
}