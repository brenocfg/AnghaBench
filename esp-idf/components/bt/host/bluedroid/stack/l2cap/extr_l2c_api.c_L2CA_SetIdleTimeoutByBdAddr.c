#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  p_first_ccb; } ;
struct TYPE_7__ {scalar_t__ link_state; TYPE_1__ ccb_queue; void* idle_timeout; scalar_t__ in_use; } ;
typedef  TYPE_2__ tL2C_LCB ;
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  void* UINT16 ;
struct TYPE_8__ {TYPE_2__* lcb_pool; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BT_BD_ANY ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ LST_CONNECTED ; 
 int MAX_L2CAP_LINKS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__ l2cb ; 
 TYPE_2__* l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_no_dynamic_ccbs (TYPE_2__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN L2CA_SetIdleTimeoutByBdAddr(BD_ADDR bd_addr, UINT16 timeout, tBT_TRANSPORT transport)
{
    tL2C_LCB        *p_lcb;

    if (memcmp (BT_BD_ANY, bd_addr, BD_ADDR_LEN)) {
        p_lcb = l2cu_find_lcb_by_bd_addr( bd_addr, transport);
        if ((p_lcb) && (p_lcb->in_use) && (p_lcb->link_state == LST_CONNECTED)) {
            p_lcb->idle_timeout = timeout;

            if (!p_lcb->ccb_queue.p_first_ccb) {
                l2cu_no_dynamic_ccbs (p_lcb);
            }
        } else {
            return FALSE;
        }
    } else {
        int         xx;
        tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

        for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++) {
            if ((p_lcb->in_use) && (p_lcb->link_state == LST_CONNECTED)) {
                p_lcb->idle_timeout = timeout;

                if (!p_lcb->ccb_queue.p_first_ccb) {
                    l2cu_no_dynamic_ccbs (p_lcb);
                }
            }
        }
    }

    return TRUE;
}