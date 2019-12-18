#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  status; int /*<<< orphan*/  r; int /*<<< orphan*/  c; } ;
typedef  TYPE_2__ tBTM_SP_LOC_OOB ;
typedef  int /*<<< orphan*/  tBTM_SP_EVT_DATA ;
typedef  scalar_t__ UINT8 ;
struct TYPE_4__ {int /*<<< orphan*/  (* p_sp_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__ api; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ERR_PROCESSING ; 
 int /*<<< orphan*/  BTM_SP_LOC_OOB_EVT ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,scalar_t__) ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  STREAM_TO_ARRAY16 (int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btm_read_local_oob_complete (UINT8 *p)
{
    tBTM_SP_LOC_OOB evt_data;
    UINT8           status = *p++;

    BTM_TRACE_EVENT ("btm_read_local_oob_complete:%d\n", status);
    if (status == HCI_SUCCESS) {
        evt_data.status = BTM_SUCCESS;
        STREAM_TO_ARRAY16(evt_data.c, p);
        STREAM_TO_ARRAY16(evt_data.r, p);
    } else {
        evt_data.status = BTM_ERR_PROCESSING;
    }

    if (btm_cb.api.p_sp_callback) {
        (*btm_cb.api.p_sp_callback) (BTM_SP_LOC_OOB_EVT, (tBTM_SP_EVT_DATA *)&evt_data);
    }
}