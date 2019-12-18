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
typedef  int /*<<< orphan*/  tBTM_DEV_STATUS_CB ;
struct TYPE_3__ {int /*<<< orphan*/ * p_dev_status_cb; } ;
struct TYPE_4__ {TYPE_1__ devcb; } ;

/* Variables and functions */
 TYPE_2__ btm_cb ; 

tBTM_DEV_STATUS_CB *BTM_RegisterForDeviceStatusNotif (tBTM_DEV_STATUS_CB *p_cb)
{
    tBTM_DEV_STATUS_CB *p_prev = btm_cb.devcb.p_dev_status_cb;

    btm_cb.devcb.p_dev_status_cb = p_cb;
    return (p_prev);
}