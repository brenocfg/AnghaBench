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
struct TYPE_5__ {int /*<<< orphan*/  xmit_data_q; } ;
typedef  TYPE_2__ tSCO_CONN ;
typedef  size_t UINT16 ;
struct TYPE_4__ {TYPE_2__* sco_db; } ;
struct TYPE_6__ {TYPE_1__ sco_cb; } ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 size_t BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  UNUSED (size_t) ; 
 TYPE_3__ btm_cb ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void btm_sco_flush_sco_data(UINT16 sco_inx)
{
#if BTM_SCO_HCI_INCLUDED == TRUE
#if (BTM_MAX_SCO_LINKS>0)
    tSCO_CONN   *p ;
    BT_HDR      *p_buf;

    if (sco_inx < BTM_MAX_SCO_LINKS) {
        p = &btm_cb.sco_cb.sco_db[sco_inx];
        while ((p_buf = (BT_HDR *)fixed_queue_dequeue(p->xmit_data_q, 0)) != NULL) {
            osi_free(p_buf);
        }
    }
#else
    UNUSED(sco_inx);
#endif
#else
    UNUSED(sco_inx);
#endif
}