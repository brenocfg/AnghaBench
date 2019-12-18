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
struct TYPE_6__ {scalar_t__ con_state; } ;
typedef  TYPE_2__ tGAP_CCB ;
typedef  size_t UINT16 ;
struct TYPE_5__ {TYPE_2__* ccb_pool; } ;
struct TYPE_7__ {TYPE_1__ conn; } ;

/* Variables and functions */
 scalar_t__ GAP_CCB_STATE_IDLE ; 
 size_t GAP_MAX_CONNECTIONS ; 
 TYPE_4__ gap_cb ; 

__attribute__((used)) static tGAP_CCB *gap_find_ccb_by_handle (UINT16 handle)
{
    tGAP_CCB     *p_ccb;

    /* Check that handle is valid */
    if (handle < GAP_MAX_CONNECTIONS) {
        p_ccb = &gap_cb.conn.ccb_pool[handle];

        if (p_ccb->con_state != GAP_CCB_STATE_IDLE) {
            return (p_ccb);
        }
    }

    /* If here, handle points to invalid connection */
    return (NULL);
}