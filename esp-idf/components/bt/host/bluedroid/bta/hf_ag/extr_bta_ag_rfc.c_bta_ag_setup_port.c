#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_AG_SCB ;
typedef  size_t UINT16 ;
struct TYPE_2__ {scalar_t__ parse_mode; } ;

/* Variables and functions */
 scalar_t__ BTA_AG_PASS_THROUGH ; 
 int /*<<< orphan*/  BTA_AG_PORT_EV_MASK ; 
 int /*<<< orphan*/  PORT_SetDataCallback (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_SetEventCallback (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_SetEventMask (size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__ bta_ag_cb ; 
 int /*<<< orphan*/ * bta_ag_data_cback_tbl ; 
 int /*<<< orphan*/ * bta_ag_port_cback_tbl ; 
 size_t bta_ag_scb_to_idx (int /*<<< orphan*/ *) ; 

void bta_ag_setup_port(tBTA_AG_SCB *p_scb, UINT16 handle)
{
    UINT16 i = bta_ag_scb_to_idx(p_scb) - 1;

    /* set up data callback if using pass through mode */
    if (bta_ag_cb.parse_mode == BTA_AG_PASS_THROUGH) {
        PORT_SetDataCallback(handle, bta_ag_data_cback_tbl[i]);
    }
    PORT_SetEventMask(handle, BTA_AG_PORT_EV_MASK);
    PORT_SetEventCallback(handle, bta_ag_port_cback_tbl[i]);
}