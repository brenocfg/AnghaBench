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
typedef  scalar_t__ UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* ppm_cb ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_sco_cb ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BTA_ID_AG ; 
 int /*<<< orphan*/  BTA_SYS_SCO_CLOSE ; 
 scalar_t__ BTM_GetNumScoLinks () ; 
 TYPE_1__ bta_sys_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void bta_sys_sco_close(UINT8 id, UINT8 app_id, BD_ADDR peer_addr)
{
    UINT8 num_sco_links;

    if ((id != BTA_ID_AG) && (bta_sys_cb.p_sco_cb)) {
        num_sco_links = BTM_GetNumScoLinks();
        bta_sys_cb.p_sco_cb(BTA_SYS_SCO_CLOSE, num_sco_links, app_id, peer_addr);
    }

    if (bta_sys_cb.ppm_cb) {
        bta_sys_cb.ppm_cb(BTA_SYS_SCO_CLOSE, id, app_id, peer_addr);
    }
}