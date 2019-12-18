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
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;
struct TYPE_2__ {scalar_t__ parse_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ BTA_AG_PASS_THROUGH ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_1__ bta_ag_cb ; 
 int /*<<< orphan*/  bta_ag_scb_to_idx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_ag_svc_conn_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void bta_ag_rcvd_slc_ready(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    UNUSED(p_data);
    APPL_TRACE_DEBUG("bta_ag_rcvd_slc_ready: handle = %d", bta_ag_scb_to_idx(p_scb));

    if (bta_ag_cb.parse_mode == BTA_AG_PASS_THROUGH) {
        /* In pass-through mode, BTA knows that SLC is ready only through call-in. */
        bta_ag_svc_conn_open(p_scb, NULL);
    }
}