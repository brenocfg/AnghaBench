#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t conn_service; } ;
typedef  TYPE_2__ tBTA_AG_SCB ;
struct TYPE_9__ {scalar_t__ status; } ;
struct TYPE_11__ {TYPE_1__ disc_result; } ;
typedef  TYPE_3__ tBTA_AG_DATA ;

/* Variables and functions */
 scalar_t__ SDP_DB_FULL ; 
 scalar_t__ SDP_SUCCESS ; 
 int /*<<< orphan*/  bta_ag_free_db (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_ag_sdp_find_attr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bta_ag_svc_mask ; 

void bta_ag_disc_acp_res(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    /* if found service */
    if (p_data->disc_result.status == SDP_SUCCESS ||
        p_data->disc_result.status == SDP_DB_FULL) {
        /* get attributes */
        bta_ag_sdp_find_attr(p_scb, bta_ag_svc_mask[p_scb->conn_service]);
    }
    /* free discovery db */
    bta_ag_free_db(p_scb, p_data);
}