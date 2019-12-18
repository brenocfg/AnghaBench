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
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  result; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_1__ tBTA_DM_DI_DISC_CMPL ;
struct TYPE_7__ {int /*<<< orphan*/ * p_di_db; } ;
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  (* p_search_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  peer_bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_DI_DISC_CMPL_EVT ; 
 scalar_t__ BTA_DM_SEARCH_IDLE ; 
 int /*<<< orphan*/  BTA_FAILURE ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ bta_dm_di_cb ; 
 int /*<<< orphan*/  bta_dm_search_cancel (int /*<<< orphan*/ *) ; 
 TYPE_3__ bta_dm_search_cb ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bta_dm_disable_search_and_disc (void)
{
#if (SDP_INCLUDED == TRUE)
    tBTA_DM_DI_DISC_CMPL    di_disc;
#endif ///SDP_INCLUDED == TRUE
    if (bta_dm_search_cb.state != BTA_DM_SEARCH_IDLE) {
        bta_dm_search_cancel(NULL);
    }
#if (SDP_INCLUDED == TRUE)
    if (bta_dm_di_cb.p_di_db != NULL) {
        memset(&di_disc, 0, sizeof(tBTA_DM_DI_DISC_CMPL));
        bdcpy(di_disc.bd_addr, bta_dm_search_cb.peer_bdaddr);
        di_disc.result      = BTA_FAILURE;

        bta_dm_di_cb.p_di_db = NULL;
        bta_dm_search_cb.p_search_cback(BTA_DM_DI_DISC_CMPL_EVT, NULL);
    }
#endif  ///SDP_INCLUDED == TRUE
}