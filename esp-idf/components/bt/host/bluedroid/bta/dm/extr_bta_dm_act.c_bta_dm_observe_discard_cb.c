#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  num_dis; } ;
struct TYPE_6__ {TYPE_1__ inq_dis; } ;
typedef  TYPE_2__ tBTA_DM_SEARCH ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_scan_cback ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTA_DM_INQ_DISCARD_NUM_EVT ; 
 TYPE_4__ bta_dm_search_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void bta_dm_observe_discard_cb (uint32_t num_dis)
{
    tBTA_DM_SEARCH  data;

    APPL_TRACE_DEBUG("bta_dm_observe_discard_cb");

    data.inq_dis.num_dis = num_dis;
    if (bta_dm_search_cb.p_scan_cback) {
        bta_dm_search_cb.p_scan_cback(BTA_DM_INQ_DISCARD_NUM_EVT, &data);
    }
}