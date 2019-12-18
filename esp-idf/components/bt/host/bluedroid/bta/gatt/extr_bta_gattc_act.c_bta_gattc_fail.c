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
struct TYPE_3__ {scalar_t__ status; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ tBTA_GATTC_CLCB ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ BTA_GATT_OK ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 

void bta_gattc_fail(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    UNUSED(p_data);

    if (p_clcb->status == BTA_GATT_OK) {
        APPL_TRACE_ERROR("operation not supported at current state [%d]", p_clcb->state);
    }
}