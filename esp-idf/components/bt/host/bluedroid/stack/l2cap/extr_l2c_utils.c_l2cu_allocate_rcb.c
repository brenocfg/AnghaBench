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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct TYPE_6__ {TYPE_1__ ucd; scalar_t__ psm; scalar_t__ in_use; } ;
typedef  TYPE_2__ tL2C_RCB ;
typedef  scalar_t__ UINT16 ;
struct TYPE_7__ {TYPE_2__* rcb_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2C_UCD_STATE_UNUSED ; 
 scalar_t__ MAX_L2CAP_CLIENTS ; 
 scalar_t__ TRUE ; 
 TYPE_4__ l2cb ; 

tL2C_RCB *l2cu_allocate_rcb (UINT16 psm)
{
    tL2C_RCB    *p_rcb = &l2cb.rcb_pool[0];
    UINT16      xx;

    for (xx = 0; xx < MAX_L2CAP_CLIENTS; xx++, p_rcb++) {
        if (!p_rcb->in_use) {
            p_rcb->in_use = TRUE;
            p_rcb->psm    = psm;
#if (L2CAP_UCD_INCLUDED == TRUE)
            p_rcb->ucd.state = L2C_UCD_STATE_UNUSED;
#endif
            return (p_rcb);
        }
    }

    /* If here, no free RCB found */
    return (NULL);
}