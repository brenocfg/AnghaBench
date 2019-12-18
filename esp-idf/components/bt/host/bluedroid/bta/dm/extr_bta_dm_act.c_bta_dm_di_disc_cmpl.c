#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_DM_SEARCH ;
struct TYPE_8__ {scalar_t__ offset; } ;
struct TYPE_9__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;
struct TYPE_10__ {int /*<<< orphan*/  result; int /*<<< orphan*/  num_record; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_3__ tBTA_DM_DI_DISC_CMPL ;
struct TYPE_12__ {int /*<<< orphan*/ * p_di_db; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* p_search_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  peer_bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_DI_DISC_CMPL_EVT ; 
 int /*<<< orphan*/  BTA_FAILURE ; 
 scalar_t__ SDP_DB_FULL ; 
 int /*<<< orphan*/  SDP_GetNumDiRecords (int /*<<< orphan*/ *) ; 
 scalar_t__ SDP_SUCCESS ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ bta_dm_di_cb ; 
 TYPE_5__ bta_dm_search_cb ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bta_dm_di_disc_cmpl(tBTA_DM_MSG *p_data)
{
    tBTA_DM_DI_DISC_CMPL    di_disc;

    memset(&di_disc, 0, sizeof(tBTA_DM_DI_DISC_CMPL));
    bdcpy(di_disc.bd_addr, bta_dm_search_cb.peer_bdaddr);

    if ((p_data->hdr.offset == SDP_SUCCESS)
            || (p_data->hdr.offset == SDP_DB_FULL)) {
        di_disc.num_record  = SDP_GetNumDiRecords(bta_dm_di_cb.p_di_db);
    } else {
        di_disc.result      = BTA_FAILURE;
    }

    bta_dm_di_cb.p_di_db = NULL;
    bta_dm_search_cb.p_search_cback(BTA_DM_DI_DISC_CMPL_EVT, (tBTA_DM_SEARCH *) &di_disc);
}