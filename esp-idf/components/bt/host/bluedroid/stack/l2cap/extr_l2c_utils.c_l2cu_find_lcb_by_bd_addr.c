#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ transport; int /*<<< orphan*/  remote_bd_addr; scalar_t__ in_use; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  scalar_t__ tBT_TRANSPORT ;
struct TYPE_5__ {TYPE_1__* lcb_pool; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int MAX_L2CAP_LINKS ; 
 TYPE_3__ l2cb ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tL2C_LCB  *l2cu_find_lcb_by_bd_addr (BD_ADDR p_bd_addr, tBT_TRANSPORT transport)
{
    int         xx;
    tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++) {
        if ((p_lcb->in_use) &&
#if BLE_INCLUDED == TRUE
                p_lcb->transport == transport &&
#endif
                (!memcmp (p_lcb->remote_bd_addr, p_bd_addr, BD_ADDR_LEN))) {
            return (p_lcb);
        }
    }

    /* If here, no match found */
    return (NULL);
}