#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ status; } ;
struct TYPE_6__ {TYPE_1__ disc_result; } ;
typedef  TYPE_2__ tBTA_HF_CLIENT_DATA ;

/* Variables and functions */
 scalar_t__ SDP_DB_FULL ; 
 scalar_t__ SDP_SUCCESS ; 
 int /*<<< orphan*/  bta_hf_client_free_db (TYPE_2__*) ; 
 int /*<<< orphan*/  bta_hf_client_sdp_find_attr () ; 

void bta_hf_client_disc_acp_res(tBTA_HF_CLIENT_DATA *p_data)
{
    /* if found service */
    if (p_data->disc_result.status == SDP_SUCCESS ||
            p_data->disc_result.status == SDP_DB_FULL) {
        /* get attributes */
        bta_hf_client_sdp_find_attr();
    }

    /* free discovery db */
    bta_hf_client_free_db(p_data);
}