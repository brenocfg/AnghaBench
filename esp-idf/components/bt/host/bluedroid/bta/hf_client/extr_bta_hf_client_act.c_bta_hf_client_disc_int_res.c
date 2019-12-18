#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ status; } ;
struct TYPE_7__ {TYPE_1__ disc_result; } ;
typedef  TYPE_2__ tBTA_HF_CLIENT_DATA ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,scalar_t__) ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_DISC_FAIL_EVT ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_DISC_OK_EVT ; 
 scalar_t__ SDP_DB_FULL ; 
 scalar_t__ SDP_SUCCESS ; 
 int /*<<< orphan*/  bta_hf_client_free_db (TYPE_2__*) ; 
 scalar_t__ bta_hf_client_sdp_find_attr () ; 
 int /*<<< orphan*/  bta_hf_client_sm_execute (int /*<<< orphan*/ ,TYPE_2__*) ; 

void bta_hf_client_disc_int_res(tBTA_HF_CLIENT_DATA *p_data)
{
    UINT16 event = BTA_HF_CLIENT_DISC_FAIL_EVT;

    APPL_TRACE_DEBUG ("bta_hf_client_disc_int_res: Status: %d", p_data->disc_result.status);

    /* if found service */
    if (p_data->disc_result.status == SDP_SUCCESS ||
            p_data->disc_result.status == SDP_DB_FULL) {
        /* get attributes */
        if (bta_hf_client_sdp_find_attr()) {
            event = BTA_HF_CLIENT_DISC_OK_EVT;
        }
    }

    /* free discovery db */
    bta_hf_client_free_db(p_data);

    /* send ourselves sdp ok/fail event */
    bta_hf_client_sm_execute(event, p_data);
}