#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_GATTC_DATA ;
struct TYPE_3__ {int /*<<< orphan*/  auto_update; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ tBTA_GATTC_CLCB ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_DISC_WAITING ; 
 int /*<<< orphan*/  BTA_GATT_CANCEL ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 

void bta_gattc_restart_discover(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    UNUSED(p_data);

    p_clcb->status      = BTA_GATT_CANCEL;
    p_clcb->auto_update = BTA_GATTC_DISC_WAITING;
}