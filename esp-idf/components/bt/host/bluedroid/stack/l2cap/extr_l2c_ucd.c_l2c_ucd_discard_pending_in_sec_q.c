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
struct TYPE_5__ {TYPE_1__* p_lcb; } ;
typedef  TYPE_2__ tL2C_CCB ;
struct TYPE_4__ {int /*<<< orphan*/  ucd_in_sec_pending_q; } ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void l2c_ucd_discard_pending_in_sec_q(tL2C_CCB  *p_ccb)
{
    BT_HDR *p_buf = (BT_HDR*)fixed_queue_dequeue(p_ccb->p_lcb->ucd_in_sec_pending_q, 0);

    if (p_buf) {
        osi_free (p_buf);
    }
}