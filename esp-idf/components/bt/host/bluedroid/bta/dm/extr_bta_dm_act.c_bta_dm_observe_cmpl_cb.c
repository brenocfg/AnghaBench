#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  num_resp; } ;
typedef  TYPE_2__ tBTM_INQUIRY_CMPL ;
struct TYPE_6__ {int /*<<< orphan*/  num_resps; } ;
struct TYPE_8__ {TYPE_1__ inq_cmpl; } ;
typedef  TYPE_3__ tBTA_DM_SEARCH ;
struct TYPE_9__ {int /*<<< orphan*/  (* p_scan_cback ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTA_DM_INQ_CMPL_EVT ; 
 TYPE_5__ bta_dm_search_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void bta_dm_observe_cmpl_cb (void *p_result)
{
    tBTA_DM_SEARCH  data;

    APPL_TRACE_DEBUG("bta_dm_observe_cmpl_cb");

    data.inq_cmpl.num_resps = ((tBTM_INQUIRY_CMPL *)p_result)->num_resp;
    if (bta_dm_search_cb.p_scan_cback) {
        bta_dm_search_cb.p_scan_cback(BTA_DM_INQ_CMPL_EVT, &data);
    }
}