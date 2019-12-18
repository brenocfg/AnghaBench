#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  client_if; } ;
struct TYPE_5__ {TYPE_1__ int_start_if; } ;
typedef  TYPE_2__ tBTA_GATTC_DATA ;
typedef  int /*<<< orphan*/  tBTA_GATTC_CB ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_StartIf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bta_gattc_cl_get_regcb (int /*<<< orphan*/ ) ; 

void bta_gattc_start_if(tBTA_GATTC_CB *p_cb, tBTA_GATTC_DATA *p_msg)
{
    UNUSED(p_cb);

    if (bta_gattc_cl_get_regcb(p_msg->int_start_if.client_if) != NULL ) {
        GATT_StartIf(p_msg->int_start_if.client_if);
    } else {
        APPL_TRACE_ERROR("Unable to start app.: Unknown interface =%d", p_msg->int_start_if.client_if );
    }
}