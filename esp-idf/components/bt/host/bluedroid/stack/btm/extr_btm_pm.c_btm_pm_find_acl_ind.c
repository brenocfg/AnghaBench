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
struct TYPE_5__ {scalar_t__ transport; int /*<<< orphan*/  remote_addr; scalar_t__ in_use; } ;
typedef  TYPE_2__ tACL_CONN ;
typedef  size_t UINT8 ;
struct TYPE_6__ {TYPE_1__* pm_mode_db; TYPE_2__* acl_db; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ BT_TRANSPORT_BR_EDR ; 
 size_t MAX_L2CAP_LINKS ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btm_pm_find_acl_ind(BD_ADDR remote_bda)
{
    tACL_CONN   *p = &btm_cb.acl_db[0];
    UINT8 xx;

    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p++) {
        if ((p->in_use) && (!memcmp (p->remote_addr, remote_bda, BD_ADDR_LEN))
#if (BLE_INCLUDED == TRUE)
                && p->transport == BT_TRANSPORT_BR_EDR
#endif  // BLE_INCLUDED
           ) {
#if BTM_PM_DEBUG == TRUE
            BTM_TRACE_DEBUG( "btm_pm_find_acl_ind ind:%d, st:%d", xx, btm_cb.pm_mode_db[xx].state);
#endif  // BTM_PM_DEBUG
            break;
        }
    }
    return xx;
}