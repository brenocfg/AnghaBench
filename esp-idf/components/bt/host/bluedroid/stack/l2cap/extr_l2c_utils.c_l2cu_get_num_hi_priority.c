#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ acl_priority; scalar_t__ in_use; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  scalar_t__ UINT8 ;
struct TYPE_4__ {TYPE_1__* lcb_pool; } ;

/* Variables and functions */
 scalar_t__ L2CAP_PRIORITY_HIGH ; 
 int MAX_L2CAP_LINKS ; 
 TYPE_2__ l2cb ; 

UINT8 l2cu_get_num_hi_priority (void)
{
    UINT8       no_hi = 0;
    int         xx;
    tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++) {
        if ((p_lcb->in_use) && (p_lcb->acl_priority == L2CAP_PRIORITY_HIGH)) {
            no_hi++;
        }
    }
    return no_hi;
}