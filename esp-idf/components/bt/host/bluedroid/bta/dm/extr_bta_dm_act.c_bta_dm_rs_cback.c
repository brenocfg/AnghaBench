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
typedef  int /*<<< orphan*/  tBTM_ROLE_SWITCH_CMPL ;
typedef  int /*<<< orphan*/  tBTA_DM_MSG ;
struct TYPE_3__ {int /*<<< orphan*/  rs_res; } ;
struct TYPE_4__ {scalar_t__ rs_event; TYPE_1__ search_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_WARNING (char*,scalar_t__) ; 
 scalar_t__ BTA_DM_API_SEARCH_EVT ; 
 int /*<<< orphan*/  BTA_DM_RS_OK ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_2__ bta_dm_cb ; 
 int /*<<< orphan*/  bta_dm_search_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bta_dm_rs_cback (tBTM_ROLE_SWITCH_CMPL *p1)
{
    UNUSED(p1);
    APPL_TRACE_WARNING("bta_dm_rs_cback:%d", bta_dm_cb.rs_event);
    if (bta_dm_cb.rs_event == BTA_DM_API_SEARCH_EVT) {
        bta_dm_cb.search_msg.rs_res = BTA_DM_RS_OK; /* do not care about the result for now */
        bta_dm_cb.rs_event = 0;
        bta_dm_search_start((tBTA_DM_MSG *)&bta_dm_cb.search_msg);
    }
}