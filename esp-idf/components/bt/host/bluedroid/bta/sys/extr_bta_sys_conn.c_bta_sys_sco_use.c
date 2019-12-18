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
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* p_sco_cb ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_SYS_SCO_OPEN ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 TYPE_1__ bta_sys_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_sys_sco_use(UINT8 id, UINT8 app_id, BD_ADDR peer_addr)
{
    UNUSED(id);

    /* AV streaming need to be suspended before SCO is connected. */
    if (bta_sys_cb.p_sco_cb) {
        /* without querying BTM_GetNumScoLinks() */
        bta_sys_cb.p_sco_cb(BTA_SYS_SCO_OPEN, 1, app_id, peer_addr);
    }
}