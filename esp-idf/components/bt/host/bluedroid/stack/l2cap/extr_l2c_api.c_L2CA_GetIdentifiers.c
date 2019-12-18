#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {TYPE_1__* p_lcb; int /*<<< orphan*/  remote_cid; } ;
typedef  TYPE_2__ tL2C_CCB ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 TYPE_2__* l2cu_find_ccb_by_cid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool L2CA_GetIdentifiers(uint16_t lcid, uint16_t *rcid, uint16_t *handle)
{
    tL2C_CCB *control_block = l2cu_find_ccb_by_cid(NULL, lcid);
    if (!control_block) {
        return false;
    }

    if (rcid) {
        *rcid = control_block->remote_cid;
    }
    if (handle) {
        *handle = control_block->p_lcb->handle;
    }

    return true;
}