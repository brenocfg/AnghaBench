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
struct TYPE_5__ {scalar_t__ link_state; void* idle_timeout; scalar_t__ in_use; } ;
typedef  TYPE_1__ tL2C_LCB ;
struct TYPE_6__ {TYPE_1__* p_lcb; } ;
typedef  TYPE_2__ tL2C_CCB ;
typedef  void* UINT16 ;
struct TYPE_7__ {void* idle_timeout; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,void*) ; 
 scalar_t__ LST_CONNECTED ; 
 scalar_t__ TRUE ; 
 TYPE_4__ l2cb ; 
 TYPE_2__* l2cu_find_ccb_by_cid (int /*<<< orphan*/ *,void*) ; 

BOOLEAN L2CA_SetIdleTimeout (UINT16 cid, UINT16 timeout, BOOLEAN is_global)
{
    tL2C_CCB        *p_ccb;
    tL2C_LCB        *p_lcb;

    if (is_global) {
        l2cb.idle_timeout = timeout;
    } else {
        /* Find the channel control block. We don't know the link it is on. */
        if ((p_ccb = l2cu_find_ccb_by_cid (NULL, cid)) == NULL) {
            L2CAP_TRACE_WARNING ("L2CAP - no CCB for L2CA_SetIdleTimeout, CID: %d", cid);
            return (FALSE);
        }

        p_lcb = p_ccb->p_lcb;

        if ((p_lcb) && (p_lcb->in_use) && (p_lcb->link_state == LST_CONNECTED)) {
            p_lcb->idle_timeout = timeout;
        } else {
            return (FALSE);
        }
    }

    return (TRUE);
}