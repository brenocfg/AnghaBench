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
struct TYPE_4__ {scalar_t__ handle; scalar_t__ in_use; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  scalar_t__ UINT16 ;
struct TYPE_5__ {TYPE_1__* lcb_pool; } ;

/* Variables and functions */
 int MAX_L2CAP_LINKS ; 
 TYPE_3__ l2cb ; 

tL2C_LCB  *l2cu_find_lcb_by_handle (UINT16 handle)
{
    int         xx;
    tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++) {
        if ((p_lcb->in_use) && (p_lcb->handle == handle)) {
            return (p_lcb);
        }
    }

    /* If here, no match found */
    return (NULL);
}